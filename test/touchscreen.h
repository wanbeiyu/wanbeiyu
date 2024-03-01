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

    typedef struct TestCase
    {
        WanbeiyuTouchscreen *ts;
        WanbeiyuRDAC *horizontal;
        WanbeiyuRDAC *vertical;
        WanbeiyuSPSTSwitch *switch_;

        WanbeiyuErrNo expected_ret;
    } TestCase;

    WanbeiyuTouchscreen ts[16];
    WanbeiyuRDAC horizontal[16];
    WanbeiyuRDAC vertical[16];
    WanbeiyuSPSTSwitch switch_[16];

    TestCase cases[] = {{.ts = NULL, /*   */ .horizontal = NULL, /*           */ .vertical = NULL, /*         */ .switch_ = NULL, /*        */ .expected_ret = WANBEIYU_EINVAL},
                        {.ts = &ts[1], /* */ .horizontal = NULL, /*           */ .vertical = NULL, /*         */ .switch_ = NULL, /*        */ .expected_ret = WANBEIYU_EINVAL},
                        {.ts = NULL, /*   */ .horizontal = &horizontal[2], /* */ .vertical = NULL, /*         */ .switch_ = NULL, /*        */ .expected_ret = WANBEIYU_EINVAL},
                        {.ts = &ts[3], /* */ .horizontal = &horizontal[3], /* */ .vertical = NULL, /*         */ .switch_ = NULL, /*        */ .expected_ret = WANBEIYU_EINVAL},
                        {.ts = NULL, /*   */ .horizontal = NULL, /*           */ .vertical = &vertical[4], /* */ .switch_ = NULL, /*        */ .expected_ret = WANBEIYU_EINVAL},
                        {.ts = &ts[5], /* */ .horizontal = NULL, /*           */ .vertical = &vertical[5], /* */ .switch_ = NULL, /*        */ .expected_ret = WANBEIYU_EINVAL},
                        {.ts = NULL, /*   */ .horizontal = &horizontal[6], /* */ .vertical = &vertical[6], /* */ .switch_ = NULL, /*        */ .expected_ret = WANBEIYU_EINVAL},
                        {.ts = &ts[7], /* */ .horizontal = &horizontal[7], /* */ .vertical = &vertical[7], /* */ .switch_ = NULL, /*        */ .expected_ret = WANBEIYU_EINVAL},
                        {.ts = NULL, /*   */ .horizontal = NULL, /*           */ .vertical = NULL, /*         */ .switch_ = &switch_[8], /* */ .expected_ret = WANBEIYU_EINVAL},
                        {.ts = &ts[9], /* */ .horizontal = NULL, /*           */ .vertical = NULL, /*         */ .switch_ = &switch_[9], /* */ .expected_ret = WANBEIYU_EINVAL},
                        {.ts = NULL, /*   */ .horizontal = &horizontal[10], /**/ .vertical = NULL, /*         */ .switch_ = &switch_[10], /**/ .expected_ret = WANBEIYU_EINVAL},
                        {.ts = &ts[11], /**/ .horizontal = &horizontal[11], /**/ .vertical = NULL, /*         */ .switch_ = &switch_[11], /**/ .expected_ret = WANBEIYU_EINVAL},
                        {.ts = NULL, /*   */ .horizontal = NULL, /*           */ .vertical = &vertical[12], /**/ .switch_ = &switch_[12], /**/ .expected_ret = WANBEIYU_EINVAL},
                        {.ts = &ts[13], /**/ .horizontal = NULL, /*           */ .vertical = &vertical[13], /**/ .switch_ = &switch_[13], /**/ .expected_ret = WANBEIYU_EINVAL},
                        {.ts = NULL, /*   */ .horizontal = &horizontal[14], /**/ .vertical = &vertical[14], /**/ .switch_ = &switch_[14], /**/ .expected_ret = WANBEIYU_EINVAL},
                        {.ts = &ts[15], /**/ .horizontal = &horizontal[15], /**/ .vertical = &vertical[15], /**/ .switch_ = &switch_[15], /**/ .expected_ret = WANBEIYU_OK}};

    TEST_FOR(cases)
    {
        WanbeiyuErrNo actual_ret = wanbeiyu_touchscreen_init(case_.ts, (WanbeiyuRDAC *)case_.horizontal, (WanbeiyuRDAC *)case_.vertical, (WanbeiyuSPSTSwitch *)case_.switch_);
        TEST_ASSERT_EQUAL_WANBEIYU_ERROR_RET(case_.expected_ret, actual_ret);
    }

    return cnt;
}

