#ifndef TEST_TOUCHSCREEN_H_
#define TEST_TOUCHSCREEN_H_

#include <wanbeiyu.h>
#include "test.h"

#include <assert.h>
#include <stdio.h>

int test_touchscreen_init(void)
{
    printf("  * %s\n", __func__);
    int cnt = 0;

    typedef struct test_case_t
    {
        wanbeiyu_touchscreen_t *ts;
        test_rdac_t *h;
        test_rdac_t *v;
        test_switch_t *sw;

        wanbeiyu_error_t expected_ret;
    } test_case_t;

    wanbeiyu_touchscreen_t ts[16];
    test_rdac_t h[16];
    test_rdac_t v[16];
    test_switch_t sw[16];
    for (size_t i = 0; i < 16; i++)
    {
        test_rdac_init(&h[i]);
        test_rdac_init(&v[i]);
        test_switch_init(&sw[i]);
    }

    test_case_t cases[] = {{.ts = NULL, /*   */ .h = NULL, /*  */ .v = NULL, /*  */ .sw = NULL, /*   */ .expected_ret = WANBEIYU_EINVAL},
                           {.ts = &ts[1], /* */ .h = NULL, /*  */ .v = NULL, /*  */ .sw = NULL, /*   */ .expected_ret = WANBEIYU_EINVAL},
                           {.ts = NULL, /*   */ .h = &h[2], /* */ .v = NULL, /*  */ .sw = NULL, /*   */ .expected_ret = WANBEIYU_EINVAL},
                           {.ts = &ts[3], /* */ .h = &h[3], /* */ .v = NULL, /*  */ .sw = NULL, /*   */ .expected_ret = WANBEIYU_EINVAL},
                           {.ts = NULL, /*   */ .h = NULL, /*  */ .v = &v[4], /* */ .sw = NULL, /*   */ .expected_ret = WANBEIYU_EINVAL},
                           {.ts = &ts[5], /* */ .h = NULL, /*  */ .v = &v[5], /* */ .sw = NULL, /*   */ .expected_ret = WANBEIYU_EINVAL},
                           {.ts = NULL, /*   */ .h = &h[6], /* */ .v = &v[6], /* */ .sw = NULL, /*   */ .expected_ret = WANBEIYU_EINVAL},
                           {.ts = &ts[7], /* */ .h = &h[7], /* */ .v = &v[7], /* */ .sw = NULL, /*   */ .expected_ret = WANBEIYU_EINVAL},
                           {.ts = NULL, /*   */ .h = NULL, /*  */ .v = NULL, /*  */ .sw = &sw[8], /* */ .expected_ret = WANBEIYU_EINVAL},
                           {.ts = &ts[9], /* */ .h = NULL, /*  */ .v = NULL, /*  */ .sw = &sw[9], /* */ .expected_ret = WANBEIYU_EINVAL},
                           {.ts = NULL, /*   */ .h = &h[10], /**/ .v = NULL, /*  */ .sw = &sw[10], /**/ .expected_ret = WANBEIYU_EINVAL},
                           {.ts = &ts[11], /**/ .h = &h[11], /**/ .v = NULL, /*  */ .sw = &sw[11], /**/ .expected_ret = WANBEIYU_EINVAL},
                           {.ts = NULL, /*   */ .h = NULL, /*  */ .v = &v[12], /**/ .sw = &sw[12], /**/ .expected_ret = WANBEIYU_EINVAL},
                           {.ts = &ts[13], /**/ .h = NULL, /*  */ .v = &v[13], /**/ .sw = &sw[13], /**/ .expected_ret = WANBEIYU_EINVAL},
                           {.ts = NULL, /*   */ .h = &h[14], /**/ .v = &v[14], /**/ .sw = &sw[14], /**/ .expected_ret = WANBEIYU_EINVAL},
                           {.ts = &ts[15], /**/ .h = &h[15], /**/ .v = &v[15], /**/ .sw = &sw[15], /**/ .expected_ret = WANBEIYU_OK}};

    TEST_FOR(cases)
    {
        wanbeiyu_error_t actual_ret = wanbeiyu_touchscreen_init(case_.ts, (wanbeiyu_rdac_t *)case_.h, (wanbeiyu_rdac_t *)case_.v, (wanbeiyu_spst_switch_t *)case_.sw);
        TEST_ASSERT_EQUAL_WANBEIYU_ERROR_RET(case_.expected_ret, actual_ret);
        if (actual_ret != WANBEIYU_OK)
        {
            continue;
        }

        test_rdac_state_t actual_h_state = case_.h->state;
        test_rdac_state_t actual_v_state = case_.v->state;
        test_switch_state_t actual_sw_state = case_.sw->state;

        if (actual_h_state != TEST_RDAC_POWER_OFF ||
            actual_v_state != TEST_RDAC_POWER_OFF ||
            actual_sw_state != TEST_SWITCH_OFF)
        {
            fprintf(stderr, "%sindex: %d,\n"
                            "  expected_h_state: %d, actual_h_state: %d,\n"
                            "  expected_v_state: %d, actual_v_state: %d,\n"
                            "  expected_sw_state: %d, actual_sw_state: %d%s\n",
                    TEXT_RED, i,
                    TEST_RDAC_POWER_OFF, actual_h_state,
                    TEST_RDAC_POWER_OFF, actual_v_state,
                    TEST_SWITCH_OFF, actual_sw_state,
                    TEXT_RESET);
            cnt++;
        }
    }

    return cnt;
}

