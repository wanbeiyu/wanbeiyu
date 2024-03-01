#ifndef WANBEIYU_H_
#define WANBEIYU_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>

    typedef int WanbeiyuError;

#define WANBEIYU_OK ((WanbeiyuError)0)
#define WANBEIYU_EIO ((WanbeiyuError)5)
#define WANBEIYU_EINVAL ((WanbeiyuError)22)

    typedef struct WanbeiyuGPIO
    {
        WanbeiyuError (*set_low)(struct WanbeiyuGPIO *gpio);
        WanbeiyuError (*set_hi_z)(struct WanbeiyuGPIO *gpio);
    } WanbeiyuGPIO;

    typedef struct WanbeiyuButton
    {
        WanbeiyuGPIO *gpio_;
    } WanbeiyuButton;

    WanbeiyuError wanbeiyu_button_init(WanbeiyuButton *btn, WanbeiyuGPIO *gpio);
    WanbeiyuError wanbeiyu_button_hold(WanbeiyuButton *btn);
    WanbeiyuError wanbeiyu_button_release(WanbeiyuButton *btn);

    typedef struct WanbeiyuHat
    {
        WanbeiyuGPIO *up_;
        WanbeiyuGPIO *right_;
        WanbeiyuGPIO *down_;
        WanbeiyuGPIO *left_;
    } WanbeiyuHat;

    typedef uint8_t WanbeiyuHatDirection;

#define WANBEIYU_HAT_UP ((WanbeiyuHatDirection)8)    /* 0b1000 */
#define WANBEIYU_HAT_RIGHT ((WanbeiyuHatDirection)4) /* 0b0100 */
#define WANBEIYU_HAT_DOWN ((WanbeiyuHatDirection)2)  /* 0b0010 */
#define WANBEIYU_HAT_LEFT ((WanbeiyuHatDirection)1)  /* 0b0001 */
#define WANBEIYU_HAT_UPRIGHT ((WanbeiyuHatDirection)(WANBEIYU_HAT_UP | WANBEIYU_HAT_RIGHT))
#define WANBEIYU_HAT_DOWNRIGHT ((WanbeiyuHatDirection)(WANBEIYU_HAT_DOWN | WANBEIYU_HAT_RIGHT))
#define WANBEIYU_HAT_DOWNLEFT ((WanbeiyuHatDirection)(WANBEIYU_HAT_DOWN | WANBEIYU_HAT_LEFT))
#define WANBEIYU_HAT_UPLEFT ((WanbeiyuHatDirection)(WANBEIYU_HAT_UP | WANBEIYU_HAT_LEFT))
#define WANBEIYU_HAT_NEUTRAL ((WanbeiyuHatDirection)0) /* 0b0000 */

    WanbeiyuError wanbeiyu_hat_init(WanbeiyuHat *hat, WanbeiyuGPIO *up, WanbeiyuGPIO *right, WanbeiyuGPIO *down, WanbeiyuGPIO *left);
    WanbeiyuError wanbeiyu_hat_hold(WanbeiyuHat *hat, WanbeiyuHatDirection dir);
    WanbeiyuError wanbeiyu_hat_release(WanbeiyuHat *hat);

    typedef struct WanbeiyuIDAC
    {
        WanbeiyuError (*set_sink)(struct WanbeiyuIDAC *idac, uint8_t val);
        WanbeiyuError (*set_source)(struct WanbeiyuIDAC *idac, uint8_t val);
    } WanbeiyuIDAC;

    typedef struct WanbeiyuSlidepad
    {
        WanbeiyuIDAC *h_;
        WanbeiyuIDAC *v_;
    } WanbeiyuSlidepad;

#define WANBEIYU_SLIDEPAD_NEUTRAL ((uint8_t)128)

    WanbeiyuError wanbeiyu_slidepad_init(WanbeiyuSlidepad *sp, WanbeiyuIDAC *h, WanbeiyuIDAC *v);
    WanbeiyuError wanbeiyu_slidepad_hold(WanbeiyuSlidepad *sp, uint8_t x, uint8_t y);
    WanbeiyuError wanbeiyu_slidepad_release(WanbeiyuSlidepad *sp);

    typedef struct WanbeiyuRDAC
    {
        WanbeiyuError (*set_wiper_position)(struct WanbeiyuRDAC *rdac, uint16_t pos);
    } WanbeiyuRDAC;

    typedef struct WanbeiyuSPSTSwitch
    {
        WanbeiyuError (*on)(struct WanbeiyuSPSTSwitch *sw);
        WanbeiyuError (*off)(struct WanbeiyuSPSTSwitch *sw);
    } WanbeiyuSPSTSwitch;

    typedef struct WanbeiyuTouchscreen
    {
        WanbeiyuRDAC *h_;
        WanbeiyuRDAC *v_;
        WanbeiyuSPSTSwitch *sw_;
    } WanbeiyuTouchscreen;

#define WANBEIYU_TOUCHSCREEN_X_MAX ((uint16_t)319)
#define WANBEIYU_TOUCHSCREEN_Y_MAX ((uint8_t)239)

    WanbeiyuError wanbeiyu_touchscreen_init(WanbeiyuTouchscreen *ts, WanbeiyuRDAC *h, WanbeiyuRDAC *v, WanbeiyuSPSTSwitch *sw);
    WanbeiyuError wanbeiyu_touchscreen_hold(WanbeiyuTouchscreen *ts, uint16_t x, uint8_t y);
    WanbeiyuError wanbeiyu_touchscreen_release(WanbeiyuTouchscreen *ts);

#ifdef __cplusplus
}
#endif

#endif // WANBEIYU_H_