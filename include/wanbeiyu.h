#ifndef WANBEIYU_H_
#define WANBEIYU_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>

    typedef int WanbeiyuErrNo;

#define WANBEIYU_OK ((WanbeiyuErrNo)0)
#define WANBEIYU_EIO ((WanbeiyuErrNo)5)
#define WANBEIYU_EINVAL ((WanbeiyuErrNo)22)

    typedef struct WanbeiyuGPIO
    {
        WanbeiyuErrNo (*set_low)(struct WanbeiyuGPIO *gpio);
        WanbeiyuErrNo (*set_hi_z)(struct WanbeiyuGPIO *gpio);
    } WanbeiyuGPIO;

    typedef struct WanbeiyuButton
    {
        WanbeiyuGPIO *gpio;
    } WanbeiyuButton;

    WanbeiyuErrNo wanbeiyu_button_init(WanbeiyuButton *btn, WanbeiyuGPIO *gpio);
    WanbeiyuErrNo wanbeiyu_button_hold(WanbeiyuButton *btn);
    WanbeiyuErrNo wanbeiyu_button_release(WanbeiyuButton *btn);

    typedef struct WanbeiyuHat
    {
        WanbeiyuGPIO *up;
        WanbeiyuGPIO *right;
        WanbeiyuGPIO *down;
        WanbeiyuGPIO *left;
    } WanbeiyuHat;

    typedef uint8_t WanbeiyuHatDirection;

#define WANBEIYU_HAT_NEUTRAL /* 0b0000 */ ((WanbeiyuHatDirection)0)
#define WANBEIYU_HAT_LEFT /*    0b0001 */ ((WanbeiyuHatDirection)1)
#define WANBEIYU_HAT_DOWN /*    0b0010 */ ((WanbeiyuHatDirection)2)
#define WANBEIYU_HAT_RIGHT /*   0b0100 */ ((WanbeiyuHatDirection)4)
#define WANBEIYU_HAT_UP /*      0b1000 */ ((WanbeiyuHatDirection)8)
#define WANBEIYU_HAT_UPRIGHT ((WanbeiyuHatDirection)(WANBEIYU_HAT_UP | WANBEIYU_HAT_RIGHT))
#define WANBEIYU_HAT_DOWNRIGHT ((WanbeiyuHatDirection)(WANBEIYU_HAT_DOWN | WANBEIYU_HAT_RIGHT))
#define WANBEIYU_HAT_DOWNLEFT ((WanbeiyuHatDirection)(WANBEIYU_HAT_DOWN | WANBEIYU_HAT_LEFT))
#define WANBEIYU_HAT_UPLEFT ((WanbeiyuHatDirection)(WANBEIYU_HAT_UP | WANBEIYU_HAT_LEFT))

    WanbeiyuErrNo wanbeiyu_hat_init(WanbeiyuHat *hat, WanbeiyuGPIO *up, WanbeiyuGPIO *right, WanbeiyuGPIO *down, WanbeiyuGPIO *left);
    WanbeiyuErrNo wanbeiyu_hat_hold(WanbeiyuHat *hat, WanbeiyuHatDirection dir);
    WanbeiyuErrNo wanbeiyu_hat_release(WanbeiyuHat *hat);

    typedef struct WanbeiyuIDAC
    {
        WanbeiyuErrNo (*set_sink)(struct WanbeiyuIDAC *idac, uint8_t val);
        WanbeiyuErrNo (*set_source)(struct WanbeiyuIDAC *idac, uint8_t val);
    } WanbeiyuIDAC;

    typedef struct WanbeiyuSlidepad
    {
        WanbeiyuIDAC *horizontal;
        WanbeiyuIDAC *vertical;
    } WanbeiyuSlidepad;

#define WANBEIYU_SLIDEPAD_NEUTRAL ((uint8_t)128)

    WanbeiyuErrNo wanbeiyu_slidepad_init(WanbeiyuSlidepad *sp, WanbeiyuIDAC *horizontal, WanbeiyuIDAC *vertical);
    WanbeiyuErrNo wanbeiyu_slidepad_hold(WanbeiyuSlidepad *sp, uint8_t x, uint8_t y);
    WanbeiyuErrNo wanbeiyu_slidepad_release(WanbeiyuSlidepad *sp);

    typedef struct WanbeiyuRDAC
    {
        WanbeiyuErrNo (*set_wiper_position)(struct WanbeiyuRDAC *rdac, uint16_t pos);
    } WanbeiyuRDAC;

    typedef struct WanbeiyuSPSTSwitch
    {
        WanbeiyuErrNo (*on)(struct WanbeiyuSPSTSwitch *sw);
        WanbeiyuErrNo (*off)(struct WanbeiyuSPSTSwitch *sw);
    } WanbeiyuSPSTSwitch;

    typedef struct WanbeiyuTouchscreen
    {
        WanbeiyuRDAC *horizontal;
        WanbeiyuRDAC *vertical;
        WanbeiyuSPSTSwitch *switch_;
    } WanbeiyuTouchscreen;

#define WANBEIYU_TOUCHSCREEN_X_MAX ((uint16_t)319)
#define WANBEIYU_TOUCHSCREEN_Y_MAX ((uint8_t)239)

    WanbeiyuErrNo wanbeiyu_touchscreen_init(WanbeiyuTouchscreen *ts, WanbeiyuRDAC *horizontal, WanbeiyuRDAC *vertical, WanbeiyuSPSTSwitch *switch_);
    WanbeiyuErrNo wanbeiyu_touchscreen_hold(WanbeiyuTouchscreen *ts, uint16_t x, uint8_t y);
    WanbeiyuErrNo wanbeiyu_touchscreen_release(WanbeiyuTouchscreen *ts);

#ifdef __cplusplus
}
#endif

#endif // WANBEIYU_H_