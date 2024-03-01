#include <wanbeiyu.h>

#include <assert.h>

WanbeiyuError wanbeiyu_hat_init(WanbeiyuHat *hat, WanbeiyuGPIO *up, WanbeiyuGPIO *right, WanbeiyuGPIO *down, WanbeiyuGPIO *left)
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

WanbeiyuError wanbeiyu_hat_hold(WanbeiyuHat *hat, WanbeiyuHatDirection dir)
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

    WanbeiyuError up_ret = (dir)&WANBEIYU_HAT_UP
                                  ? hat->up_->set_low(hat->up_)
                                  : hat->up_->set_hi_z(hat->up_);
    WanbeiyuError right_ret = (dir)&WANBEIYU_HAT_RIGHT
                                     ? hat->right_->set_low(hat->right_)
                                     : hat->right_->set_hi_z(hat->right_);
    WanbeiyuError down_ret = (dir)&WANBEIYU_HAT_DOWN
                                    ? hat->down_->set_low(hat->down_)
                                    : hat->down_->set_hi_z(hat->down_);
    WanbeiyuError left_ret = (dir)&WANBEIYU_HAT_LEFT
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

WanbeiyuError wanbeiyu_hat_release(WanbeiyuHat *hat)
{
    return wanbeiyu_hat_hold(hat, WANBEIYU_HAT_NEUTRAL);
}