#ifndef TEST_BUTTON_H_
#define TEST_BUTTON_H_

#include "wanbeiyu.h"
#include "test_gpio.h"

#include <assert.h>
#include <stdio.h>

int test_button_init(void)
{
    printf("  * test_button_init\n");
    int cnt = 0;

    typedef struct test_cast_t
    {
        wby_button_t *btn;
        test_gpio_t *gpio;
        wby_error_t expected_ret;
        test_gpio_state_t expected_state;
    } test_cast_t;

    wby_button_t case_1_btn;

    wby_button_t case_2_btn;
    test_gpio_t case_2_gpio;
    test_gpio_init(&case_2_gpio);

    test_cast_t cases[] = {{.btn = NULL, .gpio = NULL, .expected_ret = WBY_EINVAL},
                           {.btn = &case_1_btn, .gpio = NULL, .expected_ret = WBY_EINVAL},
                           {.btn = &case_2_btn, .gpio = &case_2_gpio, .expected_ret = WBY_OK, .expected_state = TEST_GPIO_HI_Z}};
    size_t size = sizeof(cases) / sizeof(test_cast_t);

    for (size_t i = 0; i < size; i++)
    {
        test_cast_t case_ = cases[i];

        wby_error_t actual_ret = wby_button_init(case_.btn, (wby_gpio_t *)case_.gpio);

        if (actual_ret != case_.expected_ret)
        {
            fprintf(stderr, "%sindex: %d, expected_ret: %d, actual_ret: %d%s\n", TEXT_RED, i, case_.expected_ret, actual_ret, TEXT_RESET);
            cnt++;
            continue;
        }

        if (actual_ret != WBY_OK)
        {
            continue;
        }

        test_gpio_state_t actual_state = case_.gpio->state;

        if (actual_state != case_.expected_state)
        {
            fprintf(stderr, "%sindex: %d, expected_state: %d, actual_state: %d%s\n", TEXT_RED, i, case_.expected_state, actual_state, TEXT_RESET);
            cnt++;
        }
    }

    return cnt;
}

int test_button_hold(void)
{
    printf("  * test_button_hold\n");
    int cnt = 0;

    typedef struct test_cast_t
    {
        wby_button_t *btn;
        test_gpio_t *gpio;
        test_gpio_state_t expected;
    } test_cast_t;

    test_gpio_t case_1_gpio;
    test_gpio_init(&case_1_gpio);
    wby_button_t case_1_btn;
    assert(wby_button_init(&case_1_btn, (wby_gpio_t *)&case_1_gpio) == WBY_OK);

    test_cast_t cases[] = {{.btn = NULL, .gpio = NULL},
                           {.btn = &case_1_btn, .gpio = &case_1_gpio, .expected = TEST_GPIO_LOW}};
    size_t size = sizeof(cases) / sizeof(test_cast_t);

    for (size_t i = 0; i < size; i++)
    {
        test_cast_t case_ = cases[i];

        wby_button_hold(case_.btn);

        if (case_.gpio == NULL)
        {
            continue;
        }

        test_gpio_state_t actual_state = case_.gpio->state;

        if (actual_state != case_.expected)
        {
            fprintf(stderr, "%sindex: %d, expected_state: %d, actual_state: %d%s\n", TEXT_RED, i, case_.expected, actual_state, TEXT_RESET);
            cnt++;
        }
    }

    return cnt;
}

int test_button_release(void)
{
    printf("  * test_button_release\n");
    int cnt = 0;

    typedef struct test_cast_t
    {
        wby_button_t *btn;
        test_gpio_t *gpio;
        test_gpio_state_t expected;
    } test_cast_t;

    test_gpio_t case_1_gpio;
    test_gpio_init(&case_1_gpio);
    wby_button_t case_1_btn;
    assert(wby_button_init(&case_1_btn, (wby_gpio_t *)&case_1_gpio) == WBY_OK);

    test_cast_t cases[] = {{.btn = NULL, .gpio = NULL},
                           {.btn = &case_1_btn, .gpio = &case_1_gpio, .expected = TEST_GPIO_HI_Z}};
    size_t size = sizeof(cases) / sizeof(test_cast_t);

    for (size_t i = 0; i < size; i++)
    {
        test_cast_t case_ = cases[i];

        wby_button_release(case_.btn);

        if (case_.gpio == NULL)
        {
            continue;
        }

        test_gpio_state_t actual_state = case_.gpio->state;

        if (actual_state != case_.expected)
        {
            fprintf(stderr, "%sindex: %d, expected_state: %d, actual_state: %d%s\n", TEXT_RED, i, case_.expected, actual_state, TEXT_RESET);
            cnt++;
        }
    }

    return cnt;
}

int test_button(void)
{
    printf("* test_button\n");
    int cnt = 0;

    cnt += test_button_init();
    cnt += test_button_hold();
    cnt += test_button_release();

    return cnt;
}

#endif // TEST_BUTTON_H_