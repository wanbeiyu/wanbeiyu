#ifndef TEST_HAT_H_
#define TEST_HAT_H_

#include "wanbeiyu.h"
#include "test_gpio.h"

#include <assert.h>
#include <stdio.h>

int test_hat_init(void)
{
    printf("  * test_hat_init\n");
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

    wby_hat_t case_1_hat;
    wby_hat_t case_2_hat;
    wby_hat_t case_3_hat;
    wby_hat_t case_4_hat;
    wby_hat_t case_5_hat;
    wby_hat_t case_6_hat;
    wby_hat_t case_7_hat;
    wby_hat_t case_8_hat;
    wby_hat_t case_9_hat;
    wby_hat_t case_10_hat;
    wby_hat_t case_11_hat;
    wby_hat_t case_12_hat;
    wby_hat_t case_13_hat;
    wby_hat_t case_14_hat;
    wby_hat_t case_15_hat;
    wby_hat_t case_16_hat;

    test_gpio_t gpio_up;
    test_gpio_init(&gpio_up);
    wby_button_t up;
    assert(wby_button_init(&up, (wby_gpio_t *)&gpio_up) == WBY_OK);

    test_gpio_t gpio_right;
    test_gpio_init(&gpio_right);
    wby_button_t right;
    assert(wby_button_init(&right, (wby_gpio_t *)&gpio_right) == WBY_OK);

    test_gpio_t gpio_down;
    test_gpio_init(&gpio_down);
    wby_button_t down;
    assert(wby_button_init(&down, (wby_gpio_t *)&gpio_down) == WBY_OK);

    test_gpio_t gpio_left;
    test_gpio_init(&gpio_left);
    wby_button_t left;
    assert(wby_button_init(&left, (wby_gpio_t *)&gpio_left) == WBY_OK);

    test_cast_t cases[] = {{.hat = NULL, .up = NULL, .right = NULL, .down = NULL, .left = NULL, .expected = WBY_EINVAL},
                           {.hat = &case_1_hat, .up = NULL, .right = NULL, .down = NULL, .left = NULL, .expected = WBY_EINVAL},
                           {.hat = &case_2_hat, .up = &up, .right = NULL, .down = NULL, .left = NULL, .expected = WBY_EINVAL},
                           {.hat = &case_3_hat, .up = NULL, .right = &right, .down = NULL, .left = NULL, .expected = WBY_EINVAL},
                           {.hat = &case_4_hat, .up = &up, .right = &right, .down = NULL, .left = NULL, .expected = WBY_EINVAL},
                           {.hat = &case_5_hat, .up = NULL, .right = NULL, .down = &down, .left = NULL, .expected = WBY_EINVAL},
                           {.hat = &case_6_hat, .up = &up, .right = NULL, .down = &down, .left = NULL, .expected = WBY_EINVAL},
                           {.hat = &case_7_hat, .up = NULL, .right = &right, .down = &down, .left = NULL, .expected = WBY_EINVAL},
                           {.hat = &case_8_hat, .up = &up, .right = &right, .down = &down, .left = NULL, .expected = WBY_EINVAL},
                           {.hat = &case_9_hat, .up = NULL, .right = NULL, .down = NULL, .left = &left, .expected = WBY_EINVAL},
                           {.hat = &case_10_hat, .up = &up, .right = NULL, .down = NULL, .left = &left, .expected = WBY_EINVAL},
                           {.hat = &case_11_hat, .up = NULL, .right = &right, .down = NULL, .left = &left, .expected = WBY_EINVAL},
                           {.hat = &case_12_hat, .up = &up, .right = &right, .down = NULL, .left = &left, .expected = WBY_EINVAL},
                           {.hat = &case_13_hat, .up = NULL, .right = NULL, .down = &down, .left = &left, .expected = WBY_EINVAL},
                           {.hat = &case_14_hat, .up = &up, .right = NULL, .down = &down, .left = &left, .expected = WBY_EINVAL},
                           {.hat = &case_15_hat, .up = NULL, .right = &right, .down = &down, .left = &left, .expected = WBY_EINVAL},
                           {.hat = &case_16_hat, .up = &up, .right = &right, .down = &down, .left = &left, .expected = WBY_OK}};
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

        if (gpio_up.state != TEST_GPIO_HI_Z ||
            gpio_right.state != TEST_GPIO_HI_Z ||
            gpio_down.state != TEST_GPIO_HI_Z ||
            gpio_left.state != TEST_GPIO_HI_Z)
        {
            fprintf(stderr, "%sindex: %d, expected_state: %d, %d, %d, %d, actual_state: %d, %d, %d, %d%s\n",
                    TEXT_RED, i, TEST_GPIO_HI_Z, TEST_GPIO_HI_Z, TEST_GPIO_HI_Z, TEST_GPIO_HI_Z,
                    gpio_up.state, gpio_right.state, gpio_down.state, gpio_left.state, TEXT_RESET);
            cnt++;
        }
    }
    return cnt;
}

