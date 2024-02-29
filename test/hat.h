#ifndef TEST_HAT_H_
#define TEST_HAT_H_

#include <wanbeiyu.h>
#include "test.h"

#include <assert.h>
#include <stdio.h>

int test_hat_init(void)
{
    printf("  * %s\n", __func__);
    int cnt = 0;

    typedef struct test_case_t
    {
        wanbeiyu_hat_t *hat;
        wanbeiyu_button_t *up;
        wanbeiyu_button_t *right;
        wanbeiyu_button_t *down;
        wanbeiyu_button_t *left;

        wanbeiyu_error_t expected;
    } test_case_t;

    wanbeiyu_hat_t hat[32];
    test_gpio_t gpio_up[32];
    wanbeiyu_button_t up[32];
    test_gpio_t gpio_right[32];
    wanbeiyu_button_t right[32];
    test_gpio_t gpio_down[32];
    wanbeiyu_button_t down[32];
    test_gpio_t gpio_left[32];
    wanbeiyu_button_t left[32];
    for (size_t i = 0; i < 32; i++)
    {
        test_gpio_init(&gpio_up[i]);
        assert(wanbeiyu_button_init(&up[i], (wanbeiyu_gpio_t *)&gpio_up[i]) == WANBEIYU_OK);
        test_gpio_init(&gpio_right[i]);
        assert(wanbeiyu_button_init(&right[i], (wanbeiyu_gpio_t *)&gpio_right[i]) == WANBEIYU_OK);
        test_gpio_init(&gpio_down[i]);
        assert(wanbeiyu_button_init(&down[i], (wanbeiyu_gpio_t *)&gpio_down[i]) == WANBEIYU_OK);
        test_gpio_init(&gpio_left[i]);
        assert(wanbeiyu_button_init(&left[i], (wanbeiyu_gpio_t *)&gpio_left[i]) == WANBEIYU_OK);
    }

    test_case_t cases[] = {{.hat = NULL, /*    */ .up = NULL, /*   */ .right = NULL, /*      */ .down = NULL, /*     */ .left = NULL, /**/ .expected = WANBEIYU_EINVAL},
                           {.hat = &hat[1], /* */ .up = NULL, /*   */ .right = NULL, /*      */ .down = NULL, /*     */ .left = NULL, /**/ .expected = WANBEIYU_EINVAL},
                           {.hat = NULL, /*    */ .up = &up[2], /* */ .right = NULL, /*      */ .down = NULL, /*     */ .left = NULL, /**/ .expected = WANBEIYU_EINVAL},
                           {.hat = &hat[3], /* */ .up = &up[3], /* */ .right = NULL, /*      */ .down = NULL, /*     */ .left = NULL, /**/ .expected = WANBEIYU_EINVAL},
                           {.hat = NULL, /*    */ .up = NULL, /*   */ .right = &right[4], /* */ .down = NULL, /*     */ .left = NULL, /**/ .expected = WANBEIYU_EINVAL},
                           {.hat = &hat[5], /* */ .up = NULL, /*   */ .right = &right[5], /* */ .down = NULL, /*     */ .left = NULL, /**/ .expected = WANBEIYU_EINVAL},
                           {.hat = NULL, /*    */ .up = &up[6], /* */ .right = &right[6], /* */ .down = NULL, /*     */ .left = NULL, /**/ .expected = WANBEIYU_EINVAL},
                           {.hat = &hat[7], /* */ .up = &up[7], /* */ .right = &right[7], /* */ .down = NULL, /*     */ .left = NULL, /**/ .expected = WANBEIYU_EINVAL},
                           {.hat = NULL, /*    */ .up = NULL, /*   */ .right = NULL, /*      */ .down = &down[8], /* */ .left = NULL, /**/ .expected = WANBEIYU_EINVAL},
                           {.hat = &hat[9], /* */ .up = NULL, /*   */ .right = NULL, /*      */ .down = &down[9], /* */ .left = NULL, /**/ .expected = WANBEIYU_EINVAL},
                           {.hat = NULL, /*    */ .up = &up[10], /**/ .right = NULL, /*      */ .down = &down[10], /**/ .left = NULL, /**/ .expected = WANBEIYU_EINVAL},
                           {.hat = &hat[11], /**/ .up = &up[11], /**/ .right = NULL, /*      */ .down = &down[11], /**/ .left = NULL, /**/ .expected = WANBEIYU_EINVAL},
                           {.hat = NULL, /*    */ .up = NULL, /*   */ .right = &right[12], /**/ .down = &down[12], /**/ .left = NULL, /**/ .expected = WANBEIYU_EINVAL},
                           {.hat = &hat[13], /**/ .up = NULL, /*   */ .right = &right[13], /**/ .down = &down[13], /**/ .left = NULL, /**/ .expected = WANBEIYU_EINVAL},
                           {.hat = NULL, /*    */ .up = &up[14], /**/ .right = &right[14], /**/ .down = &down[14], /**/ .left = NULL, /**/ .expected = WANBEIYU_EINVAL},
                           {.hat = &hat[15], /**/ .up = &up[15], /**/ .right = &right[15], /**/ .down = &down[15], /**/ .left = NULL, /**/ .expected = WANBEIYU_EINVAL},
                           {.hat = NULL, /*    */ .up = NULL, /*   */ .right = NULL, /*      */ .down = NULL, /*     */ .left = &left[16], .expected = WANBEIYU_EINVAL},
                           {.hat = &hat[17], /**/ .up = NULL, /*   */ .right = NULL, /*      */ .down = NULL, /*     */ .left = &left[17], .expected = WANBEIYU_EINVAL},
                           {.hat = NULL, /*    */ .up = &up[18], /**/ .right = NULL, /*      */ .down = NULL, /*     */ .left = &left[18], .expected = WANBEIYU_EINVAL},
                           {.hat = &hat[19], /**/ .up = &up[19], /**/ .right = NULL, /*      */ .down = NULL, /*     */ .left = &left[19], .expected = WANBEIYU_EINVAL},
                           {.hat = NULL, /*    */ .up = NULL, /*   */ .right = &right[20], /**/ .down = NULL, /*     */ .left = &left[20], .expected = WANBEIYU_EINVAL},
                           {.hat = &hat[21], /**/ .up = NULL, /*   */ .right = &right[21], /**/ .down = NULL, /*     */ .left = &left[21], .expected = WANBEIYU_EINVAL},
                           {.hat = NULL, /*    */ .up = &up[22], /**/ .right = &right[22], /**/ .down = NULL, /*     */ .left = &left[22], .expected = WANBEIYU_EINVAL},
                           {.hat = &hat[23], /**/ .up = &up[23], /**/ .right = &right[23], /**/ .down = NULL, /*     */ .left = &left[23], .expected = WANBEIYU_EINVAL},
                           {.hat = NULL, /*    */ .up = NULL, /*   */ .right = NULL, /*      */ .down = &down[24], /**/ .left = &left[24], .expected = WANBEIYU_EINVAL},
                           {.hat = &hat[25], /**/ .up = NULL, /*   */ .right = NULL, /*      */ .down = &down[25], /**/ .left = &left[25], .expected = WANBEIYU_EINVAL},
                           {.hat = NULL, /*    */ .up = &up[26], /**/ .right = NULL, /*      */ .down = &down[26], /**/ .left = &left[26], .expected = WANBEIYU_EINVAL},
                           {.hat = &hat[27], /**/ .up = &up[27], /**/ .right = NULL, /*      */ .down = &down[27], /**/ .left = &left[27], .expected = WANBEIYU_EINVAL},
                           {.hat = NULL, /*    */ .up = NULL, /*   */ .right = &right[28], /**/ .down = &down[28], /**/ .left = &left[28], .expected = WANBEIYU_EINVAL},
                           {.hat = &hat[29], /**/ .up = NULL, /*   */ .right = &right[29], /**/ .down = &down[29], /**/ .left = &left[29], .expected = WANBEIYU_EINVAL},
                           {.hat = NULL, /*    */ .up = &up[30], /**/ .right = &right[30], /**/ .down = &down[30], /**/ .left = &left[30], .expected = WANBEIYU_EINVAL},
                           {.hat = &hat[31], /**/ .up = &up[31], /**/ .right = &right[31], /**/ .down = &down[31], /**/ .left = &left[31], .expected = WANBEIYU_OK}};

    TEST_FOR(cases)
    {
        wanbeiyu_error_t actual_ret = wanbeiyu_hat_init(case_.hat, case_.up, case_.right, case_.down, case_.left);
        TEST_ASSERT_EQUAL_WANBEIYU_ERROR_RET(case_.expected, actual_ret);
        if (actual_ret != WANBEIYU_OK)
        {
            continue;
        }

        if (gpio_up[i].state != TEST_GPIO_HI_Z ||
            gpio_right[i].state != TEST_GPIO_HI_Z ||
            gpio_down[i].state != TEST_GPIO_HI_Z ||
            gpio_left[i].state != TEST_GPIO_HI_Z)
        {
            fprintf(stderr, "%sindex: %d, expected_state: %d, %d, %d, %d, actual_state: %d, %d, %d, %d%s\n",
                    TEXT_RED, i, TEST_GPIO_HI_Z, TEST_GPIO_HI_Z, TEST_GPIO_HI_Z, TEST_GPIO_HI_Z,
                    gpio_up[i].state, gpio_right[i].state, gpio_down[i].state, gpio_left[i].state, TEXT_RESET);
            cnt++;
        }
    }
    return cnt;
}

