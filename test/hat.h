#ifndef TEST_HAT_H_
#define TEST_HAT_H_

#include "wanbeiyu.h"
#include "test.h"

#include <assert.h>
#include <stdio.h>

int test_hat_init(void)
{
    int cnt = 0;

    typedef struct test_cast_t
    {
        wby_hat_t *hat;
        wby_button_t *up;
        wby_button_t *right;
        wby_button_t *down;
        wby_button_t *left;
        wby_error_t expected;
    } test_cast_t;

    wby_hat_t hat[32];
    test_gpio_t gpio_up[32];
    wby_button_t up[32];
    test_gpio_t gpio_right[32];
    wby_button_t right[32];
    test_gpio_t gpio_down[32];
    wby_button_t down[32];
    test_gpio_t gpio_left[32];
    wby_button_t left[32];
    for (size_t i = 0; i < 32; i++)
    {
        test_gpio_init(&gpio_up[i]);
        assert(wby_button_init(&up[i], (wby_gpio_t *)&gpio_up[i]) == WBY_OK);
        test_gpio_init(&gpio_right[i]);
        assert(wby_button_init(&right[i], (wby_gpio_t *)&gpio_right[i]) == WBY_OK);
        test_gpio_init(&gpio_down[i]);
        assert(wby_button_init(&down[i], (wby_gpio_t *)&gpio_down[i]) == WBY_OK);
        test_gpio_init(&gpio_left[i]);
        assert(wby_button_init(&left[i], (wby_gpio_t *)&gpio_left[i]) == WBY_OK);
    }

    test_cast_t cases[] = {{.hat = NULL, /*    */ .up = NULL, /*   */ .right = NULL, /*      */ .down = NULL, /*     */ .left = NULL, /**/ .expected = WBY_EINVAL},
                           {.hat = &hat[1], /* */ .up = NULL, /*   */ .right = NULL, /*      */ .down = NULL, /*     */ .left = NULL, /**/ .expected = WBY_EINVAL},
                           {.hat = NULL, /*    */ .up = &up[2], /* */ .right = NULL, /*      */ .down = NULL, /*     */ .left = NULL, /**/ .expected = WBY_EINVAL},
                           {.hat = &hat[3], /* */ .up = &up[3], /* */ .right = NULL, /*      */ .down = NULL, /*     */ .left = NULL, /**/ .expected = WBY_EINVAL},
                           {.hat = NULL, /*    */ .up = NULL, /*   */ .right = &right[4], /* */ .down = NULL, /*     */ .left = NULL, /**/ .expected = WBY_EINVAL},
                           {.hat = &hat[5], /* */ .up = NULL, /*   */ .right = &right[5], /* */ .down = NULL, /*     */ .left = NULL, /**/ .expected = WBY_EINVAL},
                           {.hat = NULL, /*    */ .up = &up[6], /* */ .right = &right[6], /* */ .down = NULL, /*     */ .left = NULL, /**/ .expected = WBY_EINVAL},
                           {.hat = &hat[7], /* */ .up = &up[7], /* */ .right = &right[7], /* */ .down = NULL, /*     */ .left = NULL, /**/ .expected = WBY_EINVAL},
                           {.hat = NULL, /*    */ .up = NULL, /*   */ .right = NULL, /*      */ .down = &down[8], /* */ .left = NULL, /**/ .expected = WBY_EINVAL},
                           {.hat = &hat[9], /* */ .up = NULL, /*   */ .right = NULL, /*      */ .down = &down[9], /* */ .left = NULL, /**/ .expected = WBY_EINVAL},
                           {.hat = NULL, /*    */ .up = &up[10], /**/ .right = NULL, /*      */ .down = &down[10], /**/ .left = NULL, /**/ .expected = WBY_EINVAL},
                           {.hat = &hat[11], /**/ .up = &up[11], /**/ .right = NULL, /*      */ .down = &down[11], /**/ .left = NULL, /**/ .expected = WBY_EINVAL},
                           {.hat = NULL, /*    */ .up = NULL, /*   */ .right = &right[12], /**/ .down = &down[12], /**/ .left = NULL, /**/ .expected = WBY_EINVAL},
                           {.hat = &hat[13], /**/ .up = NULL, /*   */ .right = &right[13], /**/ .down = &down[13], /**/ .left = NULL, /**/ .expected = WBY_EINVAL},
                           {.hat = NULL, /*    */ .up = &up[14], /**/ .right = &right[14], /**/ .down = &down[14], /**/ .left = NULL, /**/ .expected = WBY_EINVAL},
                           {.hat = &hat[15], /**/ .up = &up[15], /**/ .right = &right[15], /**/ .down = &down[15], /**/ .left = NULL, /**/ .expected = WBY_EINVAL},
                           {.hat = NULL, /*    */ .up = NULL, /*   */ .right = NULL, /*      */ .down = NULL, /*     */ .left = &left[16], .expected = WBY_EINVAL},
                           {.hat = &hat[17], /**/ .up = NULL, /*   */ .right = NULL, /*      */ .down = NULL, /*     */ .left = &left[17], .expected = WBY_EINVAL},
                           {.hat = NULL, /*    */ .up = &up[18], /**/ .right = NULL, /*      */ .down = NULL, /*     */ .left = &left[18], .expected = WBY_EINVAL},
                           {.hat = &hat[19], /**/ .up = &up[19], /**/ .right = NULL, /*      */ .down = NULL, /*     */ .left = &left[19], .expected = WBY_EINVAL},
                           {.hat = NULL, /*    */ .up = NULL, /*   */ .right = &right[20], /**/ .down = NULL, /*     */ .left = &left[20], .expected = WBY_EINVAL},
                           {.hat = &hat[21], /**/ .up = NULL, /*   */ .right = &right[21], /**/ .down = NULL, /*     */ .left = &left[21], .expected = WBY_EINVAL},
                           {.hat = NULL, /*    */ .up = &up[22], /**/ .right = &right[22], /**/ .down = NULL, /*     */ .left = &left[22], .expected = WBY_EINVAL},
                           {.hat = &hat[23], /**/ .up = &up[23], /**/ .right = &right[23], /**/ .down = NULL, /*     */ .left = &left[23], .expected = WBY_EINVAL},
                           {.hat = NULL, /*    */ .up = NULL, /*   */ .right = NULL, /*      */ .down = &down[24], /**/ .left = &left[24], .expected = WBY_EINVAL},
                           {.hat = &hat[25], /**/ .up = NULL, /*   */ .right = NULL, /*      */ .down = &down[25], /**/ .left = &left[25], .expected = WBY_EINVAL},
                           {.hat = NULL, /*    */ .up = &up[26], /**/ .right = NULL, /*      */ .down = &down[26], /**/ .left = &left[26], .expected = WBY_EINVAL},
                           {.hat = &hat[27], /**/ .up = &up[27], /**/ .right = NULL, /*      */ .down = &down[27], /**/ .left = &left[27], .expected = WBY_EINVAL},
                           {.hat = NULL, /*    */ .up = NULL, /*   */ .right = &right[28], /**/ .down = &down[28], /**/ .left = &left[28], .expected = WBY_EINVAL},
                           {.hat = &hat[29], /**/ .up = NULL, /*   */ .right = &right[29], /**/ .down = &down[29], /**/ .left = &left[29], .expected = WBY_EINVAL},
                           {.hat = NULL, /*    */ .up = &up[30], /**/ .right = &right[30], /**/ .down = &down[30], /**/ .left = &left[30], .expected = WBY_EINVAL},
                           {.hat = &hat[31], /**/ .up = &up[31], /**/ .right = &right[31], /**/ .down = &down[31], /**/ .left = &left[31], .expected = WBY_OK}};
    size_t size = sizeof(cases) / sizeof(test_cast_t);

    for (size_t i = 0; i < size; i++)
    {
        test_cast_t case_ = cases[i];

        wby_error_t actual_ret = wby_hat_init(case_.hat, case_.up, case_.right, case_.down, case_.left);

        if (actual_ret != case_.expected)
        {
            fprintf(stderr, "%sindex: %d, expected_ret: %d, actual_ret: %d%s\n", TEXT_RED, i, case_.expected, actual_ret, TEXT_RESET);
            cnt++;
            continue;
        }

        if (actual_ret != WBY_OK)
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
    int cnt = 0;

    typedef struct test_cast_t
    {
        wby_hat_direction_t dir;
        test_gpio_state_t expected_up_state;
        test_gpio_state_t expected_right_state;
        test_gpio_state_t expected_down_state;
        test_gpio_state_t expected_left_state;
    } test_cast_t;

    test_cast_t cases[] = {{.dir = WBY_HAT_UP, /*       */ .expected_up_state = TEST_GPIO_LOW, .expected_right_state = TEST_GPIO_HI_Z, .expected_down_state = TEST_GPIO_HI_Z, .expected_left_state = TEST_GPIO_HI_Z},
                           {.dir = WBY_HAT_UPRIGHT, /*  */ .expected_up_state = TEST_GPIO_LOW, .expected_right_state = TEST_GPIO_LOW, .expected_down_state = TEST_GPIO_HI_Z, .expected_left_state = TEST_GPIO_HI_Z},
                           {.dir = WBY_HAT_RIGHT, /*    */ .expected_up_state = TEST_GPIO_HI_Z, .expected_right_state = TEST_GPIO_LOW, .expected_down_state = TEST_GPIO_HI_Z, .expected_left_state = TEST_GPIO_HI_Z},
                           {.dir = WBY_HAT_DOWNRIGHT, /**/ .expected_up_state = TEST_GPIO_HI_Z, .expected_right_state = TEST_GPIO_LOW, .expected_down_state = TEST_GPIO_LOW, .expected_left_state = TEST_GPIO_HI_Z},
                           {.dir = WBY_HAT_DOWN, /*     */ .expected_up_state = TEST_GPIO_HI_Z, .expected_right_state = TEST_GPIO_HI_Z, .expected_down_state = TEST_GPIO_LOW, .expected_left_state = TEST_GPIO_HI_Z},
                           {.dir = WBY_HAT_DOWNLEFT, /* */ .expected_up_state = TEST_GPIO_HI_Z, .expected_right_state = TEST_GPIO_HI_Z, .expected_down_state = TEST_GPIO_LOW, .expected_left_state = TEST_GPIO_LOW},
                           {.dir = WBY_HAT_LEFT, /*     */ .expected_up_state = TEST_GPIO_HI_Z, .expected_right_state = TEST_GPIO_HI_Z, .expected_down_state = TEST_GPIO_HI_Z, .expected_left_state = TEST_GPIO_LOW},
                           {.dir = WBY_HAT_UPLEFT, /*   */ .expected_up_state = TEST_GPIO_LOW, .expected_right_state = TEST_GPIO_HI_Z, .expected_down_state = TEST_GPIO_HI_Z, .expected_left_state = TEST_GPIO_LOW},
                           {.dir = WBY_HAT_NEUTRAL, /*  */ .expected_up_state = TEST_GPIO_HI_Z, .expected_right_state = TEST_GPIO_HI_Z, .expected_down_state = TEST_GPIO_HI_Z, .expected_left_state = TEST_GPIO_HI_Z},
                           {.dir = 0b101101, /*         */ .expected_up_state = TEST_GPIO_LOW, .expected_right_state = TEST_GPIO_LOW, .expected_down_state = TEST_GPIO_HI_Z, .expected_left_state = TEST_GPIO_LOW}};
    size_t size = sizeof(cases) / sizeof(test_cast_t);

    wby_hat_t *hat_null = NULL;
    wby_hat_hold(hat_null, WBY_HAT_NEUTRAL); /* Expected that nothing will happen. */

    for (size_t i = 0; i < size; i++)
    {
        test_cast_t case_ = cases[i];

        test_gpio_t gpio[4];
        wby_button_t btn[4];
        for (size_t j = 0; j < 4; j++)
        {
            test_gpio_init(&gpio[j]);
            assert(wby_button_init(&btn[j], (wby_gpio_t *)&gpio[j]) == WBY_OK);
        }
        wby_hat_t hat;
        assert(wby_hat_init(&hat, &btn[0], &btn[1], &btn[2], &btn[3]) == WBY_OK);

        wby_hat_hold(&hat, case_.dir);

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
    int cnt = 0;

    wby_hat_t *hat_null = NULL;
    wby_hat_release(hat_null); /* Expected that nothing will happen. */

    test_gpio_t gpio[4];
    wby_button_t btn[4];
    for (size_t i = 0; i < 4; i++)
    {
        test_gpio_init(&gpio[i]);
        assert(wby_button_init(&btn[i], (wby_gpio_t *)&gpio[i]) == WBY_OK);
    }
    wby_hat_t hat;
    assert(wby_hat_init(&hat, &btn[0], &btn[1], &btn[2], &btn[3]) == WBY_OK);

    wby_hat_release(&hat);

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
    printf("* test_hat\n");
    int cnt = 0;

    printf("  * test_hat_init\n");
    cnt += test_hat_init();
    printf("  * test_hat_hold\n");
    cnt += test_hat_hold();
    printf("  * test_hat_release\n");
    cnt += test_hat_release();

    return cnt;
}

#endif // TEST_HAT_H_