#ifndef TEST_BUTTON_H_
#define TEST_BUTTON_H_

#include "wanbeiyu.h"
#include "test_gpio.h"

#include <assert.h>
#include <stdio.h>

int test_button_init(void)
{
    printf("* test_button_init\n");
    int ret = 0;

    typedef struct test_cast_t
    {
        test_gpio_t *gpio;
        wby_error_t expected_ret;
        test_gpio_state_t expected_state;
    } test_cast_t;

    test_gpio_t case_1_gpio;
    case_1_gpio.parent.set_hi_z = test_gpio_set_hi_z;
    case_1_gpio.state = TEST_GPIO_STATE_LOW;

    test_gpio_t case_2_gpio;
    case_2_gpio.parent.set_hi_z = test_gpio_einval;

    test_cast_t cases[] = {{.gpio = NULL, .expected_ret = WBY_EINVAL},
                           {.gpio = &case_1_gpio, .expected_ret = WBY_OK, .expected_state = TEST_GPIO_STATE_HI_Z},
                           {.gpio = &case_2_gpio, .expected_ret = WBY_EINVAL}};
    size_t size = sizeof(cases) / sizeof(test_cast_t);

    for (size_t i = 0; i < size; i++)
    {
        test_cast_t case_ = cases[i];

        wby_button_t btn;
        wby_error_t actual_ret = wby_button_init(&btn, (wby_gpio_t *)case_.gpio);

        if (actual_ret != case_.expected_ret)
        {
            fprintf(stderr, "%sindex: %d, expected_ret: %d, actual_ret: %d%s\n", TEXT_RED, i, case_.expected_ret, actual_ret, TEXT_RESET);
            ret++;
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
            ret++;
        }
    }

    return ret;
}

int test_button_hold(void)
{
    printf("* test_button_hold\n");
    int ret = 0;

    typedef struct test_cast_t
    {
        test_gpio_t *gpio;
        wby_error_t expected_ret;
        test_gpio_state_t expected_state;
    } test_cast_t;

    test_gpio_t case_0_gpio;
    case_0_gpio.parent.set_low = test_gpio_set_low;
    case_0_gpio.parent.set_hi_z = test_gpio_set_hi_z;

    test_gpio_t case_1_gpio;
    case_1_gpio.parent.set_low = test_gpio_einval;
    case_1_gpio.parent.set_hi_z = test_gpio_set_hi_z;

    test_cast_t cases[] = {{.gpio = &case_0_gpio, .expected_ret = WBY_OK, .expected_state = TEST_GPIO_STATE_LOW},
                           {.gpio = &case_1_gpio, .expected_ret = WBY_EINVAL}};
    size_t size = sizeof(cases) / sizeof(test_cast_t);

    for (size_t i = 0; i < size; i++)
    {
        test_cast_t case_ = cases[i];

        wby_button_t btn;
        assert(wby_button_init(&btn, (wby_gpio_t *)case_.gpio) == WBY_OK);

        wby_error_t actual_ret = wby_button_hold(&btn);

        if (actual_ret != case_.expected_ret)
        {
            fprintf(stderr, "%sindex: %d, expected_ret: %d, actual_ret: %d%s\n", TEXT_RED, i, case_.expected_ret, actual_ret, TEXT_RESET);
            ret++;
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
            ret++;
        }
    }

    return ret;
}

int test_button_release(void)
{
    printf("* test_button_release\n");
    int ret = 0;

    typedef struct test_cast_t
    {
        test_gpio_t *gpio;
        wby_error_t expected_ret;
        test_gpio_state_t expected_state;
    } test_cast_t;

    test_gpio_t case_0_gpio;
    case_0_gpio.parent.set_hi_z = test_gpio_set_hi_z;

    test_gpio_t case_1_gpio;
    case_1_gpio.parent.set_hi_z = test_gpio_set_hi_z_only_once;

    test_cast_t cases[] = {{.gpio = &case_0_gpio, .expected_ret = WBY_OK, .expected_state = TEST_GPIO_STATE_HI_Z},
                           {.gpio = &case_1_gpio, .expected_ret = WBY_EINVAL}};
    size_t size = sizeof(cases) / sizeof(test_cast_t);

    for (size_t i = 0; i < size; i++)
    {
        test_cast_t case_ = cases[i];

        wby_button_t btn;
        assert(wby_button_init(&btn, (wby_gpio_t *)case_.gpio) == WBY_OK);

        wby_error_t actual_ret = wby_button_release(&btn);

        if (actual_ret != case_.expected_ret)
        {
            fprintf(stderr, "%sindex: %d, expected_ret: %d, actual_ret: %d%s\n", TEXT_RED, i, case_.expected_ret, actual_ret, TEXT_RESET);
            ret++;
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
            ret++;
        }
    }

    return ret;
}

int test_button(void)
{
    int ret = 0;
    ret += test_button_init();
    ret += test_button_hold();
    ret += test_button_release();
    return ret;
}

#endif // TEST_BUTTON_H_