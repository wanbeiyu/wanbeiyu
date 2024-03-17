#ifndef WANBEIYU_SPST_SWITCH_H
#define WANBEIYU_SPST_SWITCH_H

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

    typedef struct WanbeiyuSPSTSwitch
    {
        errno_t (*on)(struct WanbeiyuSPSTSwitch *);
        errno_t (*off)(struct WanbeiyuSPSTSwitch *);
    } WanbeiyuSPSTSwitch;

    errno_t wanbeiyu_spst_switch_on(WanbeiyuSPSTSwitch *);
    errno_t wanbeiyu_spst_switch_off(WanbeiyuSPSTSwitch *);

#ifdef __cplusplus
}
#endif

#endif // WANBEIYU_SPST_SWITCH_H