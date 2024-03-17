#ifndef WANBEIYU_BUTTON_H
#define WANBEIYU_BUTTON_H

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

#include "gpio.h"

    typedef struct WanbeiyuButton
    {
        WanbeiyuGPIO *gpio;
    } WanbeiyuButton;

    errno_t wanbeiyu_button_init(WanbeiyuButton *, WanbeiyuGPIO *);
    errno_t wanbeiyu_button_hold(WanbeiyuButton *);
    errno_t wanbeiyu_button_release(WanbeiyuButton *);

#ifdef __cplusplus
}
#endif

#endif // WANBEIYU_BUTTON_H