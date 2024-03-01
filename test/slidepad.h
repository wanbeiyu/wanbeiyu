#ifndef TEST_SLIDEPAD_H_
#define TEST_SLIDEPAD_H_

#include <wanbeiyu.h>
#include "test.h"

#include <assert.h>
#include <stdio.h>

int test_slidepad_init(void)
{
    printf("  * %s\n", __func__);
    int cnt = 0;

    typedef struct TestCase
    {
        WanbeiyuSlidepad *sp;
        WanbeiyuIDAC *horizontal;
        WanbeiyuIDAC *vertical;

        WanbeiyuErrNo expected_ret;
    } TestCase;

    WanbeiyuSlidepad sp[8];
    WanbeiyuIDAC horizontal[8];
    WanbeiyuIDAC vertical[8];

    TestCase cases[] = {{.sp = NULL, /*  */ .horizontal = NULL, /*          */ .vertical = NULL, /*        */ .expected_ret = WANBEIYU_EINVAL},
                        {.sp = &sp[1], /**/ .horizontal = NULL, /*          */ .vertical = NULL, /*        */ .expected_ret = WANBEIYU_EINVAL},
                        {.sp = NULL, /*  */ .horizontal = &horizontal[2], /**/ .vertical = NULL, /*        */ .expected_ret = WANBEIYU_EINVAL},
                        {.sp = &sp[3], /**/ .horizontal = &horizontal[3], /**/ .vertical = NULL, /*        */ .expected_ret = WANBEIYU_EINVAL},
                        {.sp = NULL, /*  */ .horizontal = NULL, /*          */ .vertical = &vertical[4], /**/ .expected_ret = WANBEIYU_EINVAL},
                        {.sp = &sp[5], /**/ .horizontal = NULL, /*          */ .vertical = &vertical[5], /**/ .expected_ret = WANBEIYU_EINVAL},
                        {.sp = NULL, /*  */ .horizontal = &horizontal[6], /**/ .vertical = &vertical[6], /**/ .expected_ret = WANBEIYU_EINVAL},
                        {.sp = &sp[7], /**/ .horizontal = &horizontal[7], /**/ .vertical = &vertical[7], /**/ .expected_ret = WANBEIYU_OK}};

    TEST_FOR(cases)
    {
        WanbeiyuErrNo actual_ret = wanbeiyu_slidepad_init(case_.sp, (WanbeiyuIDAC *)case_.horizontal, (WanbeiyuIDAC *)case_.vertical);
        TEST_ASSERT_EQUAL_WANBEIYU_ERROR_RET(case_.expected_ret, actual_ret);
    }

    return cnt;
}

int test_slidepad_hold(void)
{
    printf("  * %s\n", __func__);
    int cnt = 0;

    typedef struct TestCase
    {
        uint8_t x;
        uint8_t y;

        WanbeiyuErrNo expected_ret;
        TestIDACState expected_horizontal_state;
        uint8_t expected_horizontal_value;
        TestIDACState expected_vertical_state;
        uint8_t expected_vertical_value;
    } TestCase;

    TestCase cases[] = {{.x = WANBEIYU_SLIDEPAD_AXIS_NEUTRAL, .y = WANBEIYU_SLIDEPAD_AXIS_NEUTRAL, .expected_ret = WANBEIYU_OK, .expected_horizontal_state = TEST_IDAC_SOURCE, /**/ .expected_horizontal_value = 0, /*   */ .expected_vertical_state = TEST_IDAC_SOURCE, /**/ .expected_vertical_value = 0},
                        {.x = 0, /*                        */ .y = 0, /*                        */ .expected_ret = WANBEIYU_OK, .expected_horizontal_state = TEST_IDAC_SOURCE, /**/ .expected_horizontal_value = UINT8_MAX, .expected_vertical_state = TEST_IDAC_SOURCE, /**/ .expected_vertical_value = UINT8_MAX},
                        {.x = UINT8_MAX, /*                */ .y = UINT8_MAX, /*                */ .expected_ret = WANBEIYU_OK, .expected_horizontal_state = TEST_IDAC_SINK, /*  */ .expected_horizontal_value = UINT8_MAX, .expected_vertical_state = TEST_IDAC_SINK, /*  */ .expected_vertical_value = UINT8_MAX}};

    TEST_FOR(cases)
    {
        WanbeiyuSlidepad *sp_null = NULL;
        WanbeiyuErrNo actual_ret = wanbeiyu_slidepad_hold(sp_null, case_.x, case_.y);
        TEST_ASSERT_EQUAL_WANBEIYU_ERROR_RET(WANBEIYU_EINVAL, actual_ret);

        WanbeiyuSlidepad sp;
        TestIDAC horizontal;
        TestIDAC vertical;
        test_idac_init(&horizontal);
        test_idac_init(&vertical);
        assert(wanbeiyu_slidepad_init(&sp, (WanbeiyuIDAC *)&horizontal, (WanbeiyuIDAC *)&vertical) == WANBEIYU_OK);

        actual_ret = wanbeiyu_slidepad_hold(&sp, case_.x, case_.y);
        TEST_ASSERT_EQUAL_WANBEIYU_ERROR_RET(case_.expected_ret, actual_ret);
        if (actual_ret != WANBEIYU_OK)
        {
            continue;
        }

        TestIDACState actual_horizontal_state = horizontal.state;
        uint8_t actual_horizontal_value = horizontal.value;
        TestIDACState actual_vertical_state = vertical.state;
        uint8_t actual_vertical_value = vertical.value;
        if (actual_horizontal_state != case_.expected_horizontal_state ||
            actual_horizontal_value != case_.expected_horizontal_value ||
            actual_vertical_state != case_.expected_vertical_state ||
            actual_vertical_value != case_.expected_vertical_value)
        {
            fprintf(stderr, "%sindex: %d,\n"
                            "  expected_horizontal_state: %s, actual_horizontal_state: %s,\n"
                            "  expected_horizontal_value: %d, actual_horizontal_value: %d,\n"
                            "  expected_vertical_state: %s, actual_vertical_state: %s,\n"
                            "  expected_vertical_value: %d, actual_vertical_value: %d%s\n",
                    TEXT_RED, i,
                    TEST_IDAC_STATE(case_.expected_horizontal_state), TEST_IDAC_STATE(actual_horizontal_state),
                    case_.expected_horizontal_value, actual_horizontal_value,
                    TEST_IDAC_STATE(case_.expected_vertical_state), TEST_IDAC_STATE(actual_vertical_state),
                    case_.expected_vertical_value, actual_vertical_value,
                    TEXT_RESET);
            cnt++;
        }
    }

    return cnt;
}

