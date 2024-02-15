#include "wanbeiyu.h"

#include <assert.h>
#include <stdio.h>

#include "test_gpio.h"
#include "test_dac.h"
#include "test_digipot.h"
#include "test_switch.h"

#define TEXT_RED "\e[31m"
#define TEXT_GREEN "\e[32m"
#define TEXT_RESET "\e[0m"

typedef enum test_gpio_state_t
{
    TEST_GPIO_STATE_LOW,
    TEST_GPIO_STATE_HI_Z,
} test_gpio_state_t;

typedef struct test_gpio_t
{
    wby_gpio_t parent;
    test_gpio_state_t state;
} test_gpio_t;

static wby_error_t test_gpio_set_low(wby_gpio_t *gpio)
{
    ((test_gpio_t *)gpio)->state = TEST_GPIO_STATE_LOW;
    return WBY_OK;
}

static wby_error_t test_gpio_set_hi_z(wby_gpio_t *gpio)
{
    ((test_gpio_t *)gpio)->state = TEST_GPIO_STATE_HI_Z;
    return WBY_OK;
}

static wby_error_t test_gpio_set_hi_z_only_once(wby_gpio_t *gpio)
{
    static int count = 0;
    if (0 < count)
    {
        return WBY_EINVAL;
    }

    ((test_gpio_t *)gpio)->state = TEST_GPIO_STATE_HI_Z;
    count++;
    return WBY_OK;
}

static wby_error_t test_gpio_einval(wby_gpio_t *gpio)
{
    return WBY_EINVAL;
}

int test_button_init(void)
{
    printf("* test_button_init\n");
    int ret = 0;

    typedef struct test_cast_t
    {
        test_gpio_t *gpio;
        wby_error_t expected_ret;
        test_gpio_state_t expected_state;
    } test_cast_t;

    test_gpio_t case_1_gpio;
    case_1_gpio.parent.set_hi_z = test_gpio_set_hi_z;
    case_1_gpio.state = TEST_GPIO_STATE_LOW;

    test_gpio_t case_2_gpio;
    case_2_gpio.parent.set_hi_z = test_gpio_einval;

    test_cast_t cases[] = {{.gpio = NULL, .expected_ret = WBY_EINVAL},
                           {.gpio = &case_1_gpio, .expected_ret = WBY_OK, .expected_state = TEST_GPIO_STATE_HI_Z},
                           {.gpio = &case_2_gpio, .expected_ret = WBY_EINVAL}};
    size_t size = sizeof(cases) / sizeof(test_cast_t);

    for (size_t i = 0; i < size; i++)
    {
        test_cast_t case_ = cases[i];

        wby_button_t btn;
        wby_error_t actual_ret = wby_button_init(&btn, (wby_gpio_t *)case_.gpio);

        if (actual_ret != case_.expected_ret)
        {
            fprintf(stderr, "%sindex: %d, expected_ret: %d, actual_ret: %d%s\n", TEXT_RED, i, case_.expected_ret, actual_ret, TEXT_RESET);
            ret++;
            continue;
        }
        if (actual_ret != WBY_OK)
        {
            continue;
        }

        test_gpio_state_t actual_state = case_.gpio->state;

        if (actual_state != case_.expected_state)
        {
            fprintf(stderr, "%sindex: %d, expected_state: %d, actual_state: %d%s\n", TEXT_RED, i, case_.expected_state, actual_state, TEXT_RESET);
            ret++;
        }
    }

    return ret;
}

