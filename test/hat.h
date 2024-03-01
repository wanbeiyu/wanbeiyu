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

    typedef struct TestCase
    {
        WanbeiyuHat *hat;
        WanbeiyuGPIO *up;
        WanbeiyuGPIO *right;
        WanbeiyuGPIO *down;
        WanbeiyuGPIO *left;

        WanbeiyuError expected_ret;
    } TestCase;

    WanbeiyuHat hat[32];
    WanbeiyuGPIO up[32];
    WanbeiyuGPIO right[32];
    WanbeiyuGPIO down[32];
    WanbeiyuGPIO left[32];

    TestCase cases[] = {{.hat = NULL, /*    */ .up = NULL, /*   */ .right = NULL, /*      */ .down = NULL, /*     */ .left = NULL, /**/ .expected_ret = WANBEIYU_EINVAL},
                        {.hat = &hat[1], /* */ .up = NULL, /*   */ .right = NULL, /*      */ .down = NULL, /*     */ .left = NULL, /**/ .expected_ret = WANBEIYU_EINVAL},
                        {.hat = NULL, /*    */ .up = &up[2], /* */ .right = NULL, /*      */ .down = NULL, /*     */ .left = NULL, /**/ .expected_ret = WANBEIYU_EINVAL},
                        {.hat = &hat[3], /* */ .up = &up[3], /* */ .right = NULL, /*      */ .down = NULL, /*     */ .left = NULL, /**/ .expected_ret = WANBEIYU_EINVAL},
                        {.hat = NULL, /*    */ .up = NULL, /*   */ .right = &right[4], /* */ .down = NULL, /*     */ .left = NULL, /**/ .expected_ret = WANBEIYU_EINVAL},
                        {.hat = &hat[5], /* */ .up = NULL, /*   */ .right = &right[5], /* */ .down = NULL, /*     */ .left = NULL, /**/ .expected_ret = WANBEIYU_EINVAL},
                        {.hat = NULL, /*    */ .up = &up[6], /* */ .right = &right[6], /* */ .down = NULL, /*     */ .left = NULL, /**/ .expected_ret = WANBEIYU_EINVAL},
                        {.hat = &hat[7], /* */ .up = &up[7], /* */ .right = &right[7], /* */ .down = NULL, /*     */ .left = NULL, /**/ .expected_ret = WANBEIYU_EINVAL},
                        {.hat = NULL, /*    */ .up = NULL, /*   */ .right = NULL, /*      */ .down = &down[8], /* */ .left = NULL, /**/ .expected_ret = WANBEIYU_EINVAL},
                        {.hat = &hat[9], /* */ .up = NULL, /*   */ .right = NULL, /*      */ .down = &down[9], /* */ .left = NULL, /**/ .expected_ret = WANBEIYU_EINVAL},
                        {.hat = NULL, /*    */ .up = &up[10], /**/ .right = NULL, /*      */ .down = &down[10], /**/ .left = NULL, /**/ .expected_ret = WANBEIYU_EINVAL},
                        {.hat = &hat[11], /**/ .up = &up[11], /**/ .right = NULL, /*      */ .down = &down[11], /**/ .left = NULL, /**/ .expected_ret = WANBEIYU_EINVAL},
                        {.hat = NULL, /*    */ .up = NULL, /*   */ .right = &right[12], /**/ .down = &down[12], /**/ .left = NULL, /**/ .expected_ret = WANBEIYU_EINVAL},
                        {.hat = &hat[13], /**/ .up = NULL, /*   */ .right = &right[13], /**/ .down = &down[13], /**/ .left = NULL, /**/ .expected_ret = WANBEIYU_EINVAL},
                        {.hat = NULL, /*    */ .up = &up[14], /**/ .right = &right[14], /**/ .down = &down[14], /**/ .left = NULL, /**/ .expected_ret = WANBEIYU_EINVAL},
                        {.hat = &hat[15], /**/ .up = &up[15], /**/ .right = &right[15], /**/ .down = &down[15], /**/ .left = NULL, /**/ .expected_ret = WANBEIYU_EINVAL},
                        {.hat = NULL, /*    */ .up = NULL, /*   */ .right = NULL, /*      */ .down = NULL, /*     */ .left = &left[16], .expected_ret = WANBEIYU_EINVAL},
                        {.hat = &hat[17], /**/ .up = NULL, /*   */ .right = NULL, /*      */ .down = NULL, /*     */ .left = &left[17], .expected_ret = WANBEIYU_EINVAL},
                        {.hat = NULL, /*    */ .up = &up[18], /**/ .right = NULL, /*      */ .down = NULL, /*     */ .left = &left[18], .expected_ret = WANBEIYU_EINVAL},
                        {.hat = &hat[19], /**/ .up = &up[19], /**/ .right = NULL, /*      */ .down = NULL, /*     */ .left = &left[19], .expected_ret = WANBEIYU_EINVAL},
                        {.hat = NULL, /*    */ .up = NULL, /*   */ .right = &right[20], /**/ .down = NULL, /*     */ .left = &left[20], .expected_ret = WANBEIYU_EINVAL},
                        {.hat = &hat[21], /**/ .up = NULL, /*   */ .right = &right[21], /**/ .down = NULL, /*     */ .left = &left[21], .expected_ret = WANBEIYU_EINVAL},
                        {.hat = NULL, /*    */ .up = &up[22], /**/ .right = &right[22], /**/ .down = NULL, /*     */ .left = &left[22], .expected_ret = WANBEIYU_EINVAL},
                        {.hat = &hat[23], /**/ .up = &up[23], /**/ .right = &right[23], /**/ .down = NULL, /*     */ .left = &left[23], .expected_ret = WANBEIYU_EINVAL},
                        {.hat = NULL, /*    */ .up = NULL, /*   */ .right = NULL, /*      */ .down = &down[24], /**/ .left = &left[24], .expected_ret = WANBEIYU_EINVAL},
                        {.hat = &hat[25], /**/ .up = NULL, /*   */ .right = NULL, /*      */ .down = &down[25], /**/ .left = &left[25], .expected_ret = WANBEIYU_EINVAL},
                        {.hat = NULL, /*    */ .up = &up[26], /**/ .right = NULL, /*      */ .down = &down[26], /**/ .left = &left[26], .expected_ret = WANBEIYU_EINVAL},
                        {.hat = &hat[27], /**/ .up = &up[27], /**/ .right = NULL, /*      */ .down = &down[27], /**/ .left = &left[27], .expected_ret = WANBEIYU_EINVAL},
                        {.hat = NULL, /*    */ .up = NULL, /*   */ .right = &right[28], /**/ .down = &down[28], /**/ .left = &left[28], .expected_ret = WANBEIYU_EINVAL},
                        {.hat = &hat[29], /**/ .up = NULL, /*   */ .right = &right[29], /**/ .down = &down[29], /**/ .left = &left[29], .expected_ret = WANBEIYU_EINVAL},
                        {.hat = NULL, /*    */ .up = &up[30], /**/ .right = &right[30], /**/ .down = &down[30], /**/ .left = &left[30], .expected_ret = WANBEIYU_EINVAL},
                        {.hat = &hat[31], /**/ .up = &up[31], /**/ .right = &right[31], /**/ .down = &down[31], /**/ .left = &left[31], .expected_ret = WANBEIYU_OK}};

    TEST_FOR(cases)
    {
        WanbeiyuError actual_ret = wanbeiyu_hat_init(case_.hat, case_.up, case_.right, case_.down, case_.left);
        TEST_ASSERT_EQUAL_WANBEIYU_ERROR_RET(case_.expected_ret, actual_ret);
    }

    return cnt;
}