int test_slidepad_release(void)
{
    printf("  * %s\n", __func__);
    int cnt = 0;

    typedef struct TestCase
    {
        WanbeiyuErrNo expected_ret;
        TestIDACState expected_horizontal_state;
        uint8_t expected_horizontal_value;
        TestIDACState expected_vertical_state;
        uint8_t expected_vertical_value;
    } TestCase;

    TestCase cases[] = {{.expected_ret = WANBEIYU_OK, .expected_horizontal_state = TEST_IDAC_SOURCE, .expected_horizontal_value = 0, .expected_vertical_state = TEST_IDAC_SOURCE, .expected_vertical_value = 0}};

    TEST_FOR(cases)
    {
        WanbeiyuSlidepad *sp_null = NULL;
        WanbeiyuErrNo actual_ret = wanbeiyu_slidepad_release(sp_null);
        TEST_ASSERT_EQUAL_WANBEIYU_ERROR_RET(WANBEIYU_EINVAL, actual_ret);

        WanbeiyuSlidepad sp;
        TestIDAC horizontal;
        TestIDAC vertical;
        test_idac_init(&horizontal);
        test_idac_init(&vertical);
        assert(wanbeiyu_slidepad_init(&sp, (WanbeiyuIDAC *)&horizontal, (WanbeiyuIDAC *)&vertical) == WANBEIYU_OK);

        actual_ret = wanbeiyu_slidepad_release(&sp);
        TEST_ASSERT_EQUAL_WANBEIYU_ERROR_RET(case_.expected_ret, actual_ret);
        if (actual_ret != WANBEIYU_OK)
        {
            continue;
        }

        TestIDACState actual_horizontal_state = horizontal.state;
        uint8_t actual_horizontal_value = horizontal.value;
        TestIDACState actual_vertical_state = vertical.state;
        uint8_t actual_vertical_value = vertical.value;
        if (actual_horizontal_state != case_.expected_horizontal_state ||
            actual_horizontal_value != case_.expected_horizontal_value ||
            actual_vertical_state != case_.expected_vertical_state ||
            actual_vertical_value != case_.expected_vertical_value)
        {
            fprintf(stderr, "%sindex: %d,\n"
                            "  expected_horizontal_state: %s, actual_horizontal_state: %s,\n"
                            "  expected_horizontal_value: %d, actual_horizontal_value: %d,\n"
                            "  expected_vertical_state: %s, actual_vertical_state: %s,\n"
                            "  expected_vertical_value: %d, actual_vertical_value: %d%s\n",
                    TEXT_RED, i,
                    TEST_IDAC_STATE(case_.expected_horizontal_state), TEST_IDAC_STATE(actual_horizontal_state),
                    case_.expected_horizontal_value, actual_horizontal_value,
                    TEST_IDAC_STATE(case_.expected_vertical_state), TEST_IDAC_STATE(actual_vertical_state),
                    case_.expected_vertical_value, actual_vertical_value,
                    TEXT_RESET);
            cnt++;
        }
    }

    return cnt;
}

int test_slidepad(void)
{
    printf("* %s\n", __func__);
    int cnt = 0;

    cnt += test_slidepad_init();
    cnt += test_slidepad_hold();
    cnt += test_slidepad_release();

    return cnt;
}

#endif // TEST_SLIDEPAD_H_