int test_hat_hold(void)
{
    printf("  * %s\n", __func__);
    int cnt = 0;

    typedef struct test_case_t
    {
        wanbeiyu_hat_direction_t dir;

        test_gpio_state_t expected_up_state;
        test_gpio_state_t expected_right_state;
        test_gpio_state_t expected_down_state;
        test_gpio_state_t expected_left_state;
    } test_case_t;

    test_case_t cases[] = {{.dir = WANBEIYU_HAT_UP, /*       */ .expected_up_state = TEST_GPIO_LOW, .expected_right_state = TEST_GPIO_HI_Z, .expected_down_state = TEST_GPIO_HI_Z, .expected_left_state = TEST_GPIO_HI_Z},
                           {.dir = WANBEIYU_HAT_UPRIGHT, /*  */ .expected_up_state = TEST_GPIO_LOW, .expected_right_state = TEST_GPIO_LOW, .expected_down_state = TEST_GPIO_HI_Z, .expected_left_state = TEST_GPIO_HI_Z},
                           {.dir = WANBEIYU_HAT_RIGHT, /*    */ .expected_up_state = TEST_GPIO_HI_Z, .expected_right_state = TEST_GPIO_LOW, .expected_down_state = TEST_GPIO_HI_Z, .expected_left_state = TEST_GPIO_HI_Z},
                           {.dir = WANBEIYU_HAT_DOWNRIGHT, /**/ .expected_up_state = TEST_GPIO_HI_Z, .expected_right_state = TEST_GPIO_LOW, .expected_down_state = TEST_GPIO_LOW, .expected_left_state = TEST_GPIO_HI_Z},
                           {.dir = WANBEIYU_HAT_DOWN, /*     */ .expected_up_state = TEST_GPIO_HI_Z, .expected_right_state = TEST_GPIO_HI_Z, .expected_down_state = TEST_GPIO_LOW, .expected_left_state = TEST_GPIO_HI_Z},
                           {.dir = WANBEIYU_HAT_DOWNLEFT, /* */ .expected_up_state = TEST_GPIO_HI_Z, .expected_right_state = TEST_GPIO_HI_Z, .expected_down_state = TEST_GPIO_LOW, .expected_left_state = TEST_GPIO_LOW},
                           {.dir = WANBEIYU_HAT_LEFT, /*     */ .expected_up_state = TEST_GPIO_HI_Z, .expected_right_state = TEST_GPIO_HI_Z, .expected_down_state = TEST_GPIO_HI_Z, .expected_left_state = TEST_GPIO_LOW},
                           {.dir = WANBEIYU_HAT_UPLEFT, /*   */ .expected_up_state = TEST_GPIO_LOW, .expected_right_state = TEST_GPIO_HI_Z, .expected_down_state = TEST_GPIO_HI_Z, .expected_left_state = TEST_GPIO_LOW},
                           {.dir = WANBEIYU_HAT_NEUTRAL, /*  */ .expected_up_state = TEST_GPIO_HI_Z, .expected_right_state = TEST_GPIO_HI_Z, .expected_down_state = TEST_GPIO_HI_Z, .expected_left_state = TEST_GPIO_HI_Z},
                           {.dir = 0b101101, /*              */ .expected_up_state = TEST_GPIO_LOW, .expected_right_state = TEST_GPIO_LOW, .expected_down_state = TEST_GPIO_HI_Z, .expected_left_state = TEST_GPIO_LOW}};

    wanbeiyu_hat_t *hat_null = NULL;
    wanbeiyu_hat_hold(hat_null, WANBEIYU_HAT_NEUTRAL); /* Expected that nothing will happen. */

    TEST_FOR(cases)
    {
        test_gpio_t gpio[4];
        wanbeiyu_button_t btn[4];
        for (size_t j = 0; j < 4; j++)
        {
            test_gpio_init(&gpio[j]);
            assert(wanbeiyu_button_init(&btn[j], (wanbeiyu_gpio_t *)&gpio[j]) == WANBEIYU_OK);
        }
        wanbeiyu_hat_t hat;
        assert(wanbeiyu_hat_init(&hat, &btn[0], &btn[1], &btn[2], &btn[3]) == WANBEIYU_OK);

        wanbeiyu_hat_hold(&hat, case_.dir);

        if (gpio[0].state != case_.expected_up_state ||
            gpio[1].state != case_.expected_right_state ||
            gpio[2].state != case_.expected_down_state ||
            gpio[3].state != case_.expected_left_state)
        {
            fprintf(stderr, "%sindex: %d, expected_state: %d, %d, %d, %d, actual_state: %d, %d, %d, %d%s\n",
                    TEXT_RED, i, case_.expected_up_state, case_.expected_right_state, case_.expected_down_state, case_.expected_left_state,
                    gpio[0].state, gpio[1].state, gpio[2].state, gpio[3].state, TEXT_RESET);
            cnt++;
        }
    }

    return cnt;
}

