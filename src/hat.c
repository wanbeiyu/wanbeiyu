#include <wanbeiyu.h>

#include <assert.h>

wanbeiyu_error_t wanbeiyu_hat_init(wanbeiyu_hat_t *hat, wanbeiyu_gpio_t *up, wanbeiyu_gpio_t *right, wanbeiyu_gpio_t *down, wanbeiyu_gpio_t *left)
{
    if (hat == NULL ||
        up == NULL ||
        right == NULL ||
        down == NULL ||
        left == NULL)
    {
        return WANBEIYU_EINVAL;
    }

    hat->up_ = up;
    hat->right_ = right;
    hat->down_ = down;
    hat->left_ = left;

    return WANBEIYU_OK;
}

wanbeiyu_error_t wanbeiyu_hat_hold(wanbeiyu_hat_t *hat, wanbeiyu_hat_direction_t dir)
{
    if (hat == NULL ||
        (WANBEIYU_HAT_UP | WANBEIYU_HAT_RIGHT | WANBEIYU_HAT_DOWN | WANBEIYU_HAT_LEFT) < dir)
    {
        return WANBEIYU_EINVAL;
    }
    assert(hat->up_ != NULL &&
           hat->right_ != NULL &&
           hat->down_ != NULL &&
           hat->left_ != NULL);

    wanbeiyu_error_t up_ret = (dir)&WANBEIYU_HAT_UP
                                  ? hat->up_->set_low(hat->up_)
                                  : hat->up_->set_hi_z(hat->up_);
    wanbeiyu_error_t right_ret = (dir)&WANBEIYU_HAT_RIGHT
                                     ? hat->right_->set_low(hat->right_)
                                     : hat->right_->set_hi_z(hat->right_);
    wanbeiyu_error_t down_ret = (dir)&WANBEIYU_HAT_DOWN
                                    ? hat->down_->set_low(hat->down_)
                                    : hat->down_->set_hi_z(hat->down_);
    wanbeiyu_error_t left_ret = (dir)&WANBEIYU_HAT_LEFT
                                    ? hat->left_->set_low(hat->left_)
                                    : hat->left_->set_hi_z(hat->left_);
    if (up_ret != WANBEIYU_OK ||
        right_ret != WANBEIYU_OK ||
        down_ret != WANBEIYU_OK ||
        left_ret != WANBEIYU_OK)
    {
        return WANBEIYU_EIO;
    }

    return WANBEIYU_OK;
}

wanbeiyu_error_t wanbeiyu_hat_release(wanbeiyu_hat_t *hat)
{
    return wanbeiyu_hat_hold(hat, WANBEIYU_HAT_NEUTRAL);
}