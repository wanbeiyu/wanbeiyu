#ifndef WANBEIYU_H_
#define WANBEIYU_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>

    typedef int wanbeiyu_error_t;

#define WANBEIYU_OK ((wanbeiyu_error_t)0)
#define WANBEIYU_EIO ((wanbeiyu_error_t)5)
#define WANBEIYU_EINVAL ((wanbeiyu_error_t)22)

    typedef struct wanbeiyu_gpio_t
    {
        wanbeiyu_error_t (*set_low)(struct wanbeiyu_gpio_t *gpio);
        wanbeiyu_error_t (*set_hi_z)(struct wanbeiyu_gpio_t *gpio);
    } wanbeiyu_gpio_t;

    typedef struct wanbeiyu_button_t
    {
        wanbeiyu_gpio_t *gpio_;
    } wanbeiyu_button_t;

    wanbeiyu_error_t wanbeiyu_button_init(wanbeiyu_button_t *btn, wanbeiyu_gpio_t *gpio);
    wanbeiyu_error_t wanbeiyu_button_hold(wanbeiyu_button_t *btn);
    wanbeiyu_error_t wanbeiyu_button_release(wanbeiyu_button_t *btn);

    typedef struct wanbeiyu_hat_t
    {
        wanbeiyu_gpio_t *up_;
        wanbeiyu_gpio_t *right_;
        wanbeiyu_gpio_t *down_;
        wanbeiyu_gpio_t *left_;
    } wanbeiyu_hat_t;

    typedef uint8_t wanbeiyu_hat_direction_t;

#define WANBEIYU_HAT_UP ((wanbeiyu_hat_direction_t)8)    /* 0b1000 */
#define WANBEIYU_HAT_RIGHT ((wanbeiyu_hat_direction_t)4) /* 0b0100 */
#define WANBEIYU_HAT_DOWN ((wanbeiyu_hat_direction_t)2)  /* 0b0010 */
#define WANBEIYU_HAT_LEFT ((wanbeiyu_hat_direction_t)1)  /* 0b0001 */
#define WANBEIYU_HAT_UPRIGHT ((wanbeiyu_hat_direction_t)(WANBEIYU_HAT_UP | WANBEIYU_HAT_RIGHT))
#define WANBEIYU_HAT_DOWNRIGHT ((wanbeiyu_hat_direction_t)(WANBEIYU_HAT_DOWN | WANBEIYU_HAT_RIGHT))
#define WANBEIYU_HAT_DOWNLEFT ((wanbeiyu_hat_direction_t)(WANBEIYU_HAT_DOWN | WANBEIYU_HAT_LEFT))
#define WANBEIYU_HAT_UPLEFT ((wanbeiyu_hat_direction_t)(WANBEIYU_HAT_UP | WANBEIYU_HAT_LEFT))
#define WANBEIYU_HAT_NEUTRAL ((wanbeiyu_hat_direction_t)0) /* 0b0000 */

    wanbeiyu_error_t wanbeiyu_hat_init(wanbeiyu_hat_t *hat, wanbeiyu_gpio_t *up, wanbeiyu_gpio_t *right, wanbeiyu_gpio_t *down, wanbeiyu_gpio_t *left);
    wanbeiyu_error_t wanbeiyu_hat_hold(wanbeiyu_hat_t *hat, wanbeiyu_hat_direction_t dir);
    wanbeiyu_error_t wanbeiyu_hat_release(wanbeiyu_hat_t *hat);

    typedef struct wanbeiyu_idac_t
    {
        wanbeiyu_error_t (*set_sink)(struct wanbeiyu_idac_t *idac, uint8_t val);
        wanbeiyu_error_t (*set_source)(struct wanbeiyu_idac_t *idac, uint8_t val);
    } wanbeiyu_idac_t;

    typedef struct wanbeiyu_slidepad_t
    {
        wanbeiyu_idac_t *h_;
        wanbeiyu_idac_t *v_;
    } wanbeiyu_slidepad_t;

#define WANBEIYU_SLIDEPAD_NEUTRAL ((uint8_t)128)

    wanbeiyu_error_t wanbeiyu_slidepad_init(wanbeiyu_slidepad_t *sp, wanbeiyu_idac_t *h, wanbeiyu_idac_t *v);
    wanbeiyu_error_t wanbeiyu_slidepad_hold(wanbeiyu_slidepad_t *sp, uint8_t x, uint8_t y);
    wanbeiyu_error_t wanbeiyu_slidepad_release(wanbeiyu_slidepad_t *sp);

    typedef struct wanbeiyu_rdac_t
    {
        wanbeiyu_error_t (*set_wiper_position)(struct wanbeiyu_rdac_t *rdac, uint16_t pos);
    } wanbeiyu_rdac_t;

    typedef struct wanbeiyu_spst_switch_t
    {
        wanbeiyu_error_t (*on)(struct wanbeiyu_spst_switch_t *sw);
        wanbeiyu_error_t (*off)(struct wanbeiyu_spst_switch_t *sw);
    } wanbeiyu_spst_switch_t;

    typedef struct wanbeiyu_touchscreen_t
    {
        wanbeiyu_rdac_t *h_;
        wanbeiyu_rdac_t *v_;
        wanbeiyu_spst_switch_t *sw_;
    } wanbeiyu_touchscreen_t;

#define WANBEIYU_TOUCHSCREEN_X_MAX ((uint16_t)319)
#define WANBEIYU_TOUCHSCREEN_Y_MAX ((uint8_t)239)

    wanbeiyu_error_t wanbeiyu_touchscreen_init(wanbeiyu_touchscreen_t *ts, wanbeiyu_rdac_t *h, wanbeiyu_rdac_t *v, wanbeiyu_spst_switch_t *sw);
    wanbeiyu_error_t wanbeiyu_touchscreen_hold(wanbeiyu_touchscreen_t *ts, uint16_t x, uint8_t y);
    wanbeiyu_error_t wanbeiyu_touchscreen_release(wanbeiyu_touchscreen_t *ts);

#ifdef __cplusplus
}
#endif

#endif // WANBEIYU_H_