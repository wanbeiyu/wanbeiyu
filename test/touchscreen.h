#ifndef TEST_TOUCHSCREEN_H
#define TEST_TOUCHSCREEN_H

#include <wanbeiyu/touchscreen.h>
#include "test.h"

#include <assert.h>
#include <stdio.h>

int test_touchscreen_init(void)
{
    typedef struct TestCase
    {
        WanbeiyuTouchscreen *ts;
        WanbeiyuRDAC *horizontal;
        WanbeiyuRDAC *vertical;
        WanbeiyuSPSTSwitch *switch_;

        errno_t expected_err;
    } TestCase;

    WanbeiyuTouchscreen ts[16];
    WanbeiyuRDAC horizontal[16];
    WanbeiyuRDAC vertical[16];
    WanbeiyuSPSTSwitch switch_[16];

    TestCase TEST_CASES[] = {{.ts = NULL, /*   */ .horizontal = NULL, /*           */ .vertical = NULL, /*         */ .switch_ = NULL, /*        */ .expected_err = EINVAL},
                             {.ts = &ts[1], /* */ .horizontal = NULL, /*           */ .vertical = NULL, /*         */ .switch_ = NULL, /*        */ .expected_err = EINVAL},
                             {.ts = NULL, /*   */ .horizontal = &horizontal[2], /* */ .vertical = NULL, /*         */ .switch_ = NULL, /*        */ .expected_err = EINVAL},
                             {.ts = &ts[3], /* */ .horizontal = &horizontal[3], /* */ .vertical = NULL, /*         */ .switch_ = NULL, /*        */ .expected_err = EINVAL},
                             {.ts = NULL, /*   */ .horizontal = NULL, /*           */ .vertical = &vertical[4], /* */ .switch_ = NULL, /*        */ .expected_err = EINVAL},
                             {.ts = &ts[5], /* */ .horizontal = NULL, /*           */ .vertical = &vertical[5], /* */ .switch_ = NULL, /*        */ .expected_err = EINVAL},
                             {.ts = NULL, /*   */ .horizontal = &horizontal[6], /* */ .vertical = &vertical[6], /* */ .switch_ = NULL, /*        */ .expected_err = EINVAL},
                             {.ts = &ts[7], /* */ .horizontal = &horizontal[7], /* */ .vertical = &vertical[7], /* */ .switch_ = NULL, /*        */ .expected_err = EINVAL},
                             {.ts = NULL, /*   */ .horizontal = NULL, /*           */ .vertical = NULL, /*         */ .switch_ = &switch_[8], /* */ .expected_err = EINVAL},
                             {.ts = &ts[9], /* */ .horizontal = NULL, /*           */ .vertical = NULL, /*         */ .switch_ = &switch_[9], /* */ .expected_err = EINVAL},
                             {.ts = NULL, /*   */ .horizontal = &horizontal[10], /**/ .vertical = NULL, /*         */ .switch_ = &switch_[10], /**/ .expected_err = EINVAL},
                             {.ts = &ts[11], /**/ .horizontal = &horizontal[11], /**/ .vertical = NULL, /*         */ .switch_ = &switch_[11], /**/ .expected_err = EINVAL},
                             {.ts = NULL, /*   */ .horizontal = NULL, /*           */ .vertical = &vertical[12], /**/ .switch_ = &switch_[12], /**/ .expected_err = EINVAL},
                             {.ts = &ts[13], /**/ .horizontal = NULL, /*           */ .vertical = &vertical[13], /**/ .switch_ = &switch_[13], /**/ .expected_err = EINVAL},
                             {.ts = NULL, /*   */ .horizontal = &horizontal[14], /**/ .vertical = &vertical[14], /**/ .switch_ = &switch_[14], /**/ .expected_err = EINVAL},
                             {.ts = &ts[15], /**/ .horizontal = &horizontal[15], /**/ .vertical = &vertical[15], /**/ .switch_ = &switch_[15], /**/ .expected_err = 0}};

    TEST_FOR(TEST_CASES)
    {
        errno_t actual_ret = wanbeiyu_touchscreen_init(TEST_CASE->ts, (WanbeiyuRDAC *)TEST_CASE->horizontal, (WanbeiyuRDAC *)TEST_CASE->vertical, (WanbeiyuSPSTSwitch *)TEST_CASE->switch_);
        TEST_ASSERT_EQUAL_ERRNO_T(TEST_CASE->expected_err, actual_ret);
    }

    return TEST_COUNT;
}

