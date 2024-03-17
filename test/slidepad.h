#ifndef TEST_SLIDEPAD_H
#define TEST_SLIDEPAD_H

#include <wanbeiyu/slidepad.h>
#include "test.h"

#include <assert.h>
#include <stdio.h>

int test_slidepad_init(void)
{
    typedef struct TestCase
    {
        WanbeiyuSlidepad *sp;
        WanbeiyuIDAC *horizontal;
        WanbeiyuIDAC *vertical;

        errno_t expected_err;
    } TestCase;

    WanbeiyuSlidepad sp[8];
    WanbeiyuIDAC horizontal[8];
    WanbeiyuIDAC vertical[8];

    TestCase TEST_CASES[] = {{.sp = NULL, /*  */ .horizontal = NULL, /*          */ .vertical = NULL, /*        */ .expected_err = EINVAL},
                             {.sp = &sp[1], /**/ .horizontal = NULL, /*          */ .vertical = NULL, /*        */ .expected_err = EINVAL},
                             {.sp = NULL, /*  */ .horizontal = &horizontal[2], /**/ .vertical = NULL, /*        */ .expected_err = EINVAL},
                             {.sp = &sp[3], /**/ .horizontal = &horizontal[3], /**/ .vertical = NULL, /*        */ .expected_err = EINVAL},
                             {.sp = NULL, /*  */ .horizontal = NULL, /*          */ .vertical = &vertical[4], /**/ .expected_err = EINVAL},
                             {.sp = &sp[5], /**/ .horizontal = NULL, /*          */ .vertical = &vertical[5], /**/ .expected_err = EINVAL},
                             {.sp = NULL, /*  */ .horizontal = &horizontal[6], /**/ .vertical = &vertical[6], /**/ .expected_err = EINVAL},
                             {.sp = &sp[7], /**/ .horizontal = &horizontal[7], /**/ .vertical = &vertical[7], /**/ .expected_err = 0}};

    TEST_FOR(TEST_CASES)
    {
        errno_t actual_err = wanbeiyu_slidepad_init(TEST_CASE->sp, (WanbeiyuIDAC *)TEST_CASE->horizontal, (WanbeiyuIDAC *)TEST_CASE->vertical);
        TEST_ASSERT_EQUAL_ERRNO_T(TEST_CASE->expected_err, actual_err);
    }

    return TEST_COUNT;
}

int test_slidepad_hold(void)
{
    typedef struct TestCase
    {
        WanbeiyuSlidepad *sp;
        uint8_t x;
        uint8_t y;

        errno_t expected_err;
        TestIDACState expected_horizontal_state;
        uint8_t expected_horizontal_value;
        TestIDACState expected_vertical_state;
        uint8_t expected_vertical_value;
    } TestCase;

    WanbeiyuSlidepad sp[4];
    TestIDAC horizontal[4];
    TestIDAC vertical[4];
    for (size_t i = 0; i < 4; i++)
    {
        test_idac_init(&horizontal[i]);
        test_idac_init(&vertical[i]);
        assert(wanbeiyu_slidepad_init(&sp[i], (WanbeiyuIDAC *)&horizontal[i], (WanbeiyuIDAC *)&vertical[i]) == 0);
    }

    TestCase TEST_CASES[] = {{.sp = NULL, /*  */ .x = 0, /*                        */ .y = 0, /*                        */ .expected_err = EINVAL},
                             {.sp = &sp[1], /**/ .x = WANBEIYU_SLIDEPAD_AXIS_NEUTRAL, .y = WANBEIYU_SLIDEPAD_AXIS_NEUTRAL, .expected_err = 0, .expected_horizontal_state = TEST_IDAC_SOURCE, /**/ .expected_horizontal_value = 0, /*   */ .expected_vertical_state = TEST_IDAC_SOURCE, /**/ .expected_vertical_value = 0},
                             {.sp = &sp[2], /**/ .x = 0, /*                        */ .y = 0, /*                        */ .expected_err = 0, .expected_horizontal_state = TEST_IDAC_SOURCE, /**/ .expected_horizontal_value = UINT8_MAX, .expected_vertical_state = TEST_IDAC_SOURCE, /**/ .expected_vertical_value = UINT8_MAX},
                             {.sp = &sp[3], /**/ .x = UINT8_MAX, /*                */ .y = UINT8_MAX, /*                */ .expected_err = 0, .expected_horizontal_state = TEST_IDAC_SINK, /*  */ .expected_horizontal_value = UINT8_MAX, .expected_vertical_state = TEST_IDAC_SINK, /*  */ .expected_vertical_value = UINT8_MAX}};

    TEST_FOR(TEST_CASES)
    {
        errno_t actual_err = wanbeiyu_slidepad_hold(TEST_CASE->sp, TEST_CASE->x, TEST_CASE->y);
        TEST_ASSERT_EQUAL_ERRNO_T(TEST_CASE->expected_err, actual_err);
        if (actual_err != 0)
        {
            continue;
        }

        TestIDACState actual_horizontal_state = horizontal[TEST_INDEX].state;
        TEST_ASSERT_EQUAL_TEST_IDAC_STATE(TEST_CASE->expected_horizontal_state, actual_horizontal_state);

        uint8_t actual_horizontal_value = horizontal[TEST_INDEX].value;
        TEST_ASSERT_EQUAL_INT(TEST_CASE->expected_horizontal_value, actual_horizontal_value);

        TestIDACState actual_vertical_state = vertical[TEST_INDEX].state;
        TEST_ASSERT_EQUAL_TEST_IDAC_STATE(TEST_CASE->expected_horizontal_state, actual_horizontal_state);

        uint8_t actual_vertical_value = vertical[TEST_INDEX].value;
        TEST_ASSERT_EQUAL_INT(TEST_CASE->expected_horizontal_value, actual_horizontal_value);
    }

    return TEST_COUNT;
}