int test_hat_hold(void)
{
    printf("  * %s\n", __func__);
    int cnt = 0;

    typedef struct TestCase
    {
        WanbeiyuHatDirection dir;

        WanbeiyuError expected_ret;
        TestGPIOState expected_up_state;
        TestGPIOState expected_right_state;
        TestGPIOState expected_down_state;
        TestGPIOState expected_left_state;
    } TestCase;

    TestCase cases[] = {{.dir = WANBEIYU_HAT_UP, /*       */ .expected_ret = WANBEIYU_OK, .expected_up_state = TEST_GPIO_LOW, .expected_right_state = TEST_GPIO_HI_Z, .expected_down_state = TEST_GPIO_HI_Z, .expected_left_state = TEST_GPIO_HI_Z},
                        {.dir = WANBEIYU_HAT_UPRIGHT, /*  */ .expected_ret = WANBEIYU_OK, .expected_up_state = TEST_GPIO_LOW, .expected_right_state = TEST_GPIO_LOW, .expected_down_state = TEST_GPIO_HI_Z, .expected_left_state = TEST_GPIO_HI_Z},
                        {.dir = WANBEIYU_HAT_RIGHT, /*    */ .expected_ret = WANBEIYU_OK, .expected_up_state = TEST_GPIO_HI_Z, .expected_right_state = TEST_GPIO_LOW, .expected_down_state = TEST_GPIO_HI_Z, .expected_left_state = TEST_GPIO_HI_Z},
                        {.dir = WANBEIYU_HAT_DOWNRIGHT, /**/ .expected_ret = WANBEIYU_OK, .expected_up_state = TEST_GPIO_HI_Z, .expected_right_state = TEST_GPIO_LOW, .expected_down_state = TEST_GPIO_LOW, .expected_left_state = TEST_GPIO_HI_Z},
                        {.dir = WANBEIYU_HAT_DOWN, /*     */ .expected_ret = WANBEIYU_OK, .expected_up_state = TEST_GPIO_HI_Z, .expected_right_state = TEST_GPIO_HI_Z, .expected_down_state = TEST_GPIO_LOW, .expected_left_state = TEST_GPIO_HI_Z},
                        {.dir = WANBEIYU_HAT_DOWNLEFT, /* */ .expected_ret = WANBEIYU_OK, .expected_up_state = TEST_GPIO_HI_Z, .expected_right_state = TEST_GPIO_HI_Z, .expected_down_state = TEST_GPIO_LOW, .expected_left_state = TEST_GPIO_LOW},
                        {.dir = WANBEIYU_HAT_LEFT, /*     */ .expected_ret = WANBEIYU_OK, .expected_up_state = TEST_GPIO_HI_Z, .expected_right_state = TEST_GPIO_HI_Z, .expected_down_state = TEST_GPIO_HI_Z, .expected_left_state = TEST_GPIO_LOW},
                        {.dir = WANBEIYU_HAT_UPLEFT, /*   */ .expected_ret = WANBEIYU_OK, .expected_up_state = TEST_GPIO_LOW, .expected_right_state = TEST_GPIO_HI_Z, .expected_down_state = TEST_GPIO_HI_Z, .expected_left_state = TEST_GPIO_LOW},
                        {.dir = WANBEIYU_HAT_NEUTRAL, /*  */ .expected_ret = WANBEIYU_OK, .expected_up_state = TEST_GPIO_HI_Z, .expected_right_state = TEST_GPIO_HI_Z, .expected_down_state = TEST_GPIO_HI_Z, .expected_left_state = TEST_GPIO_HI_Z},
                        {.dir = 0b1101, /*                */ .expected_ret = WANBEIYU_OK, .expected_up_state = TEST_GPIO_LOW, .expected_right_state = TEST_GPIO_LOW, .expected_down_state = TEST_GPIO_HI_Z, .expected_left_state = TEST_GPIO_LOW},
                        {.dir = 0b1111, /*                */ .expected_ret = WANBEIYU_OK, .expected_up_state = TEST_GPIO_LOW, .expected_right_state = TEST_GPIO_LOW, .expected_down_state = TEST_GPIO_LOW, .expected_left_state = TEST_GPIO_LOW},
                        {.dir = 0b10000, /*               */ .expected_ret = WANBEIYU_EINVAL}};

    TEST_FOR(cases)
    {
        WanbeiyuHat *hat_null = NULL;
        WanbeiyuError actual_ret = wanbeiyu_hat_hold(hat_null, case_.dir);
        TEST_ASSERT_EQUAL_WANBEIYU_ERROR_RET(WANBEIYU_EINVAL, actual_ret);

        WanbeiyuHat hat;
        TestGPIO gpio[4];
        for (size_t j = 0; j < 4; j++)
        {
            test_gpio_init(&gpio[j]);
        }
        assert(wanbeiyu_hat_init(&hat, (WanbeiyuGPIO *)&gpio[0], (WanbeiyuGPIO *)&gpio[1], (WanbeiyuGPIO *)&gpio[2], (WanbeiyuGPIO *)&gpio[3]) == WANBEIYU_OK);

        actual_ret = wanbeiyu_hat_hold(&hat, case_.dir);
        TEST_ASSERT_EQUAL_WANBEIYU_ERROR_RET(case_.expected_ret, actual_ret);
        if (actual_ret != WANBEIYU_OK)
        {
            continue;
        }

        if (gpio[0].state != case_.expected_up_state ||
            gpio[1].state != case_.expected_right_state ||
            gpio[2].state != case_.expected_down_state ||
            gpio[3].state != case_.expected_left_state)
        {
            fprintf(stderr, "%sindex: %d, expected_state: %d, %d, %d, %d, actual_state: %d, %d, %d, %d%s\n",
                    TEXT_RED, i, TEST_GPIO_STATE(case_.expected_up_state), TEST_GPIO_STATE(case_.expected_right_state), TEST_GPIO_STATE(case_.expected_down_state), TEST_GPIO_STATE(case_.expected_left_state),
                    TEST_GPIO_STATE(gpio[0].state), TEST_GPIO_STATE(gpio[1].state), TEST_GPIO_STATE(gpio[2].state), TEST_GPIO_STATE(gpio[3].state), TEXT_RESET);
            cnt++;
        }
    }

    return cnt;
}

