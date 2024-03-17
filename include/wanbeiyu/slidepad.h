#ifndef WANBEIYU_SLIDEPAD_H
#define WANBEIYU_SLIDEPAD_H

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

#include "idac.h"

    typedef struct WanbeiyuSlidepad
    {
        WanbeiyuIDAC *horizontal;
        WanbeiyuIDAC *vertical;
    } WanbeiyuSlidepad;

#define WANBEIYU_SLIDEPAD_AXIS_NEUTRAL ((uint8_t)128)

    errno_t wanbeiyu_slidepad_init(WanbeiyuSlidepad *, WanbeiyuIDAC *, WanbeiyuIDAC *);
    errno_t wanbeiyu_slidepad_hold(WanbeiyuSlidepad *, uint8_t, uint8_t);
    errno_t wanbeiyu_slidepad_release(WanbeiyuSlidepad *);

#ifdef __cplusplus
}
#endif

#endif // WANBEIYU_SLIDEPAD_H