int test_touchscreen_hold(void)
{
    printf("  * %s\n", __func__);
    int cnt = 0;

    typedef struct test_case_t
    {
        uint16_t x;
        uint8_t y;

        test_rdac_state_t expected_h_state;
        uint16_t expected_h_position;
        test_rdac_state_t expected_v_state;
        uint16_t expected_v_position;
        test_switch_state_t expected_sw_state;
    } test_case_t;

    test_case_t cases[] = {{.x = WANBEIYU_TOUCHSCREEN_X_MIN, .y = WANBEIYU_TOUCHSCREEN_Y_MIN, .expected_h_state = TEST_RDAC_POWER_ON, .expected_h_position = 0, .expected_v_state = TEST_RDAC_POWER_ON, .expected_v_position = 0, .expected_sw_state = TEST_SWITCH_ON},
                           {.x = 160, /*                  */ .y = 120, /*                  */ .expected_h_state = TEST_RDAC_POWER_ON, .expected_h_position = TEST_UINT16_MID, .expected_v_state = TEST_RDAC_POWER_ON, .expected_v_position = TEST_UINT16_MID, .expected_sw_state = TEST_SWITCH_ON},
                           {.x = WANBEIYU_TOUCHSCREEN_X_MAX, .y = WANBEIYU_TOUCHSCREEN_Y_MAX, .expected_h_state = TEST_RDAC_POWER_ON, .expected_h_position = UINT16_MAX, .expected_v_state = TEST_RDAC_POWER_ON, .expected_v_position = UINT16_MAX, .expected_sw_state = TEST_SWITCH_ON},
                           {.x = 320, /*                  */ .y = 0, /*                    */ .expected_h_state = TEST_RDAC_POWER_OFF, .expected_v_state = TEST_RDAC_POWER_OFF, .expected_sw_state = TEST_SWITCH_OFF},
                           {.x = 0, /*                    */ .y = 240, /*                  */ .expected_h_state = TEST_RDAC_POWER_OFF, .expected_v_state = TEST_RDAC_POWER_OFF, .expected_sw_state = TEST_SWITCH_OFF},
                           {.x = 320, /*                  */ .y = 240, /*                  */ .expected_h_state = TEST_RDAC_POWER_OFF, .expected_v_state = TEST_RDAC_POWER_OFF, .expected_sw_state = TEST_SWITCH_OFF}};

    wanbeiyu_touchscreen_t *ts_null = NULL;
    wanbeiyu_touchscreen_hold(ts_null, 0, 0); /* Expected that nothing will happen. */

    TEST_FOR(cases)
    {
        test_rdac_t h;
        test_rdac_init(&h);
        test_rdac_t v;
        test_rdac_init(&v);
        test_switch_t sw;
        test_switch_init(&sw);
        wanbeiyu_touchscreen_t ts;
        assert(wanbeiyu_touchscreen_init(&ts, (wanbeiyu_rdac_t *)&h, (wanbeiyu_rdac_t *)&v, (wanbeiyu_spst_switch_t *)&sw) == WANBEIYU_OK);

        wanbeiyu_touchscreen_hold(&ts, case_.x, case_.y);

        test_rdac_state_t actual_h_state = h.state;
        test_rdac_state_t actual_v_state = v.state;
        test_switch_state_t actual_sw_state = sw.state;

        if (actual_h_state != case_.expected_h_state ||
            actual_v_state != case_.expected_v_state ||
            actual_sw_state != case_.expected_sw_state)
        {
            fprintf(stderr, "%sindex: %d,\n"
                            "  expected_h_state: %d, actual_h_state: %d,\n"
                            "  expected_v_state: %d, actual_v_state: %d,\n"
                            "  expected_sw_state: %d, actual_sw_state: %d%s\n",
                    TEXT_RED, i,
                    case_.expected_h_state, actual_h_state,
                    case_.expected_v_state, actual_v_state,
                    case_.expected_sw_state, actual_sw_state,
                    TEXT_RESET);
            cnt++;
            continue;
        }

        if (actual_h_state != TEST_RDAC_POWER_ON ||
            actual_v_state != TEST_RDAC_POWER_ON ||
            actual_sw_state != TEST_SWITCH_ON)
        {
            continue;
        }

        uint16_t actual_h_position = h.position;
        uint16_t actual_v_position = v.position;

        if ((h.position < case_.expected_h_position - TEST_RDAC_TOLERANCE && case_.expected_h_position + TEST_RDAC_TOLERANCE < h.position) ||
            (v.position < case_.expected_v_position - TEST_RDAC_TOLERANCE && case_.expected_v_position + TEST_RDAC_TOLERANCE < v.position))
        {
            fprintf(stderr, "%sindex: %d,\n"
                            "  expected_h_position: %d, actual_h_position: %d,\n"
                            "  expected_v_position: %d, actual_v_position: %d%s\n",
                    TEXT_RED, i,
                    case_.expected_h_position, actual_h_position,
                    case_.expected_v_position, actual_v_position,
                    TEXT_RESET);
            cnt++;
            continue;
        }
    }

    return cnt;
}

