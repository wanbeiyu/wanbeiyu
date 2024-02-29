#ifndef TEST_BUTTON_H_
#define TEST_BUTTON_H_

#include "wanbeiyu.h"
#include "test.h"

#include <assert.h>
#include <stdio.h>

int test_button_init(void)
{
    printf("  * %s\n", __func__);
    int cnt = 0;

    typedef struct test_case_t
    {
        wanbeiyu_button_t *btn;
        test_gpio_t *gpio;

        wanbeiyu_error_t expected_ret;
        test_gpio_state_t expected_state;
    } test_case_t;

    wanbeiyu_button_t btn[4];
    test_gpio_t gpio[4];
    for (size_t i = 0; i < 4; i++)
    {
        test_gpio_init(&gpio[i]);
    }

    test_case_t cases[] = {{.btn = NULL, /*   */ .gpio = NULL, /*    */ .expected_ret = WANBEIYU_EINVAL},
                           {.btn = &btn[1], /**/ .gpio = NULL, /*    */ .expected_ret = WANBEIYU_EINVAL},
                           {.btn = NULL, /*   */ .gpio = &gpio[2], /**/ .expected_ret = WANBEIYU_EINVAL},
                           {.btn = &btn[3], /**/ .gpio = &gpio[3], /**/ .expected_ret = WANBEIYU_OK, .expected_state = TEST_GPIO_HI_Z}};

    TEST_FOR(cases)
    {
        wanbeiyu_error_t actual_ret = wanbeiyu_button_init(case_.btn, (wanbeiyu_gpio_t *)case_.gpio);
        TEST_ASSERT_EQUAL_WANBEIYU_ERROR_RET(case_.expected_ret, actual_ret);
        if (actual_ret != WANBEIYU_OK)
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
    printf("  * %s\n", __func__);
    int cnt = 0;

    wanbeiyu_button_t *btn_null = NULL;
    wanbeiyu_button_hold(btn_null); /* Expected that nothing will happen. */

    test_gpio_t gpio;
    test_gpio_init(&gpio);
    wanbeiyu_button_t btn;
    assert(wanbeiyu_button_init(&btn, (wanbeiyu_gpio_t *)&gpio) == WANBEIYU_OK);

    wanbeiyu_button_hold(&btn);

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
    printf("  * %s\n", __func__);
    int cnt = 0;

    wanbeiyu_button_t *btn_null = NULL;
    wanbeiyu_button_release(btn_null); /* Expected that nothing will happen. */

    test_gpio_t gpio;
    test_gpio_init(&gpio);
    wanbeiyu_button_t btn;
    assert(wanbeiyu_button_init(&btn, (wanbeiyu_gpio_t *)&gpio) == WANBEIYU_OK);

    wanbeiyu_button_release(&btn);

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
    printf("* %s\n", __func__);
    int cnt = 0;

    cnt += test_button_init();
    cnt += test_button_hold();
    cnt += test_button_release();

    return cnt;
}

#endif // TEST_BUTTON_H_