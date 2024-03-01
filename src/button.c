#include <wanbeiyu.h>

#include <assert.h>

WanbeiyuError wanbeiyu_button_init(WanbeiyuButton *btn, WanbeiyuGPIO *gpio)
{
    if (btn == NULL ||
        gpio == NULL)
    {
        return WANBEIYU_EINVAL;
    }

    btn->gpio_ = gpio;

    return WANBEIYU_OK;
}

WanbeiyuError wanbeiyu_button_hold(WanbeiyuButton *btn)
{
    if (btn == NULL)
    {
        return WANBEIYU_EINVAL;
    }
    assert(btn->gpio_ != NULL);

    WanbeiyuError ret = btn->gpio_->set_low(btn->gpio_);
    if (ret != WANBEIYU_OK)
    {
        return WANBEIYU_EIO;
    }

    return WANBEIYU_OK;
}

WanbeiyuError wanbeiyu_button_release(WanbeiyuButton *btn)
{
    if (btn == NULL)
    {
        return WANBEIYU_EINVAL;
    }
    assert(btn->gpio_ != NULL);

    WanbeiyuError ret = btn->gpio_->set_hi_z(btn->gpio_);
    if (ret != WANBEIYU_OK)
    {
        return WANBEIYU_EIO;
    }

    return WANBEIYU_OK;
}