int test_button_hold(void)
{
    printf("* test_button_hold\n");
    int ret = 0;

    typedef struct test_cast_t
    {
        test_gpio_t *gpio;
        wby_error_t expected_ret;
        test_gpio_state_t expected_state;
    } test_cast_t;

    test_gpio_t case_0_gpio;
    case_0_gpio.parent.set_low = test_gpio_set_low;
    case_0_gpio.parent.set_hi_z = test_gpio_set_hi_z;

    test_gpio_t case_1_gpio;
    case_1_gpio.parent.set_low = test_gpio_einval;
    case_1_gpio.parent.set_hi_z = test_gpio_set_hi_z;

    test_cast_t cases[] = {{.gpio = &case_0_gpio, .expected_ret = WBY_OK, .expected_state = TEST_GPIO_STATE_LOW},
                           {.gpio = &case_1_gpio, .expected_ret = WBY_EINVAL}};
    size_t size = sizeof(cases) / sizeof(test_cast_t);

    for (size_t i = 0; i < size; i++)
    {
        test_cast_t case_ = cases[i];

        wby_button_t btn;
        assert(wby_button_init(&btn, (wby_gpio_t *)case_.gpio) == WBY_OK);

        wby_error_t actual_ret = wby_button_hold(&btn);

        if (actual_ret != case_.expected_ret)
        {
            fprintf(stderr, "%sindex: %d, expected_ret: %d, actual_ret: %d%s\n", TEXT_RED, i, case_.expected_ret, actual_ret, TEXT_RESET);
            ret++;
            continue;
        }
        if (actual_ret != WBY_OK)
        {
            continue;
        }

        test_gpio_state_t actual_state = case_.gpio->state;

        if (actual_state != case_.expected_state)
        {
            fprintf(stderr, "%sindex: %d, expected_state: %d, actual_state: %d%s\n", TEXT_RED, i, case_.expected_state, actual_state, TEXT_RESET);
            ret++;
        }
    }

    return ret;
}

int test_button_release(void)
{
    printf("* test_button_release\n");
    int ret = 0;

    typedef struct test_cast_t
    {
        test_gpio_t *gpio;
        wby_error_t expected_ret;
        test_gpio_state_t expected_state;
    } test_cast_t;

    test_gpio_t case_0_gpio;
    case_0_gpio.parent.set_hi_z = test_gpio_set_hi_z;

    test_gpio_t case_1_gpio;
    case_1_gpio.parent.set_hi_z = test_gpio_set_hi_z_only_once;

    test_cast_t cases[] = {{.gpio = &case_0_gpio, .expected_ret = WBY_OK, .expected_state = TEST_GPIO_STATE_HI_Z},
                           {.gpio = &case_1_gpio, .expected_ret = WBY_EINVAL}};
    size_t size = sizeof(cases) / sizeof(test_cast_t);

    for (size_t i = 0; i < size; i++)
    {
        test_cast_t case_ = cases[i];

        wby_button_t btn;
        assert(wby_button_init(&btn, (wby_gpio_t *)case_.gpio) == WBY_OK);

        wby_error_t actual_ret = wby_button_release(&btn);

        if (actual_ret != case_.expected_ret)
        {
            fprintf(stderr, "%sindex: %d, expected_ret: %d, actual_ret: %d%s\n", TEXT_RED, i, case_.expected_ret, actual_ret, TEXT_RESET);
            ret++;
            continue;
        }
        if (actual_ret != WBY_OK)
        {
            continue;
        }

        test_gpio_state_t actual_state = case_.gpio->state;

        if (actual_state != case_.expected_state)
        {
            fprintf(stderr, "%sindex: %d, expected_state: %d, actual_state: %d%s\n", TEXT_RED, i, case_.expected_state, actual_state, TEXT_RESET);
            ret++;
        }
    }

    return ret;
}

