#include "wanbeiyu.h"

#include <assert.h>
#include <stdio.h>

#define TEXT_RED "\e[31m"
#define TEXT_GREEN "\e[32m"
#define TEXT_RESET "\e[0m"

#include "test_gpio.h"
#include "test_dac.h"
#include "test_digipot.h"
#include "test_switch.h"

#include "button.h"

int test_hat(void)
{
    int index = -1;

    test_gpio_t gpio_up;
    test_gpio_init(&gpio_up);
    wby_button_t btn_up;
    wby_button_init(&btn_up, (wby_gpio_t *)&gpio_up);

    test_gpio_t gpio_right;
    test_gpio_init(&gpio_right);
    wby_button_t btn_right;
    wby_button_init(&btn_right, (wby_gpio_t *)&gpio_right);

    test_gpio_t gpio_down;
    test_gpio_init(&gpio_down);
    wby_button_t btn_down;
    wby_button_init(&btn_down, (wby_gpio_t *)&gpio_down);

    test_gpio_t gpio_left;
    test_gpio_init(&gpio_left);
    wby_button_t btn_left;
    wby_button_init(&btn_left, (wby_gpio_t *)&gpio_left);

    wby_hat_t hat;
    wby_hat_init(&hat, &btn_up, &btn_right, &btn_down, &btn_left);
    assert(gpio_up.state == TEST_GPIO_STATE_HI_Z &&
           gpio_right.state == TEST_GPIO_STATE_HI_Z &&
           gpio_down.state == TEST_GPIO_STATE_HI_Z &&
           gpio_left.state == TEST_GPIO_STATE_HI_Z);

    wby_hat_hold(&hat, WBY_HAT_UP);
    if (!(gpio_up.state == TEST_GPIO_STATE_LOW &&
          gpio_right.state == TEST_GPIO_STATE_HI_Z &&
          gpio_down.state == TEST_GPIO_STATE_HI_Z &&
          gpio_left.state == TEST_GPIO_STATE_HI_Z))
    {
        index = 0;
        goto cleanup;
    }

    wby_hat_hold(&hat, WBY_HAT_UPRIGHT);
    if (!(gpio_up.state == TEST_GPIO_STATE_LOW &&
          gpio_right.state == TEST_GPIO_STATE_LOW &&
          gpio_down.state == TEST_GPIO_STATE_HI_Z &&
          gpio_left.state == TEST_GPIO_STATE_HI_Z))
    {
        index = 1;
        goto cleanup;
    }

    wby_hat_hold(&hat, WBY_HAT_RIGHT);
    if (!(gpio_up.state == TEST_GPIO_STATE_HI_Z &&
          gpio_right.state == TEST_GPIO_STATE_LOW &&
          gpio_down.state == TEST_GPIO_STATE_HI_Z &&
          gpio_left.state == TEST_GPIO_STATE_HI_Z))
    {
        index = 2;
        goto cleanup;
    }

    wby_hat_hold(&hat, WBY_HAT_DOWNRIGHT);
    if (!(gpio_up.state == TEST_GPIO_STATE_HI_Z &&
          gpio_right.state == TEST_GPIO_STATE_LOW &&
          gpio_down.state == TEST_GPIO_STATE_LOW &&
          gpio_left.state == TEST_GPIO_STATE_HI_Z))
    {
        index = 3;
        goto cleanup;
    }

    wby_hat_hold(&hat, WBY_HAT_DOWN);
    if (!(gpio_up.state == TEST_GPIO_STATE_HI_Z &&
          gpio_right.state == TEST_GPIO_STATE_HI_Z &&
          gpio_down.state == TEST_GPIO_STATE_LOW &&
          gpio_left.state == TEST_GPIO_STATE_HI_Z))
    {
        index = 4;
        goto cleanup;
    }

    wby_hat_hold(&hat, WBY_HAT_DOWNLEFT);
    if (!(gpio_up.state == TEST_GPIO_STATE_HI_Z &&
          gpio_right.state == TEST_GPIO_STATE_HI_Z &&
          gpio_down.state == TEST_GPIO_STATE_LOW &&
          gpio_left.state == TEST_GPIO_STATE_LOW))
    {
        index = 5;
        goto cleanup;
    }

    wby_hat_hold(&hat, WBY_HAT_LEFT);
    if (!(gpio_up.state == TEST_GPIO_STATE_HI_Z &&
          gpio_right.state == TEST_GPIO_STATE_HI_Z &&
          gpio_down.state == TEST_GPIO_STATE_HI_Z &&
          gpio_left.state == TEST_GPIO_STATE_LOW))
    {
        index = 6;
        goto cleanup;
    }

    wby_hat_hold(&hat, WBY_HAT_UPLEFT);
    if (!(gpio_up.state == TEST_GPIO_STATE_LOW &&
          gpio_right.state == TEST_GPIO_STATE_HI_Z &&
          gpio_down.state == TEST_GPIO_STATE_HI_Z &&
          gpio_left.state == TEST_GPIO_STATE_LOW))
    {
        index = 7;
        goto cleanup;
    }

    wby_hat_hold(&hat, WBY_HAT_NEUTRAL);
    if (!(gpio_up.state == TEST_GPIO_STATE_HI_Z &&
          gpio_right.state == TEST_GPIO_STATE_HI_Z &&
          gpio_down.state == TEST_GPIO_STATE_HI_Z &&
          gpio_left.state == TEST_GPIO_STATE_HI_Z))
    {
        index = 8;
        goto cleanup;
    }

    wby_hat_release(&hat);
    if (!(gpio_up.state == TEST_GPIO_STATE_HI_Z &&
          gpio_right.state == TEST_GPIO_STATE_HI_Z &&
          gpio_down.state == TEST_GPIO_STATE_HI_Z &&
          gpio_left.state == TEST_GPIO_STATE_HI_Z))
    {
        index = 9;
        goto cleanup;
    }

cleanup:

    return index;
}

