#ifndef WANBEIYU_RDAC_H
#define WANBEIYU_RDAC_H

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

    typedef struct WanbeiyuRDAC
    {
        errno_t (*set_wiper_position)(struct WanbeiyuRDAC *, uint16_t);
    } WanbeiyuRDAC;

    errno_t wanbeiyu_rdac_set_wiper_position(WanbeiyuRDAC *, uint16_t);

#ifdef __cplusplus
}
#endif

#endif // WANBEIYU_RDAC_H