#include "wanbeiyu.h"

#include <stdlib.h>

typedef enum TestGPIOState
{
    TEST_GPIO_LOW,
    TEST_GPIO_HIGH,
    TEST_GPIO_HI_Z
} TestGPIOState;

typedef struct TestGPIO
{
    wby_gpio_t parent;
    TestGPIOState state;
} TestGPIO;

static wby_error_t _test_gpio_set_low(wby_gpio_t *parent)
{
    TestGPIO *self = (TestGPIO *)parent;
    self->state = TEST_GPIO_LOW;

    return WBY_OK;
}

static wby_error_t _test_gpio_set_hi_z(wby_gpio_t *parent)
{
    TestGPIO *self = (TestGPIO *)parent;
    self->state = TEST_GPIO_HI_Z;

    return WBY_OK;
}

TestGPIO *test_gpio_new(void)
{
    TestGPIO *self = (TestGPIO *)malloc(sizeof(TestGPIO));
    if (self == NULL)
    {
        return NULL;
    }

    self->parent.set_low = _test_gpio_set_low;
    self->parent.set_hi_z = _test_gpio_set_hi_z;

    self->state = TEST_GPIO_HI_Z;

    return self;
}

void test_gpio_delete(TestGPIO *self)
{
    free(self);
}