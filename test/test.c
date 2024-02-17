#include "wanbeiyu.h"

#include <assert.h>
#include <stdio.h>

#define TEXT_RED "\e[31m"
#define TEXT_GREEN "\e[32m"
#define TEXT_RESET "\e[0m"

#include "test_gpio.h"
#include "test_idac.h"
#include "test_digipot.h"
#include "test_switch.h"

#include "button.h"
#include "hat.h"

int test_slidepad_init(void)
{
    printf("  * test_slidepad_init\n");
    int cnt = 0;

    typedef struct test_cast_t
    {
        wby_slidepad_t *sp;
        test_idac_t *h;
        test_idac_t *v;
        wby_error_t expected_ret;
    } test_cast_t;

    wby_slidepad_t case_1_sp;

    wby_slidepad_t case_2_sp;
    test_idac_t case_2_h;
    test_idac_init(&case_2_h);

    wby_slidepad_t case_3_sp;
    test_idac_t case_3_v;
    test_idac_init(&case_3_v);

    wby_slidepad_t case_4_sp;
    test_idac_t case_4_h;
    test_idac_init(&case_4_h);
    test_idac_t case_4_v;
    test_idac_init(&case_4_v);

    test_cast_t cases[] = {{.sp = NULL, .h = NULL, .v = NULL, .expected_ret = WBY_EINVAL},
                           {.sp = &case_1_sp, .h = NULL, .v = NULL, .expected_ret = WBY_EINVAL},
                           {.sp = &case_2_sp, .h = &case_2_h, .v = NULL, .expected_ret = WBY_EINVAL},
                           {.sp = &case_3_sp, .h = NULL, .v = &case_3_v, .expected_ret = WBY_EINVAL},
                           {.sp = &case_4_sp, .h = &case_4_h, .v = &case_4_h, .expected_ret = WBY_OK}};
    size_t size = sizeof(cases) / sizeof(test_cast_t);

    for (size_t i = 0; i < size; i++)
    {
        test_cast_t case_ = cases[i];

        wby_error_t actual_ret = wby_slidepad_init(case_.sp, (wby_idac_t *)case_.h, (wby_idac_t *)case_.v);

        if (actual_ret != case_.expected_ret)
        {
            fprintf(stderr, "%sindex: %d, expected_ret: %d, actual_ret: %d%s\n", TEXT_RED, i, case_.expected_ret, actual_ret, TEXT_RESET);
            cnt++;
            continue;
        }

        if (actual_ret != WBY_OK)
        {
            continue;
        }

        test_gpio_state_t actual_h_state = case_.h->state;
        uint8_t actual_h_value = case_.h->value;
        test_gpio_state_t actual_v_state = case_.v->state;
        uint8_t actual_v_value = case_.v->value;

        if (actual_h_state != TEST_IDAC_SOURCE ||
            actual_h_value != 0 ||
            actual_v_state != TEST_IDAC_SOURCE ||
            actual_v_value != 0)
        {
            fprintf(stderr, "%sindex: %d,\n"
                            "expected_h_state: %d, actual_h_state: %d, expected_h_value: %d, actual_h_value: %d\n"
                            "expected_v_state: %d, actual_v_state: %d, expected_v_value: %d, actual_v_value: %d%s\n",
                    TEXT_RED, i,
                    TEST_IDAC_SOURCE, actual_h_state, 0, actual_h_value,
                    TEST_IDAC_SOURCE, actual_v_state, 0, actual_v_value,
                    TEXT_RESET);
            cnt++;
        }
    }

    return cnt;
}

int test_slidepad(void)
{
    int index = -1;

    test_idac_t h;
    test_idac_init(&h);
    test_idac_t v;
    test_idac_init(&v);

    wby_slidepad_t sp;
    wby_slidepad_init(&sp, (wby_idac_t *)&h, (wby_idac_t *)&v);
    assert(v.state == TEST_IDAC_SOURCE && v.value == 0 &&
           h.state == TEST_IDAC_SOURCE && h.value == 0);

    wby_slidepad_hold(&sp, 0, 0);
    if (!(v.state == TEST_IDAC_SOURCE && v.value == UINT8_MAX &&
          h.state == TEST_IDAC_SOURCE && h.value == UINT8_MAX))
    {
        index = 0;
        goto cleanup;
    }

    wby_slidepad_hold(&sp, 0, UINT8_MAX);
    if (!(v.state == TEST_IDAC_SINK && v.value == UINT8_MAX &&
          h.state == TEST_IDAC_SOURCE && h.value == UINT8_MAX))
    {
        index = 1;
        goto cleanup;
    }

    wby_slidepad_hold(&sp, UINT8_MAX, UINT8_MAX);
    if (!(v.state == TEST_IDAC_SINK && v.value == UINT8_MAX &&
          h.state == TEST_IDAC_SINK && h.value == UINT8_MAX))
    {
        index = 2;
        goto cleanup;
    }

    wby_slidepad_hold(&sp, UINT8_MAX, 0);
    if (!(v.state == TEST_IDAC_SOURCE && v.value == UINT8_MAX &&
          h.state == TEST_IDAC_SINK && h.value == UINT8_MAX))
    {
        index = 3;
        goto cleanup;
    }

    wby_slidepad_release(&sp);
    if (!(v.state == TEST_IDAC_SOURCE && v.value == 0 &&
          h.state == TEST_IDAC_SOURCE && h.value == 0))
    {
        index = 4;
        goto cleanup;
    }

cleanup:

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

    int cnt = 0;

    cnt += test_button();
    cnt += test_hat();
    cnt += test_slidepad_init();

    if (cnt == 0)
    {
        printf("%sOK%s\n", TEXT_GREEN, TEXT_RESET);
        return 0;
    }
    else
    {
        fprintf(stderr, "%s%d errors found%s\n", TEXT_RED, cnt, TEXT_RESET);
        return 1;
    }
}