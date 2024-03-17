#ifndef TEST_HAT_H
#define TEST_HAT_H

#include <wanbeiyu/hat.h>
#include "test.h"

#include <assert.h>
#include <stdio.h>

int test_hat_init(void)
{
    typedef struct TestCase
    {
        WanbeiyuHat *hat;
        WanbeiyuGPIO *up;
        WanbeiyuGPIO *right;
        WanbeiyuGPIO *down;
        WanbeiyuGPIO *left;

        errno_t expected_err;
    } TestCase;

    WanbeiyuHat hat[32];
    WanbeiyuGPIO up[32];
    WanbeiyuGPIO right[32];
    WanbeiyuGPIO down[32];
    WanbeiyuGPIO left[32];

    TestCase TEST_CASES[] = {{.hat = NULL, /*    */ .up = NULL, /*   */ .right = NULL, /*      */ .down = NULL, /*     */ .left = NULL, /**/ .expected_err = EINVAL},
                             {.hat = &hat[1], /* */ .up = NULL, /*   */ .right = NULL, /*      */ .down = NULL, /*     */ .left = NULL, /**/ .expected_err = EINVAL},
                             {.hat = NULL, /*    */ .up = &up[2], /* */ .right = NULL, /*      */ .down = NULL, /*     */ .left = NULL, /**/ .expected_err = EINVAL},
                             {.hat = &hat[3], /* */ .up = &up[3], /* */ .right = NULL, /*      */ .down = NULL, /*     */ .left = NULL, /**/ .expected_err = EINVAL},
                             {.hat = NULL, /*    */ .up = NULL, /*   */ .right = &right[4], /* */ .down = NULL, /*     */ .left = NULL, /**/ .expected_err = EINVAL},
                             {.hat = &hat[5], /* */ .up = NULL, /*   */ .right = &right[5], /* */ .down = NULL, /*     */ .left = NULL, /**/ .expected_err = EINVAL},
                             {.hat = NULL, /*    */ .up = &up[6], /* */ .right = &right[6], /* */ .down = NULL, /*     */ .left = NULL, /**/ .expected_err = EINVAL},
                             {.hat = &hat[7], /* */ .up = &up[7], /* */ .right = &right[7], /* */ .down = NULL, /*     */ .left = NULL, /**/ .expected_err = EINVAL},
                             {.hat = NULL, /*    */ .up = NULL, /*   */ .right = NULL, /*      */ .down = &down[8], /* */ .left = NULL, /**/ .expected_err = EINVAL},
                             {.hat = &hat[9], /* */ .up = NULL, /*   */ .right = NULL, /*      */ .down = &down[9], /* */ .left = NULL, /**/ .expected_err = EINVAL},
                             {.hat = NULL, /*    */ .up = &up[10], /**/ .right = NULL, /*      */ .down = &down[10], /**/ .left = NULL, /**/ .expected_err = EINVAL},
                             {.hat = &hat[11], /**/ .up = &up[11], /**/ .right = NULL, /*      */ .down = &down[11], /**/ .left = NULL, /**/ .expected_err = EINVAL},
                             {.hat = NULL, /*    */ .up = NULL, /*   */ .right = &right[12], /**/ .down = &down[12], /**/ .left = NULL, /**/ .expected_err = EINVAL},
                             {.hat = &hat[13], /**/ .up = NULL, /*   */ .right = &right[13], /**/ .down = &down[13], /**/ .left = NULL, /**/ .expected_err = EINVAL},
                             {.hat = NULL, /*    */ .up = &up[14], /**/ .right = &right[14], /**/ .down = &down[14], /**/ .left = NULL, /**/ .expected_err = EINVAL},
                             {.hat = &hat[15], /**/ .up = &up[15], /**/ .right = &right[15], /**/ .down = &down[15], /**/ .left = NULL, /**/ .expected_err = EINVAL},
                             {.hat = NULL, /*    */ .up = NULL, /*   */ .right = NULL, /*      */ .down = NULL, /*     */ .left = &left[16], .expected_err = EINVAL},
                             {.hat = &hat[17], /**/ .up = NULL, /*   */ .right = NULL, /*      */ .down = NULL, /*     */ .left = &left[17], .expected_err = EINVAL},
                             {.hat = NULL, /*    */ .up = &up[18], /**/ .right = NULL, /*      */ .down = NULL, /*     */ .left = &left[18], .expected_err = EINVAL},
                             {.hat = &hat[19], /**/ .up = &up[19], /**/ .right = NULL, /*      */ .down = NULL, /*     */ .left = &left[19], .expected_err = EINVAL},
                             {.hat = NULL, /*    */ .up = NULL, /*   */ .right = &right[20], /**/ .down = NULL, /*     */ .left = &left[20], .expected_err = EINVAL},
                             {.hat = &hat[21], /**/ .up = NULL, /*   */ .right = &right[21], /**/ .down = NULL, /*     */ .left = &left[21], .expected_err = EINVAL},
                             {.hat = NULL, /*    */ .up = &up[22], /**/ .right = &right[22], /**/ .down = NULL, /*     */ .left = &left[22], .expected_err = EINVAL},
                             {.hat = &hat[23], /**/ .up = &up[23], /**/ .right = &right[23], /**/ .down = NULL, /*     */ .left = &left[23], .expected_err = EINVAL},
                             {.hat = NULL, /*    */ .up = NULL, /*   */ .right = NULL, /*      */ .down = &down[24], /**/ .left = &left[24], .expected_err = EINVAL},
                             {.hat = &hat[25], /**/ .up = NULL, /*   */ .right = NULL, /*      */ .down = &down[25], /**/ .left = &left[25], .expected_err = EINVAL},
                             {.hat = NULL, /*    */ .up = &up[26], /**/ .right = NULL, /*      */ .down = &down[26], /**/ .left = &left[26], .expected_err = EINVAL},
                             {.hat = &hat[27], /**/ .up = &up[27], /**/ .right = NULL, /*      */ .down = &down[27], /**/ .left = &left[27], .expected_err = EINVAL},
                             {.hat = NULL, /*    */ .up = NULL, /*   */ .right = &right[28], /**/ .down = &down[28], /**/ .left = &left[28], .expected_err = EINVAL},
                             {.hat = &hat[29], /**/ .up = NULL, /*   */ .right = &right[29], /**/ .down = &down[29], /**/ .left = &left[29], .expected_err = EINVAL},
                             {.hat = NULL, /*    */ .up = &up[30], /**/ .right = &right[30], /**/ .down = &down[30], /**/ .left = &left[30], .expected_err = EINVAL},
                             {.hat = &hat[31], /**/ .up = &up[31], /**/ .right = &right[31], /**/ .down = &down[31], /**/ .left = &left[31], .expected_err = 0}};

    TEST_FOR(TEST_CASES)
    {
        errno_t actual_err = wanbeiyu_hat_init(TEST_CASE->hat, (WanbeiyuGPIO *)TEST_CASE->up, (WanbeiyuGPIO *)TEST_CASE->right, (WanbeiyuGPIO *)TEST_CASE->down, (WanbeiyuGPIO *)TEST_CASE->left);
        TEST_ASSERT_EQUAL_ERRNO_T(TEST_CASE->expected_err, actual_err);
    }

    return TEST_COUNT;
}

