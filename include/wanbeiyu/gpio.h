#ifndef WANBEIYU_GPIO_H
#define WANBEIYU_GPIO_H

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

    typedef struct WanbeiyuGPIO
    {
        errno_t (*set_low)(struct WanbeiyuGPIO *);
        errno_t (*set_hi_z)(struct WanbeiyuGPIO *);
    } WanbeiyuGPIO;

    errno_t wanbeiyu_gpio_set_low(WanbeiyuGPIO *);
    errno_t wanbeiyu_gpio_set_hi_z(WanbeiyuGPIO *);

#ifdef __cplusplus
}
#endif

#endif // WANBEIYU_GPIO_H