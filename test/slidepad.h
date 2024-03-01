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

    typedef struct test_case_t
    {
        wanbeiyu_slidepad_t *sp;
        wanbeiyu_idac_t *h;
        wanbeiyu_idac_t *v;

        wanbeiyu_error_t expected_ret;
    } test_case_t;

    wanbeiyu_slidepad_t sp[8];
    wanbeiyu_idac_t h[8];
    wanbeiyu_idac_t v[8];

    test_case_t cases[] = {{.sp = NULL, /*  */ .h = NULL, /* */ .v = NULL, /* */ .expected_ret = WANBEIYU_EINVAL},
                           {.sp = &sp[1], /**/ .h = NULL, /* */ .v = NULL, /* */ .expected_ret = WANBEIYU_EINVAL},
                           {.sp = NULL, /*  */ .h = &h[2], /**/ .v = NULL, /* */ .expected_ret = WANBEIYU_EINVAL},
                           {.sp = &sp[3], /**/ .h = &h[3], /**/ .v = NULL, /* */ .expected_ret = WANBEIYU_EINVAL},
                           {.sp = NULL, /*  */ .h = NULL, /* */ .v = &v[4], /**/ .expected_ret = WANBEIYU_EINVAL},
                           {.sp = &sp[5], /**/ .h = NULL, /* */ .v = &v[5], /**/ .expected_ret = WANBEIYU_EINVAL},
                           {.sp = NULL, /*  */ .h = &h[6], /**/ .v = &v[6], /**/ .expected_ret = WANBEIYU_EINVAL},
                           {.sp = &sp[7], /**/ .h = &h[7], /**/ .v = &v[7], /**/ .expected_ret = WANBEIYU_OK}};

    TEST_FOR(cases)
    {
        wanbeiyu_error_t actual_ret = wanbeiyu_slidepad_init(case_.sp, (wanbeiyu_idac_t *)case_.h, (wanbeiyu_idac_t *)case_.v);
        TEST_ASSERT_EQUAL_WANBEIYU_ERROR_RET(case_.expected_ret, actual_ret);
    }

    return cnt;
}