int test_hat_hold(void)
{
    printf("  * test_hat_hold\n");
    int cnt = 0;

    typedef struct test_cast_t
    {
        wby_hat_direction_t dir;
        test_gpio_state_t expected_up_state;
        test_gpio_state_t expected_right_state;
        test_gpio_state_t expected_down_state;
        test_gpio_state_t expected_left_state;
    } test_cast_t;

    test_cast_t cases[] = {{.dir = WBY_HAT_UP, .expected_up_state = TEST_GPIO_LOW, .expected_right_state = TEST_GPIO_HI_Z, .expected_down_state = TEST_GPIO_HI_Z, .expected_left_state = TEST_GPIO_HI_Z},
                           {.dir = WBY_HAT_UPRIGHT, .expected_up_state = TEST_GPIO_LOW, .expected_right_state = TEST_GPIO_LOW, .expected_down_state = TEST_GPIO_HI_Z, .expected_left_state = TEST_GPIO_HI_Z},
                           {.dir = WBY_HAT_RIGHT, .expected_up_state = TEST_GPIO_HI_Z, .expected_right_state = TEST_GPIO_LOW, .expected_down_state = TEST_GPIO_HI_Z, .expected_left_state = TEST_GPIO_HI_Z},
                           {.dir = WBY_HAT_DOWNRIGHT, .expected_up_state = TEST_GPIO_HI_Z, .expected_right_state = TEST_GPIO_LOW, .expected_down_state = TEST_GPIO_LOW, .expected_left_state = TEST_GPIO_HI_Z},
                           {.dir = WBY_HAT_DOWN, .expected_up_state = TEST_GPIO_HI_Z, .expected_right_state = TEST_GPIO_HI_Z, .expected_down_state = TEST_GPIO_LOW, .expected_left_state = TEST_GPIO_HI_Z},
                           {.dir = WBY_HAT_DOWNLEFT, .expected_up_state = TEST_GPIO_HI_Z, .expected_right_state = TEST_GPIO_HI_Z, .expected_down_state = TEST_GPIO_LOW, .expected_left_state = TEST_GPIO_LOW},
                           {.dir = WBY_HAT_LEFT, .expected_up_state = TEST_GPIO_HI_Z, .expected_right_state = TEST_GPIO_HI_Z, .expected_down_state = TEST_GPIO_HI_Z, .expected_left_state = TEST_GPIO_LOW},
                           {.dir = WBY_HAT_UPLEFT, .expected_up_state = TEST_GPIO_LOW, .expected_right_state = TEST_GPIO_HI_Z, .expected_down_state = TEST_GPIO_HI_Z, .expected_left_state = TEST_GPIO_LOW},
                           {.dir = WBY_HAT_NEUTRAL, .expected_up_state = TEST_GPIO_HI_Z, .expected_right_state = TEST_GPIO_HI_Z, .expected_down_state = TEST_GPIO_HI_Z, .expected_left_state = TEST_GPIO_HI_Z},
                           {.dir = 0b101101 /* Bits higher than the fourth digit are ignored. */, .expected_up_state = TEST_GPIO_LOW, .expected_right_state = TEST_GPIO_LOW, .expected_down_state = TEST_GPIO_HI_Z, .expected_left_state = TEST_GPIO_LOW}};
    size_t size = sizeof(cases) / sizeof(test_cast_t);

    for (size_t i = 0; i < size; i++)
    {
        test_cast_t case_ = cases[i];

        test_gpio_t gpios[4];
        wby_button_t btns[4];
        for (size_t j = 0; j < 4; j++)
        {
            test_gpio_init(&gpios[j]);
            assert(wby_button_init(&btns[j], (wby_gpio_t *)&gpios[j]) == WBY_OK);
        }

        wby_hat_t hat;
        assert(wby_hat_init(&hat, &btns[0], &btns[1], &btns[2], &btns[3]) == WBY_OK);

        wby_hat_hold(&hat, case_.dir);

        if (gpios[0].state != case_.expected_up_state ||
            gpios[1].state != case_.expected_right_state ||
            gpios[2].state != case_.expected_down_state ||
            gpios[3].state != case_.expected_left_state)
        {
            fprintf(stderr, "%sindex: %d, expected_state: %d, %d, %d, %d, actual_state: %d, %d, %d, %d%s\n",
                    TEXT_RED, i, case_.expected_up_state, case_.expected_right_state, case_.expected_down_state, case_.expected_left_state,
                    gpios[0].state, gpios[1].state, gpios[2].state, gpios[3].state, TEXT_RESET);
            cnt++;
        }
    }

    return cnt;
}