int test_hat(void)
{
    int index = -1;

    TestGPIO *gpio_up = test_gpio_new();
    assert(gpio_up != NULL);
    wby_button_t btn_up;
    wby_button_init(&btn_up, (wby_gpio_t *)gpio_up);

    TestGPIO *gpio_right = test_gpio_new();
    assert(gpio_right != NULL);
    wby_button_t btn_right;
    wby_button_init(&btn_right, (wby_gpio_t *)gpio_right);

    TestGPIO *gpio_down = test_gpio_new();
    assert(gpio_down != NULL);
    wby_button_t btn_down;
    wby_button_init(&btn_down, (wby_gpio_t *)gpio_down);

    TestGPIO *gpio_left = test_gpio_new();
    assert(gpio_left != NULL);
    wby_button_t btn_left;
    wby_button_init(&btn_left, (wby_gpio_t *)gpio_left);

    wby_hat_t hat;
    wby_hat_init(&hat, &btn_up, &btn_right, &btn_down, &btn_left);
    assert(gpio_up->state == TEST_GPIO_HI_Z &&
           gpio_right->state == TEST_GPIO_HI_Z &&
           gpio_down->state == TEST_GPIO_HI_Z &&
           gpio_left->state == TEST_GPIO_HI_Z);

    wby_hat_hold(&hat, WBY_HAT_UP);
    if (!(gpio_up->state == TEST_GPIO_LOW &&
          gpio_right->state == TEST_GPIO_HI_Z &&
          gpio_down->state == TEST_GPIO_HI_Z &&
          gpio_left->state == TEST_GPIO_HI_Z))
    {
        index = 0;
        goto cleanup;
    }

    wby_hat_hold(&hat, WBY_HAT_UPRIGHT);
    if (!(gpio_up->state == TEST_GPIO_LOW &&
          gpio_right->state == TEST_GPIO_LOW &&
          gpio_down->state == TEST_GPIO_HI_Z &&
          gpio_left->state == TEST_GPIO_HI_Z))
    {
        index = 1;
        goto cleanup;
    }

    wby_hat_hold(&hat, WBY_HAT_RIGHT);
    if (!(gpio_up->state == TEST_GPIO_HI_Z &&
          gpio_right->state == TEST_GPIO_LOW &&
          gpio_down->state == TEST_GPIO_HI_Z &&
          gpio_left->state == TEST_GPIO_HI_Z))
    {
        index = 2;
        goto cleanup;
    }

    wby_hat_hold(&hat, WBY_HAT_DOWNRIGHT);
    if (!(gpio_up->state == TEST_GPIO_HI_Z &&
          gpio_right->state == TEST_GPIO_LOW &&
          gpio_down->state == TEST_GPIO_LOW &&
          gpio_left->state == TEST_GPIO_HI_Z))
    {
        index = 3;
        goto cleanup;
    }

    wby_hat_hold(&hat, WBY_HAT_DOWN);
    if (!(gpio_up->state == TEST_GPIO_HI_Z &&
          gpio_right->state == TEST_GPIO_HI_Z &&
          gpio_down->state == TEST_GPIO_LOW &&
          gpio_left->state == TEST_GPIO_HI_Z))
    {
        index = 4;
        goto cleanup;
    }

    wby_hat_hold(&hat, WBY_HAT_DOWNLEFT);
    if (!(gpio_up->state == TEST_GPIO_HI_Z &&
          gpio_right->state == TEST_GPIO_HI_Z &&
          gpio_down->state == TEST_GPIO_LOW &&
          gpio_left->state == TEST_GPIO_LOW))
    {
        index = 5;
        goto cleanup;
    }

    wby_hat_hold(&hat, WBY_HAT_LEFT);
    if (!(gpio_up->state == TEST_GPIO_HI_Z &&
          gpio_right->state == TEST_GPIO_HI_Z &&
          gpio_down->state == TEST_GPIO_HI_Z &&
          gpio_left->state == TEST_GPIO_LOW))
    {
        index = 6;
        goto cleanup;
    }

    wby_hat_hold(&hat, WBY_HAT_UPLEFT);
    if (!(gpio_up->state == TEST_GPIO_LOW &&
          gpio_right->state == TEST_GPIO_HI_Z &&
          gpio_down->state == TEST_GPIO_HI_Z &&
          gpio_left->state == TEST_GPIO_LOW))
    {
        index = 7;
        goto cleanup;
    }

    wby_hat_hold(&hat, WBY_HAT_NEUTRAL);
    if (!(gpio_up->state == TEST_GPIO_HI_Z &&
          gpio_right->state == TEST_GPIO_HI_Z &&
          gpio_down->state == TEST_GPIO_HI_Z &&
          gpio_left->state == TEST_GPIO_HI_Z))
    {
        index = 8;
        goto cleanup;
    }

    wby_hat_release(&hat);
    if (!(gpio_up->state == TEST_GPIO_HI_Z &&
          gpio_right->state == TEST_GPIO_HI_Z &&
          gpio_down->state == TEST_GPIO_HI_Z &&
          gpio_left->state == TEST_GPIO_HI_Z))
    {
        index = 9;
        goto cleanup;
    }

cleanup:
    test_gpio_delete(gpio_left);
    test_gpio_delete(gpio_down);
    test_gpio_delete(gpio_right);
    test_gpio_delete(gpio_up);

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

    wby_touchscreen_hold(&ts, 1, 1);
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

    wby_touchscreen_hold(&ts, 320, 240);
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
    ret += test_button_init();
    ret += test_button_hold();
    ret += test_button_release();

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