int test_slidepad_hold(void)
{
    printf("  * %s\n", __func__);
    int cnt = 0;

    typedef struct test_case_t
    {
        uint8_t x;
        uint8_t y;

        wanbeiyu_error_t expected_ret;
        test_idac_state_t expected_h_state;
        uint8_t expected_h_value;
        test_idac_state_t expected_v_state;
        uint8_t expected_v_value;
    } test_case_t;

    test_case_t cases[] = {{.x = WANBEIYU_SLIDEPAD_NEUTRAL, .y = WANBEIYU_SLIDEPAD_NEUTRAL, .expected_ret = WANBEIYU_OK, .expected_h_state = TEST_IDAC_SOURCE, /**/ .expected_h_value = 0, /*   */ .expected_v_state = TEST_IDAC_SOURCE, /**/ .expected_v_value = 0},
                           {.x = 0, /*                   */ .y = 0, /*                   */ .expected_ret = WANBEIYU_OK, .expected_h_state = TEST_IDAC_SOURCE, /**/ .expected_h_value = UINT8_MAX, .expected_v_state = TEST_IDAC_SOURCE, /**/ .expected_v_value = UINT8_MAX},
                           {.x = UINT8_MAX, /*           */ .y = UINT8_MAX, /*           */ .expected_ret = WANBEIYU_OK, .expected_h_state = TEST_IDAC_SINK, /*  */ .expected_h_value = UINT8_MAX, .expected_v_state = TEST_IDAC_SINK, /*  */ .expected_v_value = UINT8_MAX}};

    TEST_FOR(cases)
    {
        wanbeiyu_slidepad_t *sp_null = NULL;
        wanbeiyu_error_t actual_ret = wanbeiyu_slidepad_hold(sp_null, case_.x, case_.y);
        TEST_ASSERT_EQUAL_WANBEIYU_ERROR_RET(WANBEIYU_EINVAL, actual_ret);

        wanbeiyu_slidepad_t sp;
        test_idac_t h;
        test_idac_t v;
        test_idac_init(&h);
        test_idac_init(&v);
        assert(wanbeiyu_slidepad_init(&sp, (wanbeiyu_idac_t *)&h, (wanbeiyu_idac_t *)&v) == WANBEIYU_OK);

        actual_ret = wanbeiyu_slidepad_hold(&sp, case_.x, case_.y);
        TEST_ASSERT_EQUAL_WANBEIYU_ERROR_RET(case_.expected_ret, actual_ret);
        if (actual_ret != WANBEIYU_OK)
        {
            continue;
        }

        test_idac_state_t actual_h_state = h.state;
        uint8_t actual_h_value = h.value;
        test_idac_state_t actual_v_state = v.state;
        uint8_t actual_v_value = v.value;
        if (actual_h_state != case_.expected_h_state ||
            actual_h_value != case_.expected_h_value ||
            actual_v_state != case_.expected_v_state ||
            actual_v_value != case_.expected_v_value)
        {
            fprintf(stderr, "%sindex: %d,\n"
                            "  expected_h_state: %s, actual_h_state: %s,\n"
                            "  expected_h_value: %d, actual_h_value: %d,\n"
                            "  expected_v_state: %s, actual_v_state: %s,\n"
                            "  expected_v_value: %d, actual_v_value: %d%s\n",
                    TEXT_RED, i,
                    TEST_IDAC_STATE(case_.expected_h_state), TEST_IDAC_STATE(actual_h_state),
                    case_.expected_h_value, actual_h_value,
                    TEST_IDAC_STATE(case_.expected_v_state), TEST_IDAC_STATE(actual_v_state),
                    case_.expected_v_value, actual_v_value,
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

    typedef struct test_case_t
    {
        wanbeiyu_error_t expected_ret;
        test_idac_state_t expected_h_state;
        uint8_t expected_h_value;
        test_idac_state_t expected_v_state;
        uint8_t expected_v_value;
    } test_case_t;

    test_case_t cases[] = {{.expected_ret = WANBEIYU_OK, .expected_h_state = TEST_IDAC_SOURCE, .expected_h_value = 0, .expected_v_state = TEST_IDAC_SOURCE, .expected_v_value = 0}};

    TEST_FOR(cases)
    {
        wanbeiyu_slidepad_t *sp_null = NULL;
        wanbeiyu_error_t actual_ret = wanbeiyu_slidepad_release(sp_null);
        TEST_ASSERT_EQUAL_WANBEIYU_ERROR_RET(WANBEIYU_EINVAL, actual_ret);

        wanbeiyu_slidepad_t sp;
        test_idac_t h;
        test_idac_t v;
        test_idac_init(&h);
        test_idac_init(&v);
        assert(wanbeiyu_slidepad_init(&sp, (wanbeiyu_idac_t *)&h, (wanbeiyu_idac_t *)&v) == WANBEIYU_OK);

        actual_ret = wanbeiyu_slidepad_release(&sp);
        TEST_ASSERT_EQUAL_WANBEIYU_ERROR_RET(case_.expected_ret, actual_ret);
        if (actual_ret != WANBEIYU_OK)
        {
            continue;
        }

        test_idac_state_t actual_h_state = h.state;
        uint8_t actual_h_value = h.value;
        test_idac_state_t actual_v_state = v.state;
        uint8_t actual_v_value = v.value;
        if (actual_h_state != case_.expected_h_state ||
            actual_h_value != case_.expected_h_value ||
            actual_v_state != case_.expected_v_state ||
            actual_v_value != case_.expected_v_value)
        {
            fprintf(stderr, "%sindex: %d,\n"
                            "  expected_h_state: %s, actual_h_state: %s,\n"
                            "  expected_h_value: %d, actual_h_value: %d,\n"
                            "  expected_v_state: %s, actual_v_state: %s,\n"
                            "  expected_v_value: %d, actual_v_value: %d%s\n",
                    TEXT_RED, i,
                    TEST_IDAC_STATE(case_.expected_h_state), TEST_IDAC_STATE(actual_h_state),
                    case_.expected_h_value, actual_h_value,
                    TEST_IDAC_STATE(case_.expected_v_state), TEST_IDAC_STATE(actual_v_state),
                    case_.expected_v_value, actual_v_value,
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