int test_touchscreen_release(void)
{
    printf("  * %s\n", __func__);
    int cnt = 0;

    wanbeiyu_touchscreen_t *ts_null = NULL;
    wanbeiyu_touchscreen_release(ts_null); /* Expected that nothing will happen. */

    test_rdac_t h;
    test_rdac_init(&h);
    test_rdac_t v;
    test_rdac_init(&v);
    test_switch_t sw;
    test_switch_init(&sw);
    wanbeiyu_touchscreen_t ts;
    assert(wanbeiyu_touchscreen_init(&ts, (wanbeiyu_rdac_t *)&h, (wanbeiyu_rdac_t *)&v, (wanbeiyu_spst_switch_t *)&sw) == WANBEIYU_OK);

    wanbeiyu_touchscreen_release(&ts);

    test_rdac_state_t actual_h_state = h.state;
    test_rdac_state_t actual_v_state = v.state;
    test_switch_state_t actual_sw_state = sw.state;

    if (actual_h_state != TEST_RDAC_POWER_OFF ||
        actual_v_state != TEST_RDAC_POWER_OFF ||
        actual_sw_state != TEST_SWITCH_OFF)
    {
        fprintf(stderr, "%sindex: %d,\n"
                        "  expected_h_state: %d, actual_h_state: %d,\n"
                        "  expected_v_state: %d, actual_v_state: %d,\n"
                        "  expected_sw_state: %d, actual_sw_state: %d%s\n",
                TEXT_RED, 0,
                TEST_RDAC_POWER_OFF, actual_h_state,
                TEST_RDAC_POWER_OFF, actual_v_state,
                TEST_SWITCH_OFF, actual_sw_state,
                TEXT_RESET);
        cnt++;
    }

    return cnt;
}

int test_touchscreen(void)
{
    printf("* %s\n", __func__);
    int cnt = 0;

    cnt += test_touchscreen_init();
    cnt += test_touchscreen_hold();
    cnt += test_touchscreen_release();

    return cnt;
}

#endif // TEST_TOUCHSCREEN_H_