int test_hat_hold(void)
{
    typedef struct TestCase
    {
        WanbeiyuHat *hat;
        WanbeiyuHatDirection dir;

        errno_t expected_err;
        TestGPIOState expected_up_state;
        TestGPIOState expected_right_state;
        TestGPIOState expected_down_state;
        TestGPIOState expected_left_state;
    } TestCase;

    WanbeiyuHat hat[13];
    TestGPIO up[13];
    TestGPIO right[13];
    TestGPIO down[13];
    TestGPIO left[13];
    for (size_t i = 0; i < 13; i++)
    {
        test_gpio_init(&up[i]);
        test_gpio_init(&right[i]);
        test_gpio_init(&down[i]);
        test_gpio_init(&left[i]);
        assert(wanbeiyu_hat_init(&hat[i], (WanbeiyuGPIO *)&up[i], (WanbeiyuGPIO *)&right[i], (WanbeiyuGPIO *)&down[i], (WanbeiyuGPIO *)&left[i]) == 0);
    }

    TestCase TEST_CASES[] = {{.hat = NULL, /*    */ .dir = WANBEIYU_HAT_NEUTRAL, /*  */ .expected_err = EINVAL},
                             {.hat = &hat[1], /* */ .dir = WANBEIYU_HAT_UP, /*       */ .expected_err = 0, .expected_up_state = TEST_GPIO_LOW, .expected_right_state = TEST_GPIO_HI_Z, .expected_down_state = TEST_GPIO_HI_Z, .expected_left_state = TEST_GPIO_HI_Z},
                             {.hat = &hat[2], /* */ .dir = WANBEIYU_HAT_UPRIGHT, /*  */ .expected_err = 0, .expected_up_state = TEST_GPIO_LOW, .expected_right_state = TEST_GPIO_LOW, .expected_down_state = TEST_GPIO_HI_Z, .expected_left_state = TEST_GPIO_HI_Z},
                             {.hat = &hat[3], /* */ .dir = WANBEIYU_HAT_RIGHT, /*    */ .expected_err = 0, .expected_up_state = TEST_GPIO_HI_Z, .expected_right_state = TEST_GPIO_LOW, .expected_down_state = TEST_GPIO_HI_Z, .expected_left_state = TEST_GPIO_HI_Z},
                             {.hat = &hat[4], /* */ .dir = WANBEIYU_HAT_DOWNRIGHT, /**/ .expected_err = 0, .expected_up_state = TEST_GPIO_HI_Z, .expected_right_state = TEST_GPIO_LOW, .expected_down_state = TEST_GPIO_LOW, .expected_left_state = TEST_GPIO_HI_Z},
                             {.hat = &hat[5], /* */ .dir = WANBEIYU_HAT_DOWN, /*     */ .expected_err = 0, .expected_up_state = TEST_GPIO_HI_Z, .expected_right_state = TEST_GPIO_HI_Z, .expected_down_state = TEST_GPIO_LOW, .expected_left_state = TEST_GPIO_HI_Z},
                             {.hat = &hat[6], /* */ .dir = WANBEIYU_HAT_DOWNLEFT, /* */ .expected_err = 0, .expected_up_state = TEST_GPIO_HI_Z, .expected_right_state = TEST_GPIO_HI_Z, .expected_down_state = TEST_GPIO_LOW, .expected_left_state = TEST_GPIO_LOW},
                             {.hat = &hat[7], /* */ .dir = WANBEIYU_HAT_LEFT, /*     */ .expected_err = 0, .expected_up_state = TEST_GPIO_HI_Z, .expected_right_state = TEST_GPIO_HI_Z, .expected_down_state = TEST_GPIO_HI_Z, .expected_left_state = TEST_GPIO_LOW},
                             {.hat = &hat[8], /* */ .dir = WANBEIYU_HAT_UPLEFT, /*   */ .expected_err = 0, .expected_up_state = TEST_GPIO_LOW, .expected_right_state = TEST_GPIO_HI_Z, .expected_down_state = TEST_GPIO_HI_Z, .expected_left_state = TEST_GPIO_LOW},
                             {.hat = &hat[9], /* */ .dir = WANBEIYU_HAT_NEUTRAL, /*  */ .expected_err = 0, .expected_up_state = TEST_GPIO_HI_Z, .expected_right_state = TEST_GPIO_HI_Z, .expected_down_state = TEST_GPIO_HI_Z, .expected_left_state = TEST_GPIO_HI_Z},
                             {.hat = &hat[10], /**/ .dir = 0b1101, /*                */ .expected_err = 0, .expected_up_state = TEST_GPIO_LOW, .expected_right_state = TEST_GPIO_LOW, .expected_down_state = TEST_GPIO_HI_Z, .expected_left_state = TEST_GPIO_LOW},
                             {.hat = &hat[11], /**/ .dir = 0b1111, /*                */ .expected_err = 0, .expected_up_state = TEST_GPIO_LOW, .expected_right_state = TEST_GPIO_LOW, .expected_down_state = TEST_GPIO_LOW, .expected_left_state = TEST_GPIO_LOW},
                             {.hat = &hat[12], /**/ .dir = 0b10000, /*               */ .expected_err = EINVAL}};

    TEST_FOR(TEST_CASES)
    {
        errno_t actual_ret = wanbeiyu_hat_hold(TEST_CASE->hat, TEST_CASE->dir);
        TEST_ASSERT_EQUAL_ERRNO_T(TEST_CASE->expected_err, actual_ret);
        if (actual_ret != 0)
        {
            continue;
        }

        TestGPIOState actual_up_state = up[TEST_INDEX].state;
        TEST_ASSERT_EQUAL_TEST_GPIO_STATE(TEST_CASE->expected_up_state, actual_up_state);

        TestGPIOState actual_right_state = right[TEST_INDEX].state;
        TEST_ASSERT_EQUAL_TEST_GPIO_STATE(TEST_CASE->expected_right_state, actual_right_state);

        TestGPIOState actual_down_state = down[TEST_INDEX].state;
        TEST_ASSERT_EQUAL_TEST_GPIO_STATE(TEST_CASE->expected_down_state, actual_down_state);

        TestGPIOState actual_left_state = left[TEST_INDEX].state;
        TEST_ASSERT_EQUAL_TEST_GPIO_STATE(TEST_CASE->expected_left_state, actual_left_state);
    }

    return TEST_COUNT;
}

