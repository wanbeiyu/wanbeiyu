#include <wanbeiyu/hat.h>

#include <assert.h>

errno_t wanbeiyu_hat_init(WanbeiyuHat *hat, WanbeiyuGPIO *up, WanbeiyuGPIO *right, WanbeiyuGPIO *down, WanbeiyuGPIO *left)
{
    if (hat == NULL ||
        up == NULL ||
        right == NULL ||
        down == NULL ||
        left == NULL)
    {
        return EINVAL;
    }

    hat->up = up;
    hat->right = right;
    hat->down = down;
    hat->left = left;

    return 0;
}

errno_t wanbeiyu_hat_hold(WanbeiyuHat *hat, WanbeiyuHatDirection dir)
{
    if (hat == NULL ||
        (WANBEIYU_HAT_UP | WANBEIYU_HAT_RIGHT | WANBEIYU_HAT_DOWN | WANBEIYU_HAT_LEFT) < dir)
    {
        return EINVAL;
    }
    assert(hat->up != NULL &&
           hat->right != NULL &&
           hat->down != NULL &&
           hat->left != NULL);

    errno_t up_err = dir & WANBEIYU_HAT_UP
                         ? wanbeiyu_gpio_set_low(hat->up)
                         : wanbeiyu_gpio_set_hi_z(hat->up);
    errno_t right_err = dir & WANBEIYU_HAT_RIGHT
                            ? wanbeiyu_gpio_set_low(hat->right)
                            : wanbeiyu_gpio_set_hi_z(hat->right);
    errno_t down_err = dir & WANBEIYU_HAT_DOWN
                           ? wanbeiyu_gpio_set_low(hat->down)
                           : wanbeiyu_gpio_set_hi_z(hat->down);
    errno_t left_err = dir & WANBEIYU_HAT_LEFT
                           ? wanbeiyu_gpio_set_low(hat->left)
                           : wanbeiyu_gpio_set_hi_z(hat->left);
    if (up_err != 0 ||
        right_err != 0 ||
        down_err != 0 ||
        left_err != 0)
    {
        return EIO;
    }

    return 0;
}

errno_t wanbeiyu_hat_release(WanbeiyuHat *hat)
{
    return wanbeiyu_hat_hold(hat, WANBEIYU_HAT_NEUTRAL);
}