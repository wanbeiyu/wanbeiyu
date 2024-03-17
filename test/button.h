#ifndef TEST_BUTTON_H
#define TEST_BUTTON_H

#include <wanbeiyu/button.h>
#include "test.h"

#include <assert.h>
#include <stdio.h>

int test_button_init(void)
{
    typedef struct TestCase
    {
        WanbeiyuButton *btn;
        WanbeiyuGPIO *gpio;

        errno_t expected_err;
    } TestCase;

    WanbeiyuButton btn[4];
    WanbeiyuGPIO gpio[4];

    TestCase TEST_CASES[] = {{.btn = NULL, /*   */ .gpio = NULL, /*    */ .expected_err = EINVAL},
                             {.btn = &btn[1], /**/ .gpio = NULL, /*    */ .expected_err = EINVAL},
                             {.btn = NULL, /*   */ .gpio = &gpio[2], /**/ .expected_err = EINVAL},
                             {.btn = &btn[3], /**/ .gpio = &gpio[3], /**/ .expected_err = 0}};

    TEST_FOR(TEST_CASES)
    {
        errno_t actual_err = wanbeiyu_button_init(TEST_CASE->btn, (WanbeiyuGPIO *)TEST_CASE->gpio);
        TEST_ASSERT_EQUAL_ERRNO_T(TEST_CASE->expected_err, actual_err);
    }

    return TEST_COUNT;
}

int test_button_hold(void)
{
    typedef struct TestCase
    {
        WanbeiyuButton *btn;

        errno_t expected_err;
        TestGPIOState expected_state;
    } TestCase;

    TestGPIO gpio[2];
    WanbeiyuButton btn[2];
    test_gpio_init(&gpio[1]);
    assert(wanbeiyu_button_init(&btn[1], (WanbeiyuGPIO *)&gpio[1]) == 0);

    TestCase TEST_CASES[] = {{.btn = NULL, /*   */ .expected_err = EINVAL},
                             {.btn = &btn[1], /**/ .expected_err = 0, .expected_state = TEST_GPIO_LOW}};

    TEST_FOR(TEST_CASES)
    {
        errno_t actual_err = wanbeiyu_button_hold(TEST_CASE->btn);
        TEST_ASSERT_EQUAL_ERRNO_T(TEST_CASE->expected_err, actual_err);
        if (actual_err != 0)
        {
            continue;
        }

        TestGPIOState actual_state = gpio[TEST_INDEX].state;
        TEST_ASSERT_EQUAL_TEST_GPIO_STATE(TEST_CASE->expected_state, actual_state);
    }

    return TEST_COUNT;
}

int test_button_release(void)
{
    typedef struct TestCase
    {
        WanbeiyuButton *btn;

        errno_t expected_err;
        TestGPIOState expected_state;
    } TestCase;

    TestGPIO gpio[2];
    WanbeiyuButton btn[2];
    test_gpio_init(&gpio[1]);
    assert(wanbeiyu_button_init(&btn[1], (WanbeiyuGPIO *)&gpio[1]) == 0);

    TestCase TEST_CASES[] = {{.btn = NULL, /*   */ .expected_err = EINVAL},
                             {.btn = &btn[1], /**/ .expected_err = 0, .expected_state = TEST_GPIO_HI_Z}};

    TEST_FOR(TEST_CASES)
    {
        errno_t actual_err = wanbeiyu_button_release(TEST_CASE->btn);
        TEST_ASSERT_EQUAL_ERRNO_T(TEST_CASE->expected_err, actual_err);
        if (actual_err != 0)
        {
            continue;
        }

        TestGPIOState actual_state = gpio[TEST_INDEX].state;
        TEST_ASSERT_EQUAL_TEST_GPIO_STATE(TEST_CASE->expected_state, actual_state);
    }

    return TEST_COUNT;
}

int test_button(void)
{
    int count = 0;

    count += test_button_init();
    count += test_button_hold();
    count += test_button_release();

    return count;
}

#endif // TEST_BUTTON_H