int test_hat_release(void)
{
    typedef struct TestCase
    {
        WanbeiyuHat *hat;

        errno_t expected_err;
        TestGPIOState expected_up_state;
        TestGPIOState expected_right_state;
        TestGPIOState expected_down_state;
        TestGPIOState expected_left_state;
    } TestCase;

    WanbeiyuHat hat[2];
    TestGPIO up[2];
    TestGPIO right[2];
    TestGPIO down[2];
    TestGPIO left[2];
    for (size_t i = 0; i < 2; i++)
    {
        test_gpio_init(&up[i]);
        test_gpio_init(&right[i]);
        test_gpio_init(&down[i]);
        test_gpio_init(&left[i]);
        assert(wanbeiyu_hat_init(&hat[i], (WanbeiyuGPIO *)&up[i], (WanbeiyuGPIO *)&right[i], (WanbeiyuGPIO *)&down[i], (WanbeiyuGPIO *)&left[i]) == 0);
    }

    TestCase TEST_CASES[] = {{.hat = NULL, /*   */ .expected_err = EINVAL},
                             {.hat = &hat[1], /**/ .expected_err = 0, .expected_up_state = TEST_GPIO_HI_Z, .expected_right_state = TEST_GPIO_HI_Z, .expected_down_state = TEST_GPIO_HI_Z, .expected_left_state = TEST_GPIO_HI_Z}};

    TEST_FOR(TEST_CASES)
    {
        errno_t actual_ret = wanbeiyu_hat_release(TEST_CASE->hat);
        TEST_ASSERT_EQUAL_ERRNO_T(TEST_CASE->expected_err, actual_ret);
        if (actual_ret != 0)
        {
            continue;
        }

        TestGPIOState actual_up_state = up[TEST_INDEX].state;
        TEST_ASSERT_EQUAL_TEST_GPIO_STATE(TEST_CASE->expected_up_state, actual_up_state);

        TestGPIOState actual_right_state = right[TEST_INDEX].state;
        TEST_ASSERT_EQUAL_TEST_GPIO_STATE(TEST_CASE->expected_right_state, actual_right_state);

        TestGPIOState actual_down_state = down[TEST_INDEX].state;
        TEST_ASSERT_EQUAL_TEST_GPIO_STATE(TEST_CASE->expected_down_state, actual_down_state);

        TestGPIOState actual_left_state = left[TEST_INDEX].state;
        TEST_ASSERT_EQUAL_TEST_GPIO_STATE(TEST_CASE->expected_left_state, actual_left_state);
    }

    return TEST_COUNT;
}

int test_hat(void)
{
    int count = 0;

    count += test_hat_init();
    count += test_hat_hold();
    count += test_hat_release();

    return count;
}

#endif // TEST_HAT_H