int test_touchscreen_hold(void)
{
    typedef struct TestCase
    {
        WanbeiyuTouchscreen *ts;
        uint16_t x;
        uint8_t y;

        errno_t expected_err;
        uint16_t expected_horizontal_position;
        uint16_t expected_vertical_position;
        TestSwitchState expected_switch_state;
    } TestCase;

    WanbeiyuTouchscreen ts[7];
    TestRDAC horizontal[7];
    TestRDAC vertical[7];
    TestSwitch switch_[7];
    for (size_t i = 0; i < 7; i++)
    {
        test_rdac_init(&horizontal[i]);
        test_rdac_init(&vertical[i]);
        test_switch_init(&switch_[i]);
        assert(wanbeiyu_touchscreen_init(&ts[i], (WanbeiyuRDAC *)&horizontal[i], (WanbeiyuRDAC *)&vertical[i], (WanbeiyuSPSTSwitch *)&switch_[i]) == 0);
    }

    TestCase TEST_CASES[] = {{.ts = NULL, /*  */ .x = 0, /*                    */ .y = 0, /*                    */ .expected_err = EINVAL},
                             {.ts = &ts[1], /**/ .x = 0, /*                    */ .y = 0, /*                    */ .expected_err = 0, .expected_horizontal_position = 0, /*         */ .expected_vertical_position = 0, /*         */ .expected_switch_state = TEST_SWITCH_ON},
                             {.ts = &ts[2], /**/ .x = 160, /*                  */ .y = 120, /*                  */ .expected_err = 0, .expected_horizontal_position = TEST_UINT16_MID, .expected_vertical_position = TEST_UINT16_MID, .expected_switch_state = TEST_SWITCH_ON},
                             {.ts = &ts[3], /**/ .x = WANBEIYU_TOUCHSCREEN_X_MAX, .y = WANBEIYU_TOUCHSCREEN_Y_MAX, .expected_err = 0, .expected_horizontal_position = UINT16_MAX, /**/ .expected_vertical_position = UINT16_MAX, /**/ .expected_switch_state = TEST_SWITCH_ON},
                             {.ts = &ts[4], /**/ .x = 320, /*                  */ .y = 0, /*                    */ .expected_err = EINVAL},
                             {.ts = &ts[5], /**/ .x = 0, /*                    */ .y = 240, /*                  */ .expected_err = EINVAL},
                             {.ts = &ts[6], /**/ .x = 320, /*                  */ .y = 240, /*                  */ .expected_err = EINVAL}};

    TEST_FOR(TEST_CASES)
    {
        errno_t actual_err = wanbeiyu_touchscreen_hold(TEST_CASE->ts, TEST_CASE->x, TEST_CASE->y);
        TEST_ASSERT_EQUAL_ERRNO_T(TEST_CASE->expected_err, actual_err);
        if (actual_err != 0)
        {
            continue;
        }

        uint16_t actual_horizontal_position = horizontal[TEST_INDEX].position;
        TEST_ASSERT_EQUAL_WIPER_POSITION(TEST_CASE->expected_horizontal_position, actual_horizontal_position);

        uint16_t actual_vertical_position = vertical[TEST_INDEX].position;
        TEST_ASSERT_EQUAL_WIPER_POSITION(TEST_CASE->expected_horizontal_position, actual_horizontal_position);

        TestSwitchState actual_switch_state = switch_[TEST_INDEX].state;
        TEST_ASSERT_EQUAL_TEST_SWITCH_STATE(TEST_CASE->expected_switch_state, actual_switch_state);
    }

    return TEST_COUNT;
}

int test_touchscreen_release(void)
{
    typedef struct TestCase
    {
        WanbeiyuTouchscreen *ts;

        errno_t expected_err;
        TestSwitchState expected_switch_state;
    } TestCase;

    WanbeiyuTouchscreen ts[2];
    TestRDAC horizontal[2];
    TestRDAC vertical[2];
    TestSwitch switch_[2];
    for (size_t i = 0; i < 2; i++)
    {
        test_rdac_init(&horizontal[i]);
        test_rdac_init(&vertical[i]);
        test_switch_init(&switch_[i]);
        assert(wanbeiyu_touchscreen_init(&ts[i], (WanbeiyuRDAC *)&horizontal[i], (WanbeiyuRDAC *)&vertical[i], (WanbeiyuSPSTSwitch *)&switch_[i]) == 0);
    }

    TestCase TEST_CASES[] = {{.ts = NULL, /*  */ .expected_err = EINVAL},
                             {.ts = &ts[1], /**/ .expected_err = 0, .expected_switch_state = TEST_SWITCH_OFF}};

    TEST_FOR(TEST_CASES)
    {
        errno_t actual_err = wanbeiyu_touchscreen_release(TEST_CASE->ts);
        TEST_ASSERT_EQUAL_ERRNO_T(TEST_CASE->expected_err, actual_err);
        if (actual_err != 0)
        {
            continue;
        }

        TestSwitchState actual_switch_state = switch_[TEST_INDEX].state;
        TEST_ASSERT_EQUAL_TEST_SWITCH_STATE(TEST_CASE->expected_switch_state, actual_switch_state);
    }

    return TEST_COUNT;
}

int test_touchscreen(void)
{
    int count = 0;

    count += test_touchscreen_init();
    count += test_touchscreen_hold();
    count += test_touchscreen_release();

    return count;
}

#endif // TEST_TOUCHSCREEN_H