int test_hat_release(void)
{
    printf("  * %s\n", __func__);
    int cnt = 0;

    typedef struct TestCase
    {
        WanbeiyuError expected_ret;
        TestGPIOState expected_up_state;
        TestGPIOState expected_right_state;
        TestGPIOState expected_down_state;
        TestGPIOState expected_left_state;
    } TestCase;

    TestCase cases[] = {{.expected_ret = WANBEIYU_OK, .expected_ret = WANBEIYU_OK, .expected_up_state = TEST_GPIO_HI_Z, .expected_right_state = TEST_GPIO_HI_Z, .expected_down_state = TEST_GPIO_HI_Z, .expected_left_state = TEST_GPIO_HI_Z}};

    TEST_FOR(cases)
    {
        WanbeiyuHat *hat_null = NULL;
        WanbeiyuError actual_ret = wanbeiyu_hat_release(hat_null);
        TEST_ASSERT_EQUAL_WANBEIYU_ERROR_RET(WANBEIYU_EINVAL, actual_ret);

        WanbeiyuHat hat;
        TestGPIO gpio[4];
        for (size_t j = 0; j < 4; j++)
        {
            test_gpio_init(&gpio[j]);
        }
        assert(wanbeiyu_hat_init(&hat, (WanbeiyuGPIO *)&gpio[0], (WanbeiyuGPIO *)&gpio[1], (WanbeiyuGPIO *)&gpio[2], (WanbeiyuGPIO *)&gpio[3]) == WANBEIYU_OK);

        actual_ret = wanbeiyu_hat_release(&hat);
        TEST_ASSERT_EQUAL_WANBEIYU_ERROR_RET(case_.expected_ret, actual_ret);
        if (actual_ret != WANBEIYU_OK)
        {
            continue;
        }

        if (gpio[0].state != case_.expected_up_state ||
            gpio[1].state != case_.expected_right_state ||
            gpio[2].state != case_.expected_down_state ||
            gpio[3].state != case_.expected_left_state)
        {
            fprintf(stderr, "%sindex: %d, expected_state: %d, %d, %d, %d, actual_state: %d, %d, %d, %d%s\n",
                    TEXT_RED, i, TEST_GPIO_STATE(case_.expected_up_state), TEST_GPIO_STATE(case_.expected_right_state), TEST_GPIO_STATE(case_.expected_down_state), TEST_GPIO_STATE(case_.expected_left_state),
                    TEST_GPIO_STATE(gpio[0].state), TEST_GPIO_STATE(gpio[1].state), TEST_GPIO_STATE(gpio[2].state), TEST_GPIO_STATE(gpio[3].state), TEXT_RESET);
            cnt++;
        }
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