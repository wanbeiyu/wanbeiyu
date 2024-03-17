#include <wanbeiyu/gpio.h>

#include <assert.h>

errno_t wanbeiyu_gpio_set_low(WanbeiyuGPIO *gpio)
{
    if (gpio == NULL)
    {
        return EINVAL;
    }
    assert(gpio->set_low != NULL);

    return gpio->set_low(gpio);
}

errno_t wanbeiyu_gpio_set_hi_z(WanbeiyuGPIO *gpio)
{
    if (gpio == NULL)
    {
        return EINVAL;
    }
    assert(gpio->set_hi_z != NULL);

    return gpio->set_hi_z(gpio);
}