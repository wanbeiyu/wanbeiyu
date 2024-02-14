#ifndef WANBEIYU_H_
#define WANBEIYU_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>

    typedef struct wby_gpio_t
    {
        void (*set_low)(struct wby_gpio_t *gpio);
        void (*set_hi_z)(struct wby_gpio_t *gpio);
    } wby_gpio_t;

    /**
     * @brief -263.79-263.79[uA] output is used, but slight differences should be able to be handled by calibration on the 3DS side.
     */
    typedef struct wby_idac_t
    {
        void (*sink)(struct wby_idac_t *idac, uint16_t value);
        void (*source)(struct wby_idac_t *idac, uint16_t value);
    } wby_idac_t;

    /**
     * @brief Total resistance value must be less than pull-up resistance (details unknown, 10kΩ?). Horizontal dimension is 320px and vertical dimension is 240px.
     */
    typedef struct wby_rdac_t
    {
        void (*set_wiper_position)(struct wby_rdac_t *rdac, uint16_t position);
        void (*power_on)(struct wby_rdac_t *rdac);
        void (*shutdown)(struct wby_rdac_t *rdac);
    } wby_rdac_t;

    /**
     * @brief Use CMOS analog switches with low on-resistance.
     */
    typedef struct wby_spst_switch_t
    {
        void (*on)(struct wby_spst_switch_t *sw);
        void (*off)(struct wby_spst_switch_t *sw);
    } wby_spst_switch_t;

    typedef struct wby_button_t
    {
        wby_gpio_t *gpio;
    } wby_button_t;

    void wby_button_hold(wby_button_t *btn);
    void wby_button_release(wby_button_t *btn);
    wby_button_t *wby_button_new(wby_gpio_t *gpio);
    void wby_button_delete(wby_button_t *btn);

    typedef struct wby_hat_t
    {
        wby_button_t *up;
        wby_button_t *right;
        wby_button_t *down;
        wby_button_t *left;
    } wby_hat_t;

    typedef enum wby_hat_direction_t
    {
        WBY_HAT_UP,
        WBY_HAT_UPRIGHT,
        WBY_HAT_RIGHT,
        WBY_HAT_DOWNRIGHT,
        WBY_HAT_DOWN,
        WBY_HAT_DOWNLEFT,
        WBY_HAT_LEFT,
        WBY_HAT_UPLEFT,
        WBY_HAT_NEUTRAL
    } wby_hat_direction_t;

    void wby_hat_hold(wby_hat_t *hat, wby_hat_direction_t direction);
    void wby_hat_release(wby_hat_t *hat);
    wby_hat_t *wby_hat_new(wby_button_t *up, wby_button_t *right, wby_button_t *down, wby_button_t *left);
    void wby_hat_delete(wby_hat_t *hat);

    typedef struct wby_slidepad_t
    {
        wby_idac_t *vertical;
        wby_idac_t *horizontal;
    } wby_slidepad_t;

#define WBY_SLIDEPAD_NEUTRAL ((uint16_t)32767)

    void wby_slidepad_hold(wby_slidepad_t *sp, uint16_t x, uint16_t y);
    void wby_slidepad_release(wby_slidepad_t *sp);
    wby_slidepad_t *wby_slidepad_new(wby_idac_t *vertical, wby_idac_t *horizontal);
    void wby_slidepad_delete(wby_slidepad_t *sp);

    typedef struct wby_touchscreen_t
    {
        wby_rdac_t *vertical;
        wby_rdac_t *horizontal;
        wby_spst_switch_t *sw;
    } wby_touchscreen_t;

    void wby_touchscreen_hold(wby_touchscreen_t *ts, uint16_t x, uint16_t y);
    void wby_touchscreen_release(wby_touchscreen_t *ts);
    wby_touchscreen_t *wby_touchscreen_new(wby_rdac_t *vertical, wby_rdac_t *horizontal, wby_spst_switch_t *sw);
    void wby_touchscreen_delete(wby_touchscreen_t *ts);

#ifdef __cplusplus
}
#endif

#endif // WANBEIYU_H_