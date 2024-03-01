#include <wanbeiyu.h>

#include <assert.h>

WanbeiyuErrNo wanbeiyu_hat_init(WanbeiyuHat *hat, WanbeiyuGPIO *up, WanbeiyuGPIO *right, WanbeiyuGPIO *down, WanbeiyuGPIO *left)
{
    if (hat == NULL ||
        up == NULL ||
        right == NULL ||
        down == NULL ||
        left == NULL)
    {
        return WANBEIYU_EINVAL;
    }

    hat->up = up;
    hat->right = right;
    hat->down = down;
    hat->left = left;

    return WANBEIYU_OK;
}

WanbeiyuErrNo wanbeiyu_hat_hold(WanbeiyuHat *hat, WanbeiyuHatDirection dir)
{
    if (hat == NULL ||
        (WANBEIYU_HAT_UP | WANBEIYU_HAT_RIGHT | WANBEIYU_HAT_DOWN | WANBEIYU_HAT_LEFT) < dir)
    {
        return WANBEIYU_EINVAL;
    }
    assert(hat->up != NULL &&
           hat->right != NULL &&
           hat->down != NULL &&
           hat->left != NULL);

    WanbeiyuErrNo up_ret = (dir)&WANBEIYU_HAT_UP
                               ? hat->up->set_low(hat->up)
                               : hat->up->set_hi_z(hat->up);
    WanbeiyuErrNo right_ret = (dir)&WANBEIYU_HAT_RIGHT
                                  ? hat->right->set_low(hat->right)
                                  : hat->right->set_hi_z(hat->right);
    WanbeiyuErrNo down_ret = (dir)&WANBEIYU_HAT_DOWN
                                 ? hat->down->set_low(hat->down)
                                 : hat->down->set_hi_z(hat->down);
    WanbeiyuErrNo left_ret = (dir)&WANBEIYU_HAT_LEFT
                                 ? hat->left->set_low(hat->left)
                                 : hat->left->set_hi_z(hat->left);
    if (up_ret != WANBEIYU_OK ||
        right_ret != WANBEIYU_OK ||
        down_ret != WANBEIYU_OK ||
        left_ret != WANBEIYU_OK)
    {
        return WANBEIYU_EIO;
    }

    return WANBEIYU_OK;
}

WanbeiyuErrNo wanbeiyu_hat_release(WanbeiyuHat *hat)
{
    return wanbeiyu_hat_hold(hat, WANBEIYU_HAT_NEUTRAL);
}