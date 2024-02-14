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
        void (*sink)(struct wby_idac_t *idac, uint8_t value);
        void (*source)(struct wby_idac_t *idac, uint8_t value);
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
        wby_gpio_t *_gpio;
    } wby_button_t;

#define wby_button_hold(btn) ((btn) != NULL ? (btn)->_gpio->set_low((btn)->_gpio) \
                                            : (void)0)
#define wby_button_release(btn) ((btn) != NULL ? (btn)->_gpio->set_hi_z((btn)->_gpio) \
                                               : (void)0)
#define wby_button_init(btn, gpio) (((btn) != NULL && (gpio) != NULL) ? ((btn)->_gpio = (gpio),     \
                                                                         wby_button_release((btn))) \
                                                                      : (void)0)

    typedef struct wby_hat_t
    {
        wby_button_t *_up;
        wby_button_t *_right;
        wby_button_t *_down;
        wby_button_t *_left;
    } wby_hat_t;

    typedef enum wby_hat_direction_t
    {
        WBY_HAT_UP = 8,        /* 0b1000 */
        WBY_HAT_UPRIGHT = 12,  /* 0b1100 */
        WBY_HAT_RIGHT = 4,     /* 0b0100 */
        WBY_HAT_DOWNRIGHT = 6, /* 0b0110 */
        WBY_HAT_DOWN = 2,      /* 0b0010 */
        WBY_HAT_DOWNLEFT = 3,  /* 0b0011 */
        WBY_HAT_LEFT = 1,      /* 0b0001 */
        WBY_HAT_UPLEFT = 9,    /* 0b1001 */
        WBY_HAT_NEUTRAL = 0    /* 0b0000 */
    } wby_hat_direction_t;

#define wby_hat_hold(hat, dir) ((hat) != NULL ? (((dir) & WBY_HAT_UP ? wby_button_hold((hat)->_up)            \
                                                                     : wby_button_release((hat)->_up)),       \
                                                 ((dir) & WBY_HAT_RIGHT ? wby_button_hold((hat)->_right)      \
                                                                        : wby_button_release((hat)->_right)), \
                                                 ((dir) & WBY_HAT_DOWN ? wby_button_hold((hat)->_down)        \
                                                                       : wby_button_release((hat)->_down)),   \
                                                 ((dir) & WBY_HAT_LEFT ? wby_button_hold((hat)->_left)        \
                                                                       : wby_button_release((hat)->_left)))   \
                                              : (void)0)
#define wby_hat_release(hat) ((hat) != NULL ? (wby_button_release((hat)->_up),    \
                                               wby_button_release((hat)->_right), \
                                               wby_button_release((hat)->_down),  \
                                               wby_button_release((hat)->_left))  \
                                            : (void)0)
#define wby_hat_init(hat, up, right, down, left) (((hat) != NULL && (up) != NULL && (right) != NULL && (down) != NULL && (left) != NULL) ? ((hat)->_up = up,        \
                                                                                                                                            (hat)->_right = right,  \
                                                                                                                                            (hat)->_down = down,    \
                                                                                                                                            (hat)->_left = left,    \
                                                                                                                                            wby_hat_release((hat))) \
                                                                                                                                         : (void)0)

    typedef struct wby_slidepad_t
    {
        wby_idac_t *_h;
        wby_idac_t *_v;
    } wby_slidepad_t;

#define WBY_SLIDEPAD_NEUTRAL ((uint8_t)128)
#define wby_slidepad_hold(sp, x, y) ((sp) != NULL ? ((WBY_SLIDEPAD_NEUTRAL < (x) ? /* 129, 130, ..., 255; (x - WBY_SLIDEPAD_NEUTRAL) = 1, 2, ..., 127 */ (sp)->_h->sink((sp)->_h, (uint8_t)(((double)((x)-WBY_SLIDEPAD_NEUTRAL) / 127) * UINT8_MAX))   \
                                                                                 : /* 0, 1, ..., 128; (WBY_SLIDEPAD_NEUTRAL - x) = 0, 1, ..., 128 */ (sp)->_h->source((sp)->_h, (uint8_t)(((double)(WBY_SLIDEPAD_NEUTRAL - (x)) / 128) * UINT8_MAX))), \
                                                     (WBY_SLIDEPAD_NEUTRAL < (y) ? (sp)->_v->sink((sp)->_v, (uint8_t)(((double)((y)-WBY_SLIDEPAD_NEUTRAL) / 127) * UINT8_MAX))                                                                         \
                                                                                 : (sp)->_v->source((sp)->_v, (uint8_t)(((double)(WBY_SLIDEPAD_NEUTRAL - (y)) / 128) * UINT8_MAX))))                                                                   \
                                                  : (void)0)
#define wby_slidepad_release(sp) ((sp) != NULL ? wby_slidepad_hold((sp), WBY_SLIDEPAD_NEUTRAL, WBY_SLIDEPAD_NEUTRAL) \
                                               : (void)0)
#define wby_slidepad_init(sp, h, v) (((sp) != NULL && (h) != NULL && (v) != NULL) ? ((sp)->_h = h,               \
                                                                                     (sp)->_v = v,               \
                                                                                     wby_slidepad_release((sp))) \
                                                                                  : (void)0)

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