int test_hat_release(void)
{
    printf("  * %s\n", __func__);
    int cnt = 0;

    wanbeiyu_hat_t *hat_null = NULL;
    wanbeiyu_hat_release(hat_null); /* Expected that nothing will happen. */

    test_gpio_t gpio[4];
    wanbeiyu_button_t btn[4];
    for (size_t i = 0; i < 4; i++)
    {
        test_gpio_init(&gpio[i]);
        assert(wanbeiyu_button_init(&btn[i], (wanbeiyu_gpio_t *)&gpio[i]) == WANBEIYU_OK);
    }
    wanbeiyu_hat_t hat;
    assert(wanbeiyu_hat_init(&hat, &btn[0], &btn[1], &btn[2], &btn[3]) == WANBEIYU_OK);

    wanbeiyu_hat_release(&hat);

    if (gpio[0].state != TEST_GPIO_HI_Z ||
        gpio[1].state != TEST_GPIO_HI_Z ||
        gpio[2].state != TEST_GPIO_HI_Z ||
        gpio[3].state != TEST_GPIO_HI_Z)
    {
        fprintf(stderr, "%sindex: %d, expected_state: %d, %d, %d, %d, actual_state: %d, %d, %d, %d%s\n",
                TEXT_RED, 0, TEST_GPIO_HI_Z, TEST_GPIO_HI_Z, TEST_GPIO_HI_Z, TEST_GPIO_HI_Z,
                gpio[0].state, gpio[1].state, gpio[2].state, gpio[3].state, TEXT_RESET);
        cnt++;
    }

    return cnt;
}

int test_hat(void)
{
    printf("* %s\n", __func__);
    int cnt = 0;

    cnt += test_hat_init();
    cnt += test_hat_hold();
    cnt += test_hat_release();

    return cnt;
}

#endif // TEST_HAT_H_