int test_slidepad(void)
{
    int index = -1;

    TestDAC *h = test_dac_new();
    assert(h != NULL);
    TestDAC *v = test_dac_new();
    assert(v != NULL);

    wby_slidepad_t sp;
    wby_slidepad_init(&sp, (wby_idac_t *)h, (wby_idac_t *)v);
    assert(v->state == TEST_DAC_SOURCE && v->value == 0 &&
           h->state == TEST_DAC_SOURCE && h->value == 0);

    wby_slidepad_hold(&sp, 0, 0);
    if (!(v->state == TEST_DAC_SOURCE && v->value == UINT8_MAX &&
          h->state == TEST_DAC_SOURCE && h->value == UINT8_MAX))
    {
        index = 0;
        goto cleanup;
    }

    wby_slidepad_hold(&sp, 0, UINT8_MAX);
    if (!(v->state == TEST_DAC_SINK && v->value == UINT8_MAX &&
          h->state == TEST_DAC_SOURCE && h->value == UINT8_MAX))
    {
        index = 1;
        goto cleanup;
    }

    wby_slidepad_hold(&sp, UINT8_MAX, UINT8_MAX);
    if (!(v->state == TEST_DAC_SINK && v->value == UINT8_MAX &&
          h->state == TEST_DAC_SINK && h->value == UINT8_MAX))
    {
        index = 2;
        goto cleanup;
    }

    wby_slidepad_hold(&sp, UINT8_MAX, 0);
    if (!(v->state == TEST_DAC_SOURCE && v->value == UINT8_MAX &&
          h->state == TEST_DAC_SINK && h->value == UINT8_MAX))
    {
        index = 3;
        goto cleanup;
    }

    wby_slidepad_release(&sp);
    if (!(v->state == TEST_DAC_SOURCE && v->value == 0 &&
          h->state == TEST_DAC_SOURCE && h->value == 0))
    {
        index = 4;
        goto cleanup;
    }

cleanup:
    test_dac_delete(h);
    test_dac_delete(v);

    return index;
}

static const uint16_t UINT16_MID = 0x8000U;
static const uint16_t RDAC_TOLERANCE = 500;

int test_touchscreen(void)
{
    int index = -1;

    TestDigiPot *v = test_digipot_new();
    assert(v != NULL);
    TestDigiPot *h = test_digipot_new();
    assert(h != NULL);
    TestSwitch *sw = test_switch_new();
    assert(sw != NULL);

    wby_touchscreen_t ts;
    wby_touchscreen_init(&ts, (wby_rdac_t *)h, (wby_rdac_t *)v, (wby_spst_switch_t *)sw);
    assert(v->state == TEST_DIGIPOT_POWER_OFF && h->state == TEST_DIGIPOT_POWER_OFF);
    assert(sw->state == TEST_SWITCH_OFF);

    wby_touchscreen_hold(&ts, 0, 0);
    if (!(v->state == TEST_DIGIPOT_POWER_ON && v->position == 0 &&
          h->state == TEST_DIGIPOT_POWER_ON && h->position == 0 &&
          sw->state == TEST_SWITCH_ON))
    {
        index = 0;
        goto cleanup;
    }

    wby_touchscreen_hold(&ts, 160, 120);
    if (!(v->state == TEST_DIGIPOT_POWER_ON && (UINT16_MID - RDAC_TOLERANCE < v->position && v->position < UINT16_MID + RDAC_TOLERANCE) &&
          h->state == TEST_DIGIPOT_POWER_ON && (UINT16_MID - RDAC_TOLERANCE < h->position && h->position < UINT16_MID + RDAC_TOLERANCE) &&
          sw->state == TEST_SWITCH_ON))
    {
        index = 1;
        goto cleanup;
    }

    wby_touchscreen_hold(&ts, 319, 239);
    if (!(v->state == TEST_DIGIPOT_POWER_ON && v->position == UINT16_MAX &&
          h->state == TEST_DIGIPOT_POWER_ON && h->position == UINT16_MAX &&
          sw->state == TEST_SWITCH_ON))
    {
        index = 2;
        goto cleanup;
    }

    wby_touchscreen_release(&ts);
    if (!(v->state == TEST_DIGIPOT_POWER_OFF && h->state == TEST_DIGIPOT_POWER_OFF && sw->state == TEST_SWITCH_OFF))
    {
        index = 3;
        goto cleanup;
    }

cleanup:
    test_switch_delete(sw);
    test_digipot_delete(h);
    test_digipot_delete(v);

    return index;
}

int main(void)
{
    int index;

    index = test_hat();
    if (0 <= index)
    {
        fprintf(stderr, "[test_hat] Assertion failed on index %d", index);
        return 1;
    }
    index = test_slidepad();
    if (0 <= index)
    {
        fprintf(stderr, "[test_slidepad] Assertion failed on index %d", index);
        return 1;
    }
    index = test_touchscreen();
    if (0 <= index)
    {
        fprintf(stderr, "[test_touchscreen] Assertion failed on index %d", index);
        return 1;
    }

    int ret = 0;
    ret += test_button();

    if (ret == 0)
    {
        printf("%sOK%s\n", TEXT_GREEN, TEXT_RESET);
        return 0;
    }
    else
    {
        fprintf(stderr, "%s%d errors found%s", TEXT_RED, ret, TEXT_RESET);
        return 1;
    }
}