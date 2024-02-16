#ifndef TEST_GPIO_H_
#define TEST_GPIO_H_

typedef enum test_gpio_state_t
{
    TEST_GPIO_STATE_LOW,
    TEST_GPIO_STATE_HI_Z,
} test_gpio_state_t;

typedef struct test_gpio_t
{
    wby_gpio_t parent;
    test_gpio_state_t state;
} test_gpio_t;

void test_gpio_set_low(wby_gpio_t *gpio)
{
    ((test_gpio_t *)gpio)->state = TEST_GPIO_STATE_LOW;
}

void test_gpio_set_hi_z(wby_gpio_t *gpio)
{
    ((test_gpio_t *)gpio)->state = TEST_GPIO_STATE_HI_Z;
}

void test_gpio_init(test_gpio_t *gpio)
{
    gpio->parent.set_low = test_gpio_set_low;
    gpio->parent.set_hi_z = test_gpio_set_hi_z;
    gpio->state = TEST_GPIO_STATE_LOW;
}

#endif // TEST_GPIO_H_