int test_touchscreen_hold(void)
{
    printf("  * %s\n", __func__);
    int cnt = 0;

    typedef struct TestCase
    {
        uint16_t x;
        uint8_t y;

        WanbeiyuErrNo expected_ret;
        uint16_t expected_horizontal_position;
        uint16_t expected_vertical_position;
        TestSwitchState expected_switch_state;
    } TestCase;

    TestCase cases[] = {{.x = 0, /*                    */ .y = 0, /*                    */ .expected_ret = WANBEIYU_OK, .expected_horizontal_position = 0, /*         */ .expected_vertical_position = 0, /*         */ .expected_switch_state = TEST_SWITCH_ON},
                        {.x = 160, /*                  */ .y = 120, /*                  */ .expected_ret = WANBEIYU_OK, .expected_horizontal_position = TEST_UINT16_MID, .expected_vertical_position = TEST_UINT16_MID, .expected_switch_state = TEST_SWITCH_ON},
                        {.x = WANBEIYU_TOUCHSCREEN_X_MAX, .y = WANBEIYU_TOUCHSCREEN_Y_MAX, .expected_ret = WANBEIYU_OK, .expected_horizontal_position = UINT16_MAX, /**/ .expected_vertical_position = UINT16_MAX, /**/ .expected_switch_state = TEST_SWITCH_ON},
                        {.x = 320, /*                  */ .y = 0, /*                    */ .expected_ret = WANBEIYU_EINVAL},
                        {.x = 0, /*                    */ .y = 240, /*                  */ .expected_ret = WANBEIYU_EINVAL},
                        {.x = 320, /*                  */ .y = 240, /*                  */ .expected_ret = WANBEIYU_EINVAL}};

    TEST_FOR(cases)
    {
        WanbeiyuTouchscreen *ts_null = NULL;
        WanbeiyuErrNo actual_ret = wanbeiyu_touchscreen_hold(ts_null, case_.x, case_.y);
        TEST_ASSERT_EQUAL_WANBEIYU_ERROR_RET(WANBEIYU_EINVAL, actual_ret);

        WanbeiyuTouchscreen ts;
        TestRDAC horizontal;
        TestRDAC vertical;
        TestSwitch switch_;
        test_rdac_init(&horizontal);
        test_rdac_init(&vertical);
        test_switch_init(&switch_);
        assert(wanbeiyu_touchscreen_init(&ts, (WanbeiyuRDAC *)&horizontal, (WanbeiyuRDAC *)&vertical, (WanbeiyuSPSTSwitch *)&switch_) == WANBEIYU_OK);

        actual_ret = wanbeiyu_touchscreen_hold(&ts, case_.x, case_.y);
        TEST_ASSERT_EQUAL_WANBEIYU_ERROR_RET(case_.expected_ret, actual_ret);
        if (actual_ret != WANBEIYU_OK)
        {
            continue;
        }

        TestSwitchState actual_switch_state = switch_.state;
        if (actual_switch_state != case_.expected_switch_state)
        {
            fprintf(stderr, "%sindex: %d,\n"
                            "  expected_switch_state: %s, actual_switch_state: %s%s\n",
                    TEXT_RED, i,
                    TEST_SWITCH_STATE(case_.expected_switch_state), TEST_SWITCH_STATE(actual_switch_state),
                    TEXT_RESET);
            cnt++;
            continue;
        }

        uint16_t actual_horizontal_position = horizontal.position;
        uint16_t actual_vertical_position = vertical.position;
        if ((horizontal.position < case_.expected_horizontal_position - TEST_RDAC_TOLERANCE && case_.expected_horizontal_position + TEST_RDAC_TOLERANCE < horizontal.position) ||
            (vertical.position < case_.expected_vertical_position - TEST_RDAC_TOLERANCE && case_.expected_vertical_position + TEST_RDAC_TOLERANCE < vertical.position))
        {
            fprintf(stderr, "%sindex: %d,\n"
                            "  expected_horizontal_position: %d, actual_horizontal_position: %d,\n"
                            "  expected_vertical_position: %d, actual_vertical_position: %d%s\n",
                    TEXT_RED, i,
                    case_.expected_horizontal_position, actual_horizontal_position,
                    case_.expected_vertical_position, actual_vertical_position,
                    TEXT_RESET);
            cnt++;
        }
    }

    return cnt;
}

int test_touchscreen_release(void)
{
    printf("  * %s\n", __func__);
    int cnt = 0;

    typedef struct TestCase
    {
        WanbeiyuErrNo expected_ret;
        TestSwitchState expected_switch_state;
    } TestCase;

    TestCase cases[] = {{.expected_ret = WANBEIYU_OK, .expected_switch_state = TEST_SWITCH_OFF}};

    TEST_FOR(cases)
    {
        WanbeiyuTouchscreen *ts_null = NULL;
        WanbeiyuErrNo actual_ret = wanbeiyu_touchscreen_release(ts_null);
        TEST_ASSERT_EQUAL_WANBEIYU_ERROR_RET(WANBEIYU_EINVAL, actual_ret);

        WanbeiyuTouchscreen ts;
        TestRDAC horizontal;
        TestRDAC vertical;
        TestSwitch switch_;
        test_rdac_init(&horizontal);
        test_rdac_init(&vertical);
        test_switch_init(&switch_);
        assert(wanbeiyu_touchscreen_init(&ts, (WanbeiyuRDAC *)&horizontal, (WanbeiyuRDAC *)&vertical, (WanbeiyuSPSTSwitch *)&switch_) == WANBEIYU_OK);

        actual_ret = wanbeiyu_touchscreen_release(&ts);
        TEST_ASSERT_EQUAL_WANBEIYU_ERROR_RET(case_.expected_ret, actual_ret);
        if (actual_ret != WANBEIYU_OK)
        {
            continue;
        }

        TestSwitchState actual_switch_state = switch_.state;
        if (actual_switch_state != case_.expected_switch_state)
        {
            fprintf(stderr, "%sindex: %d,\n"
                            "  expected_switch_state: %s, actual_switch_state: %s%s\n",
                    TEXT_RED, i,
                    TEST_SWITCH_STATE(case_.expected_switch_state), TEST_SWITCH_STATE(actual_switch_state),
                    TEXT_RESET);
            cnt++;
        }
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