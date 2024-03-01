#ifndef TEST_BUTTON_H_
#define TEST_BUTTON_H_

#include <wanbeiyu.h>
#include "test.h"

#include <assert.h>
#include <stdio.h>

int test_button_init(void)
{
    printf("  * %s\n", __func__);
    int cnt = 0;

    typedef struct TestCase
    {
        WanbeiyuButton *btn;
        WanbeiyuGPIO *gpio;

        WanbeiyuErrNo expected_ret;
    } TestCase;

    WanbeiyuButton btn[4];
    WanbeiyuGPIO gpio[4];

    TestCase cases[] = {{.btn = NULL, /*   */ .gpio = NULL, /*    */ .expected_ret = WANBEIYU_EINVAL},
                        {.btn = &btn[1], /**/ .gpio = NULL, /*    */ .expected_ret = WANBEIYU_EINVAL},
                        {.btn = NULL, /*   */ .gpio = &gpio[2], /**/ .expected_ret = WANBEIYU_EINVAL},
                        {.btn = &btn[3], /**/ .gpio = &gpio[3], /**/ .expected_ret = WANBEIYU_OK}};

    TEST_FOR(cases)
    {
        WanbeiyuErrNo actual_ret = wanbeiyu_button_init(case_.btn, (WanbeiyuGPIO *)case_.gpio);
        TEST_ASSERT_EQUAL_WANBEIYU_ERROR_RET(case_.expected_ret, actual_ret);
    }

    return cnt;
}

int test_button_hold(void)
{
    printf("  * %s\n", __func__);
    int cnt = 0;

    typedef struct TestCase
    {
        WanbeiyuErrNo expected_ret;
        TestGPIOState expected_state;
    } TestCase;

    TestCase cases[] = {{.expected_ret = WANBEIYU_OK, .expected_state = TEST_GPIO_LOW}};

    TEST_FOR(cases)
    {
        WanbeiyuButton *btn_null = NULL;
        WanbeiyuErrNo actual_ret = wanbeiyu_button_hold(btn_null);
        TEST_ASSERT_EQUAL_WANBEIYU_ERROR_RET(WANBEIYU_EINVAL, actual_ret);

        WanbeiyuButton btn;
        TestGPIO gpio;
        test_gpio_init(&gpio);
        assert(wanbeiyu_button_init(&btn, (WanbeiyuGPIO *)&gpio) == WANBEIYU_OK);

        actual_ret = wanbeiyu_button_hold(&btn);
        TEST_ASSERT_EQUAL_WANBEIYU_ERROR_RET(case_.expected_ret, actual_ret);
        if (actual_ret != WANBEIYU_OK)
        {
            continue;
        }

        TestGPIOState actual_state = gpio.state;
        if (case_.expected_state != actual_state)
        {
            fprintf(stderr, "%sindex: %d, expected_state: %d, actual_state: %d%s\n",
                    TEXT_RED, i, TEST_GPIO_STATE(TEST_GPIO_LOW), TEST_GPIO_STATE(actual_state), TEXT_RESET);
            cnt++;
        }
    }

    return cnt;
}

int test_button_release(void)
{
    printf("  * %s\n", __func__);
    int cnt = 0;

    typedef struct TestCase
    {
        WanbeiyuErrNo expected_ret;
        TestGPIOState expected_state;
    } TestCase;

    TestCase cases[] = {{.expected_ret = WANBEIYU_OK, .expected_state = TEST_GPIO_HI_Z}};

    TEST_FOR(cases)
    {
        WanbeiyuButton *btn_null = NULL;
        WanbeiyuErrNo actual_ret = wanbeiyu_button_release(btn_null);
        TEST_ASSERT_EQUAL_WANBEIYU_ERROR_RET(WANBEIYU_EINVAL, actual_ret);

        WanbeiyuButton btn;
        TestGPIO gpio;
        test_gpio_init(&gpio);
        assert(wanbeiyu_button_init(&btn, (WanbeiyuGPIO *)&gpio) == WANBEIYU_OK);

        actual_ret = wanbeiyu_button_release(&btn);
        TEST_ASSERT_EQUAL_WANBEIYU_ERROR_RET(case_.expected_ret, actual_ret);
        if (actual_ret != WANBEIYU_OK)
        {
            continue;
        }

        TestGPIOState actual_state = gpio.state;
        if (case_.expected_state != actual_state)
        {
            fprintf(stderr, "%sindex: %d, expected_state: %d, actual_state: %d%s\n",
                    TEXT_RED, i, TEST_GPIO_STATE(TEST_GPIO_LOW), TEST_GPIO_STATE(actual_state), TEXT_RESET);
            cnt++;
        }
    }

    return cnt;
}

int test_button(void)
{
    printf("* %s\n", __func__);
    int cnt = 0;

    cnt += test_button_init();
    cnt += test_button_hold();
    cnt += test_button_release();

    return cnt;
}

#endif // TEST_BUTTON_H_