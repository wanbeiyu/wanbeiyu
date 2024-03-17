#include <wanbeiyu/button.h>

#include <assert.h>

errno_t wanbeiyu_button_init(WanbeiyuButton *btn, WanbeiyuGPIO *gpio)
{
    if (btn == NULL ||
        gpio == NULL)
    {
        return EINVAL;
    }

    btn->gpio = gpio;

    return 0;
}

errno_t wanbeiyu_button_hold(WanbeiyuButton *btn)
{
    if (btn == NULL)
    {
        return EINVAL;
    }
    assert(btn->gpio != NULL);

    errno_t err = btn->gpio->set_low(btn->gpio);
    if (err != 0)
    {
        return EIO;
    }

    return 0;
}

errno_t wanbeiyu_button_release(WanbeiyuButton *btn)
{
    if (btn == NULL)
    {
        return EINVAL;
    }
    assert(btn->gpio != NULL);

    errno_t err = btn->gpio->set_hi_z(btn->gpio);
    if (err != 0)
    {
        return EIO;
    }

    return 0;
}