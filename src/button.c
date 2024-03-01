#include <wanbeiyu.h>

#include <assert.h>

WanbeiyuErrNo wanbeiyu_button_init(WanbeiyuButton *btn, WanbeiyuGPIO *gpio)
{
    if (btn == NULL ||
        gpio == NULL)
    {
        return WANBEIYU_EINVAL;
    }

    btn->gpio = gpio;

    return WANBEIYU_OK;
}

WanbeiyuErrNo wanbeiyu_button_hold(WanbeiyuButton *btn)
{
    if (btn == NULL)
    {
        return WANBEIYU_EINVAL;
    }
    assert(btn->gpio != NULL);

    WanbeiyuErrNo ret = btn->gpio->set_low(btn->gpio);
    if (ret != WANBEIYU_OK)
    {
        return WANBEIYU_EIO;
    }

    return WANBEIYU_OK;
}

WanbeiyuErrNo wanbeiyu_button_release(WanbeiyuButton *btn)
{
    if (btn == NULL)
    {
        return WANBEIYU_EINVAL;
    }
    assert(btn->gpio != NULL);

    WanbeiyuErrNo ret = btn->gpio->set_hi_z(btn->gpio);
    if (ret != WANBEIYU_OK)
    {
        return WANBEIYU_EIO;
    }

    return WANBEIYU_OK;
}