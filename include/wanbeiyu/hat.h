#ifndef WANBEIYU_HAT_H
#define WANBEIYU_HAT_H

#ifdef __cplusplus
extern "C"
{
#endif

#ifndef __STDC_WANT_LIB_EXT1__
#define __STDC_WANT_LIB_EXT1__ 1
#endif

#include <errno.h>
#ifndef __STDC_LIB_EXT1__
    typedef int errno_t;
#endif
#include <stddef.h>
#include <stdint.h>

#include "gpio.h"

    typedef struct WanbeiyuHat
    {
        WanbeiyuGPIO *up;
        WanbeiyuGPIO *right;
        WanbeiyuGPIO *down;
        WanbeiyuGPIO *left;
    } WanbeiyuHat;

    typedef uint8_t WanbeiyuHatDirection;

#define WANBEIYU_HAT_NEUTRAL /*  */ ((WanbeiyuHatDirection)0)                                        /* 0b0000 */
#define WANBEIYU_HAT_LEFT /*     */ ((WanbeiyuHatDirection)1)                                        /* 0b0001 */
#define WANBEIYU_HAT_DOWN /*     */ ((WanbeiyuHatDirection)2)                                        /* 0b0010 */
#define WANBEIYU_HAT_RIGHT /*    */ ((WanbeiyuHatDirection)4)                                        /* 0b0100 */
#define WANBEIYU_HAT_UP /*       */ ((WanbeiyuHatDirection)8)                                        /* 0b1000 */
#define WANBEIYU_HAT_UPRIGHT /*  */ ((WanbeiyuHatDirection)(WANBEIYU_HAT_UP | WANBEIYU_HAT_RIGHT))   /* 0b1100 */
#define WANBEIYU_HAT_DOWNRIGHT /**/ ((WanbeiyuHatDirection)(WANBEIYU_HAT_DOWN | WANBEIYU_HAT_RIGHT)) /* 0b0110 */
#define WANBEIYU_HAT_DOWNLEFT /* */ ((WanbeiyuHatDirection)(WANBEIYU_HAT_DOWN | WANBEIYU_HAT_LEFT))  /* 0b0011 */
#define WANBEIYU_HAT_UPLEFT /*   */ ((WanbeiyuHatDirection)(WANBEIYU_HAT_UP | WANBEIYU_HAT_LEFT))    /* 0b1001 */

    errno_t wanbeiyu_hat_init(WanbeiyuHat *, WanbeiyuGPIO *, WanbeiyuGPIO *, WanbeiyuGPIO *, WanbeiyuGPIO *);
    errno_t wanbeiyu_hat_hold(WanbeiyuHat *, WanbeiyuHatDirection);
    errno_t wanbeiyu_hat_release(WanbeiyuHat *);

#ifdef __cplusplus
}
#endif

#endif // WANBEIYU_HAT_H