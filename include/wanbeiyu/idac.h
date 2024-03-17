#ifndef WANBEIYU_IDAC_H
#define WANBEIYU_IDAC_H

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

    typedef struct WanbeiyuIDAC
    {
        errno_t (*set_sink)(struct WanbeiyuIDAC *, uint8_t);
        errno_t (*set_source)(struct WanbeiyuIDAC *, uint8_t);
    } WanbeiyuIDAC;

    errno_t wanbeiyu_idac_set_sink(WanbeiyuIDAC *, uint8_t);
    errno_t wanbeiyu_idac_set_source(WanbeiyuIDAC *, uint8_t);

#ifdef __cplusplus
}
#endif

#endif // WANBEIYU_IDAC_H