int test_hat_release(void)
{
    printf("  * test_hat_release\n");
    int cnt = 0;

    typedef struct test_cast_t
    {
        wby_hat_t *hat;
        test_gpio_t *gpios;
    } test_cast_t;

    test_gpio_t case_1_gpios[4];
    wby_button_t case_1_btns[4];
    for (size_t j = 0; j < 4; j++)
    {
        test_gpio_init(&case_1_gpios[j]);
        assert(wby_button_init(&case_1_btns[j], (wby_gpio_t *)&case_1_gpios[j]) == WBY_OK);
    }
    wby_hat_t case_1_hat;
    assert(wby_hat_init(&case_1_hat, &case_1_btns[0], &case_1_btns[1], &case_1_btns[2], &case_1_btns[3]) == WBY_OK);

    test_cast_t cases[] = {{.hat = NULL, .gpios = NULL},
                           {.hat = &case_1_hat, .gpios = case_1_gpios}};
    size_t size = sizeof(cases) / sizeof(test_cast_t);

    for (size_t i = 0; i < size; i++)
    {
        test_cast_t case_ = cases[i];

        wby_hat_release(case_.hat);

        if (case_.gpios == NULL)
        {
            continue;
        }

        if (case_.gpios[0].state != TEST_GPIO_HI_Z ||
            case_.gpios[1].state != TEST_GPIO_HI_Z ||
            case_.gpios[2].state != TEST_GPIO_HI_Z ||
            case_.gpios[3].state != TEST_GPIO_HI_Z)
        {
            fprintf(stderr, "%sindex: %d, expected_state: %d, %d, %d, %d, actual_state: %d, %d, %d, %d%s\n",
                    TEXT_RED, i, TEST_GPIO_HI_Z, TEST_GPIO_HI_Z, TEST_GPIO_HI_Z, TEST_GPIO_HI_Z,
                    case_.gpios[0].state, case_.gpios[1].state, case_.gpios[2].state, case_.gpios[3].state, TEXT_RESET);
            cnt++;
        }
    }

    return cnt;
}

int test_hat(void)
{
    printf("* test_hat\n");
    int cnt = 0;

    cnt += test_hat_init();
    cnt += test_hat_hold();
    cnt += test_hat_release();

    return cnt;
}

#endif // TEST_HAT_H_