#ifndef WANBEIYU_TOUCHSCREEN_H
#define WANBEIYU_TOUCHSCREEN_H

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

#include "rdac.h"
#include "spst_switch.h"

    typedef struct WanbeiyuTouchscreen
    {
        WanbeiyuRDAC *horizontal;
        WanbeiyuRDAC *vertical;
        WanbeiyuSPSTSwitch *switch_;
    } WanbeiyuTouchscreen;

#define WANBEIYU_TOUCHSCREEN_X_MAX ((uint16_t)319)
#define WANBEIYU_TOUCHSCREEN_Y_MAX ((uint8_t)239)

    errno_t wanbeiyu_touchscreen_init(WanbeiyuTouchscreen *, WanbeiyuRDAC *, WanbeiyuRDAC *, WanbeiyuSPSTSwitch *);
    errno_t wanbeiyu_touchscreen_hold(WanbeiyuTouchscreen *, uint16_t, uint8_t);
    errno_t wanbeiyu_touchscreen_release(WanbeiyuTouchscreen *);

#ifdef __cplusplus
}
#endif

#endif // WANBEIYU_TOUCHSCREEN_H