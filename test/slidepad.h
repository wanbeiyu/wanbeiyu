#ifndef TEST_SLIDEPAD_H_
#define TEST_SLIDEPAD_H_

#include "wanbeiyu.h"
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
        test_idac_t *h;
        test_idac_t *v;

        wanbeiyu_error_t expected_ret;
    } test_case_t;

    wanbeiyu_slidepad_t sp[8];
    test_idac_t h[8];
    test_idac_t v[8];
    for (size_t i = 0; i < 8; i++)
    {
        test_idac_init(&h[i]);
        test_idac_init(&v[i]);
    }

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
        if (actual_ret != WANBEIYU_OK)
        {
            continue;
        }

        test_idac_state_t actual_h_state = case_.h->state;
        uint8_t actual_h_value = case_.h->value;
        test_idac_state_t actual_v_state = case_.v->state;
        uint8_t actual_v_value = case_.v->value;

        if (actual_h_state != TEST_IDAC_SOURCE ||
            actual_h_value != 0 ||
            actual_v_state != TEST_IDAC_SOURCE ||
            actual_v_value != 0)
        {
            fprintf(stderr, "%sindex: %d,\n"
                            "  expected_h_state: %d, actual_h_state: %d, expected_h_value: %d, actual_h_value: %d,\n"
                            "  expected_v_state: %d, actual_v_state: %d, expected_v_value: %d, actual_v_value: %d%s\n",
                    TEXT_RED, i,
                    TEST_IDAC_SOURCE, actual_h_state, 0, actual_h_value,
                    TEST_IDAC_SOURCE, actual_v_state, 0, actual_v_value,
                    TEXT_RESET);
            cnt++;
        }
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

        test_idac_state_t expected_h_state;
        uint8_t expected_h_value;
        test_idac_state_t expected_v_state;
        uint8_t expected_v_value;
    } test_case_t;

    test_case_t cases[] = {{.x = WANBEIYU_SLIDEPAD_NEUTRAL, .y = WANBEIYU_SLIDEPAD_NEUTRAL, .expected_h_state = TEST_IDAC_SOURCE, /**/ .expected_h_value = 0, /*   */ .expected_v_state = TEST_IDAC_SOURCE, /**/ .expected_v_value = 0},
                           {.x = 0, /*                   */ .y = 0, /*                   */ .expected_h_state = TEST_IDAC_SOURCE, /**/ .expected_h_value = UINT8_MAX, .expected_v_state = TEST_IDAC_SOURCE, /**/ .expected_v_value = UINT8_MAX},
                           {.x = UINT8_MAX, /*           */ .y = UINT8_MAX, /*           */ .expected_h_state = TEST_IDAC_SINK, /*  */ .expected_h_value = UINT8_MAX, .expected_v_state = TEST_IDAC_SINK, /*  */ .expected_v_value = UINT8_MAX}};

    wanbeiyu_slidepad_t *sp_null = NULL;
    wanbeiyu_slidepad_hold(sp_null, 0, 0); /* Expected that nothing will happen. */

    TEST_FOR(cases)
    {
        test_idac_t h;
        test_idac_init(&h);
        test_idac_t v;
        test_idac_init(&v);
        wanbeiyu_slidepad_t sp;
        assert(wanbeiyu_slidepad_init(&sp, (wanbeiyu_idac_t *)&h, (wanbeiyu_idac_t *)&v) == WANBEIYU_OK);

        wanbeiyu_slidepad_hold(&sp, case_.x, case_.y);

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
                            "  expected_h_state: %d, actual_h_state: %d, expected_h_value: %d, actual_h_value: %d,\n"
                            "  expected_v_state: %d, actual_v_state: %d, expected_v_value: %d, actual_v_value: %d%s\n",
                    TEXT_RED, i,
                    case_.expected_h_state, actual_h_state, case_.expected_h_value, actual_h_value,
                    case_.expected_v_state, actual_v_state, case_.expected_v_value, actual_v_value,
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

    wanbeiyu_slidepad_t *sp_null = NULL;
    wanbeiyu_slidepad_release(sp_null); /* Expected that nothing will happen. */

    test_idac_t h;
    test_idac_init(&h);
    test_idac_t v;
    test_idac_init(&v);
    wanbeiyu_slidepad_t sp;
    assert(wanbeiyu_slidepad_init(&sp, (wanbeiyu_idac_t *)&h, (wanbeiyu_idac_t *)&v) == WANBEIYU_OK);

    wanbeiyu_slidepad_release(&sp);

    if (h.state != TEST_IDAC_SOURCE ||
        h.value != 0 ||
        v.state != TEST_IDAC_SOURCE ||
        v.value != 0)
    {
        fprintf(stderr, "%sindex: %d,\n"
                        "  expected_h_state: %d, actual_h_state: %d, expected_h_value: %d, actual_h_value: %d,\n"
                        "  expected_v_state: %d, actual_v_state: %d, expected_v_value: %d, actual_v_value: %d%s\n",
                TEXT_RED, 0,
                TEST_IDAC_SOURCE, h.state, 0, h.value,
                TEST_IDAC_SOURCE, v.state, 0, v.value,
                TEXT_RESET);
        cnt++;
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