int test_slidepad_release(void)
{
    typedef struct TestCase
    {
        WanbeiyuSlidepad *sp;

        errno_t expected_err;
        TestIDACState expected_horizontal_state;
        uint8_t expected_horizontal_value;
        TestIDACState expected_vertical_state;
        uint8_t expected_vertical_value;
    } TestCase;

    WanbeiyuSlidepad sp[2];
    TestIDAC horizontal[2];
    TestIDAC vertical[2];
    for (size_t i = 0; i < 2; i++)
    {
        test_idac_init(&horizontal[i]);
        test_idac_init(&vertical[i]);
        assert(wanbeiyu_slidepad_init(&sp[i], (WanbeiyuIDAC *)&horizontal[i], (WanbeiyuIDAC *)&vertical[i]) == 0);
    }

    TestCase TEST_CASES[] = {{.sp = NULL, /*  */ .expected_err = EINVAL},
                             {.sp = &sp[1], /**/ .expected_err = 0, .expected_horizontal_state = TEST_IDAC_SOURCE, .expected_horizontal_value = 0, .expected_vertical_state = TEST_IDAC_SOURCE, .expected_vertical_value = 0}};

    TEST_FOR(TEST_CASES)
    {
        errno_t actual_err = wanbeiyu_slidepad_release(TEST_CASE->sp);
        TEST_ASSERT_EQUAL_ERRNO_T(TEST_CASE->expected_err, actual_err);
        if (actual_err != 0)
        {
            continue;
        }

        TestIDACState actual_horizontal_state = horizontal[TEST_INDEX].state;
        TEST_ASSERT_EQUAL_TEST_IDAC_STATE(TEST_CASE->expected_horizontal_state, actual_horizontal_state);

        uint8_t actual_horizontal_value = horizontal[TEST_INDEX].value;
        TEST_ASSERT_EQUAL_INT(TEST_CASE->expected_horizontal_value, actual_horizontal_value);

        TestIDACState actual_vertical_state = vertical[TEST_INDEX].state;
        TEST_ASSERT_EQUAL_TEST_IDAC_STATE(TEST_CASE->expected_horizontal_state, actual_horizontal_state);

        uint8_t actual_vertical_value = vertical[TEST_INDEX].value;
        TEST_ASSERT_EQUAL_INT(TEST_CASE->expected_horizontal_value, actual_horizontal_value);
    }

    return TEST_COUNT;
}

int test_slidepad(void)
{
    int count = 0;

    count += test_slidepad_init();
    count += test_slidepad_hold();
    count += test_slidepad_release();

    return count;
}

#endif // TEST_SLIDEPAD_H