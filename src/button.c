#include <wanbeiyu.h>

#include <assert.h>

wanbeiyu_error_t wanbeiyu_button_init(wanbeiyu_button_t *btn, wanbeiyu_gpio_t *gpio)
{
    if (btn == NULL ||
        gpio == NULL)
    {
        return WANBEIYU_EINVAL;
    }

    btn->gpio_ = gpio;

    return WANBEIYU_OK;
}

wanbeiyu_error_t wanbeiyu_button_hold(wanbeiyu_button_t *btn)
{
    if (btn == NULL)
    {
        return WANBEIYU_EINVAL;
    }
    assert(btn->gpio_ != NULL);

    wanbeiyu_error_t ret = btn->gpio_->set_low(btn->gpio_);
    if (ret != WANBEIYU_OK)
    {
        return WANBEIYU_EIO;
    }

    return WANBEIYU_OK;
}

wanbeiyu_error_t wanbeiyu_button_release(wanbeiyu_button_t *btn)
{
    if (btn == NULL)
    {
        return WANBEIYU_EINVAL;
    }
    assert(btn->gpio_ != NULL);

    wanbeiyu_error_t ret = btn->gpio_->set_hi_z(btn->gpio_);
    if (ret != WANBEIYU_OK)
    {
        return WANBEIYU_EIO;
    }

    return WANBEIYU_OK;
}