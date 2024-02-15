#ifndef WANBEIYU_H_
#define WANBEIYU_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>

    typedef enum wby_error_t
    {
        WBY_OK = 0,
        WBY_EINVAL = 22
    } wby_error_t;

#define wby_internal_remap(v, in_min, in_max, out_min, out_max) (((double)(v) - (double)(in_min)) * ((double)(out_max) - (double)(out_min)) / ((double)(in_max) - (double)(in_min)) + (double)(out_min))

    typedef struct wby_gpio_t
    {
        wby_error_t (*set_low)(struct wby_gpio_t *gpio);
        wby_error_t (*set_hi_z)(struct wby_gpio_t *gpio);
    } wby_gpio_t;

    typedef struct wby_button_t
    {
        wby_gpio_t *_gpio;
    } wby_button_t;

#define wby_button_hold(btn) ((btn) != NULL ? (btn)->_gpio->set_low((btn)->_gpio) \
                                            : WBY_EINVAL)
#define wby_button_release(btn) ((btn) != NULL ? (btn)->_gpio->set_hi_z((btn)->_gpio) \
                                               : WBY_EINVAL)
#define wby_button_init(btn, gpio) (((btn) != NULL &&                 \
                                     (gpio) != NULL)                  \
                                        ? ((btn)->_gpio = (gpio),     \
                                           wby_button_release((btn))) \
                                        : WBY_EINVAL)

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
#define wby_hat_init(hat, up, right, down, left) (((hat) != NULL &&               \
                                                   (up) != NULL &&                \
                                                   (right) != NULL &&             \
                                                   (down) != NULL &&              \
                                                   (left) != NULL)                \
                                                      ? ((hat)->_up = (up),       \
                                                         (hat)->_right = (right), \
                                                         (hat)->_down = (down),   \
                                                         (hat)->_left = (left),   \
                                                         wby_hat_release((hat)))  \
                                                      : (void)0)

    typedef struct wby_idac_t
    {
        void (*set_sink)(struct wby_idac_t *idac, uint8_t val);
        void (*set_source)(struct wby_idac_t *idac, uint8_t val);
    } wby_idac_t;

    typedef struct wby_slidepad_t
    {
        wby_idac_t *_h;
        wby_idac_t *_v;
    } wby_slidepad_t;

#define WBY_SLIDEPAD_NEUTRAL ((uint8_t)128)
#define wby_slidepad_hold(sp, x, y) ((sp) != NULL ? ((WBY_SLIDEPAD_NEUTRAL < (x) ? /* 129, 130, ..., 255 */ (sp)->_h->set_sink((sp)->_h, (uint8_t)wby_internal_remap((x), 129, UINT8_MAX, 0, UINT8_MAX)) \
                                                                                 : /* 128, 127, ..., 0 */ (sp)->_h->set_source((sp)->_h, (uint8_t)wby_internal_remap((x), 128, 0, 0, UINT8_MAX))),       \
                                                     (WBY_SLIDEPAD_NEUTRAL < (y) ? (sp)->_v->set_sink((sp)->_v, (uint8_t)wby_internal_remap((y), 129, UINT8_MAX, 0, UINT8_MAX))                          \
                                                                                 : (sp)->_v->set_source((sp)->_v, (uint8_t)wby_internal_remap((y), 128, 0, 0, UINT8_MAX))))                              \
                                                  : (void)0)
#define wby_slidepad_release(sp) ((sp) != NULL ? wby_slidepad_hold((sp), WBY_SLIDEPAD_NEUTRAL, WBY_SLIDEPAD_NEUTRAL) \
                                               : (void)0)
#define wby_slidepad_init(sp, h, v) (((sp) != NULL &&                   \
                                      (h) != NULL &&                    \
                                      (v) != NULL)                      \
                                         ? ((sp)->_h = (h),             \
                                            (sp)->_v = (v),             \
                                            wby_slidepad_release((sp))) \
                                         : (void)0)

    typedef struct wby_rdac_t
    {
        void (*set_wiper_position)(struct wby_rdac_t *rdac, uint16_t pos);
        void (*power_on)(struct wby_rdac_t *rdac);
        void (*power_off)(struct wby_rdac_t *rdac);
    } wby_rdac_t;

    typedef struct wby_spst_switch_t
    {
        void (*on)(struct wby_spst_switch_t *sw);
        void (*off)(struct wby_spst_switch_t *sw);
    } wby_spst_switch_t;

    typedef struct wby_touchscreen_t
    {
        wby_rdac_t *_h;
        wby_rdac_t *_v;
        wby_spst_switch_t *_sw;
    } wby_touchscreen_t;

#define WBY_TOUCHSCREEN_X_MIN ((uint16_t)0)
#define WBY_TOUCHSCREEN_X_MAX ((uint16_t)319)
#define WBY_TOUCHSCREEN_Y_MIN ((uint8_t)0)
#define WBY_TOUCHSCREEN_Y_MAX ((uint8_t)239)
#define wby_touchscreen_hold(ts, x, y) (((ts) != NULL &&                                                                                                                               \
                                         WBY_TOUCHSCREEN_X_MIN <= (x) && (x) <= WBY_TOUCHSCREEN_X_MAX &&                                                                               \
                                         WBY_TOUCHSCREEN_Y_MIN <= (y) && (y) <= WBY_TOUCHSCREEN_Y_MAX)                                                                                 \
                                            ? ((ts)->_h->set_wiper_position((ts)->_h, (uint16_t)wby_internal_remap((x), WBY_TOUCHSCREEN_X_MIN, WBY_TOUCHSCREEN_X_MAX, 0, UINT16_MAX)), \
                                               (ts)->_v->set_wiper_position((ts)->_v, (uint16_t)wby_internal_remap((y), WBY_TOUCHSCREEN_Y_MIN, WBY_TOUCHSCREEN_Y_MAX, 0, UINT16_MAX)), \
                                               (ts)->_h->power_on((ts)->_h),                                                                                                           \
                                               (ts)->_v->power_on((ts)->_v),                                                                                                           \
                                               (ts)->_sw->on((ts)->_sw))                                                                                                               \
                                            : (void)0)
#define wby_touchscreen_release(ts) ((ts) != NULL ? ((ts)->_sw->off((ts)->_sw),     \
                                                     (ts)->_v->power_off((ts)->_v), \
                                                     (ts)->_h->power_off((ts)->_h)) \
                                                  : (void)0)
#define wby_touchscreen_init(ts, h, v, sw) (((ts) != NULL && (h) != NULL && (v) != NULL && (sw) != NULL) ? ((ts)->_h = (h),                \
                                                                                                            (ts)->_v = (v),                \
                                                                                                            (ts)->_sw = (sw),              \
                                                                                                            wby_touchscreen_release((ts))) \
                                                                                                         : (void)0)

#ifdef __cplusplus
}
#endif

#endif // WANBEIYU_H_