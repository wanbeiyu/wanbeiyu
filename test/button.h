#ifndef TEST_BUTTON_H_
#define TEST_BUTTON_H_

#include "wanbeiyu.h"
#include "test.h"

#include <assert.h>
#include <stdio.h>

int test_button_init(void)
{
    int cnt = 0;

    typedef struct test_cast_t
    {
        wby_button_t *btn;
        test_gpio_t *gpio;
        wby_error_t expected_ret;
        test_gpio_state_t expected_state;
    } test_cast_t;

    wby_button_t btn[4];
    test_gpio_t gpio[4];
    for (size_t i = 0; i < 4; i++)
    {
        test_gpio_init(&gpio[i]);
    }

    test_cast_t cases[] = {{.btn = NULL, /*   */ .gpio = NULL, /*    */ .expected_ret = WBY_EINVAL},
                           {.btn = &btn[1], /**/ .gpio = NULL, /*    */ .expected_ret = WBY_EINVAL},
                           {.btn = NULL, /*   */ .gpio = &gpio[2], /**/ .expected_ret = WBY_EINVAL},
                           {.btn = &btn[3], /**/ .gpio = &gpio[3], /**/ .expected_ret = WBY_OK, .expected_state = TEST_GPIO_HI_Z}};
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
    int cnt = 0;

    wby_button_t *btn_null = NULL;
    wby_button_hold(btn_null); /* Expected that nothing will happen. */

    test_gpio_t gpio;
    test_gpio_init(&gpio);
    wby_button_t btn;
    assert(wby_button_init(&btn, (wby_gpio_t *)&gpio) == WBY_OK);

    wby_button_hold(&btn);

    test_gpio_state_t actual_state = gpio.state;

    if (actual_state != TEST_GPIO_LOW)
    {
        fprintf(stderr, "%sindex: %d, expected_state: %d, actual_state: %d%s\n", TEXT_RED, 0, TEST_GPIO_LOW, actual_state, TEXT_RESET);
        cnt++;
    }

    return cnt;
}

int test_button_release(void)
{
    int cnt = 0;

    wby_button_t *btn_null = NULL;
    wby_button_release(btn_null); /* Expected that nothing will happen. */

    test_gpio_t gpio;
    test_gpio_init(&gpio);
    wby_button_t btn;
    assert(wby_button_init(&btn, (wby_gpio_t *)&gpio) == WBY_OK);

    wby_button_release(&btn);

    test_gpio_state_t actual_state = gpio.state;

    if (actual_state != TEST_GPIO_HI_Z)
    {
        fprintf(stderr, "%sindex: %d, expected_state: %d, actual_state: %d%s\n", TEXT_RED, 0, TEST_GPIO_HI_Z, actual_state, TEXT_RESET);
        cnt++;
    }

    return cnt;
}

int test_button(void)
{
    printf("* test_button\n");
    int cnt = 0;

    printf("  * test_button_init\n");
    cnt += test_button_init();
    printf("  * test_button_hold\n");
    cnt += test_button_hold();
    printf("  * test_button_release\n");
    cnt += test_button_release();

    return cnt;
}

#endif // TEST_BUTTON_H_