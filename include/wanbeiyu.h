#ifndef WANBEIYU_H_
#define WANBEIYU_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>

    typedef enum wanbeiyu_error_t
    {
        WANBEIYU_OK = 0,
        WANBEIYU_EINVAL = 22
    } wanbeiyu_error_t;

#define wanbeiyu_internal_remap(v, in_min, in_max, out_min, out_max) (((double)(v) - (double)(in_min)) * ((double)(out_max) - (double)(out_min)) / ((double)(in_max) - (double)(in_min)) + (double)(out_min))

    typedef struct wanbeiyu_gpio_t
    {
        void (*set_low)(struct wanbeiyu_gpio_t *gpio);
        void (*set_hi_z)(struct wanbeiyu_gpio_t *gpio);
    } wanbeiyu_gpio_t;

    typedef struct wanbeiyu_button_t
    {
        wanbeiyu_gpio_t *gpio_;
    } wanbeiyu_button_t;

#define wanbeiyu_button_hold(btn) ((btn) != NULL ? (btn)->gpio_->set_low((btn)->gpio_) \
                                                 : (void)0)
#define wanbeiyu_button_release(btn) ((btn) != NULL ? (btn)->gpio_->set_hi_z((btn)->gpio_) \
                                                    : (void)0)
#define wanbeiyu_button_init(btn, gpio) (((btn) != NULL &&                      \
                                          (gpio) != NULL)                       \
                                             ? ((btn)->gpio_ = (gpio),          \
                                                wanbeiyu_button_release((btn)), \
                                                WANBEIYU_OK)                    \
                                             : WANBEIYU_EINVAL)

    typedef struct wanbeiyu_hat_t
    {
        wanbeiyu_button_t *up_;
        wanbeiyu_button_t *right_;
        wanbeiyu_button_t *down_;
        wanbeiyu_button_t *left_;
    } wanbeiyu_hat_t;

    typedef enum wanbeiyu_hat_direction_t
    {
        WANBEIYU_HAT_UP = 8,        /* 0b1000 */
        WANBEIYU_HAT_UPRIGHT = 12,  /* 0b1100 */
        WANBEIYU_HAT_RIGHT = 4,     /* 0b0100 */
        WANBEIYU_HAT_DOWNRIGHT = 6, /* 0b0110 */
        WANBEIYU_HAT_DOWN = 2,      /* 0b0010 */
        WANBEIYU_HAT_DOWNLEFT = 3,  /* 0b0011 */
        WANBEIYU_HAT_LEFT = 1,      /* 0b0001 */
        WANBEIYU_HAT_UPLEFT = 9,    /* 0b1001 */
        WANBEIYU_HAT_NEUTRAL = 0    /* 0b0000 */
    } wanbeiyu_hat_direction_t;

#define wanbeiyu_hat_hold(hat, dir) ((hat) != NULL ? (((dir) & WANBEIYU_HAT_UP ? wanbeiyu_button_hold((hat)->up_)            \
                                                                               : wanbeiyu_button_release((hat)->up_)),       \
                                                      ((dir) & WANBEIYU_HAT_RIGHT ? wanbeiyu_button_hold((hat)->right_)      \
                                                                                  : wanbeiyu_button_release((hat)->right_)), \
                                                      ((dir) & WANBEIYU_HAT_DOWN ? wanbeiyu_button_hold((hat)->down_)        \
                                                                                 : wanbeiyu_button_release((hat)->down_)),   \
                                                      ((dir) & WANBEIYU_HAT_LEFT ? wanbeiyu_button_hold((hat)->left_)        \
                                                                                 : wanbeiyu_button_release((hat)->left_)))   \
                                                   : (void)0)
#define wanbeiyu_hat_release(hat) ((hat) != NULL ? (wanbeiyu_button_release((hat)->up_),    \
                                                    wanbeiyu_button_release((hat)->right_), \
                                                    wanbeiyu_button_release((hat)->down_),  \
                                                    wanbeiyu_button_release((hat)->left_))  \
                                                 : (void)0)
#define wanbeiyu_hat_init(hat, up, right, down, left) (((hat) != NULL &&                   \
                                                        (up) != NULL &&                    \
                                                        (right) != NULL &&                 \
                                                        (down) != NULL &&                  \
                                                        (left) != NULL)                    \
                                                           ? ((hat)->up_ = (up),           \
                                                              (hat)->right_ = (right),     \
                                                              (hat)->down_ = (down),       \
                                                              (hat)->left_ = (left),       \
                                                              wanbeiyu_hat_release((hat)), \
                                                              WANBEIYU_OK)                 \
                                                           : WANBEIYU_EINVAL)

    typedef struct wanbeiyu_idac_t
    {
        void (*set_sink)(struct wanbeiyu_idac_t *idac, uint8_t val);
        void (*set_source)(struct wanbeiyu_idac_t *idac, uint8_t val);
    } wanbeiyu_idac_t;

    typedef struct wanbeiyu_slidepad_t
    {
        wanbeiyu_idac_t *h_;
        wanbeiyu_idac_t *v_;
    } wanbeiyu_slidepad_t;

#define WANBEIYU_SLIDEPAD_NEUTRAL ((uint8_t)128)
#define wanbeiyu_slidepad_hold(sp, x, y) ((sp) != NULL ? ((WANBEIYU_SLIDEPAD_NEUTRAL < (x) ? /* 129, 130, ..., 255 */ (sp)->h_->set_sink((sp)->h_, (uint8_t)wanbeiyu_internal_remap((x), 129, UINT8_MAX, 0, UINT8_MAX)) \
                                                                                           : /* 128, 127, ..., 0 */ (sp)->h_->set_source((sp)->h_, (uint8_t)wanbeiyu_internal_remap((x), 128, 0, 0, UINT8_MAX))),       \
                                                          (WANBEIYU_SLIDEPAD_NEUTRAL < (y) ? (sp)->v_->set_sink((sp)->v_, (uint8_t)wanbeiyu_internal_remap((y), 129, UINT8_MAX, 0, UINT8_MAX))                          \
                                                                                           : (sp)->v_->set_source((sp)->v_, (uint8_t)wanbeiyu_internal_remap((y), 128, 0, 0, UINT8_MAX))))                              \
                                                       : (void)0)
#define wanbeiyu_slidepad_release(sp) ((sp) != NULL ? wanbeiyu_slidepad_hold((sp), WANBEIYU_SLIDEPAD_NEUTRAL, WANBEIYU_SLIDEPAD_NEUTRAL) \
                                                    : (void)0)
#define wanbeiyu_slidepad_init(sp, h, v) (((sp) != NULL &&                        \
                                           (h) != NULL &&                         \
                                           (v) != NULL)                           \
                                              ? ((sp)->h_ = (h),                  \
                                                 (sp)->v_ = (v),                  \
                                                 wanbeiyu_slidepad_release((sp)), \
                                                 WANBEIYU_OK)                     \
                                              : WANBEIYU_EINVAL)

    typedef struct wanbeiyu_rdac_t
    {
        void (*set_wiper_position)(struct wanbeiyu_rdac_t *rdac, uint16_t pos);
        void (*power_on)(struct wanbeiyu_rdac_t *rdac);
        void (*power_off)(struct wanbeiyu_rdac_t *rdac);
    } wanbeiyu_rdac_t;

    typedef struct wanbeiyu_spst_switch_t
    {
        void (*on)(struct wanbeiyu_spst_switch_t *sw);
        void (*off)(struct wanbeiyu_spst_switch_t *sw);
    } wanbeiyu_spst_switch_t;

    typedef struct wanbeiyu_touchscreen_t
    {
        wanbeiyu_rdac_t *h_;
        wanbeiyu_rdac_t *v_;
        wanbeiyu_spst_switch_t *sw_;
    } wanbeiyu_touchscreen_t;

#define WANBEIYU_TOUCHSCREEN_X_MIN ((uint16_t)0)
#define WANBEIYU_TOUCHSCREEN_X_MAX ((uint16_t)319)
#define WANBEIYU_TOUCHSCREEN_Y_MIN ((uint8_t)0)
#define WANBEIYU_TOUCHSCREEN_Y_MAX ((uint8_t)239)
#define wanbeiyu_touchscreen_hold(ts, x, y) (((ts) != NULL &&                                                                                                                                              \
                                              WANBEIYU_TOUCHSCREEN_X_MIN <= (x) && (x) <= WANBEIYU_TOUCHSCREEN_X_MAX &&                                                                                    \
                                              WANBEIYU_TOUCHSCREEN_Y_MIN <= (y) && (y) <= WANBEIYU_TOUCHSCREEN_Y_MAX)                                                                                      \
                                                 ? ((ts)->h_->set_wiper_position((ts)->h_, (uint16_t)wanbeiyu_internal_remap((x), WANBEIYU_TOUCHSCREEN_X_MIN, WANBEIYU_TOUCHSCREEN_X_MAX, 0, UINT16_MAX)), \
                                                    (ts)->v_->set_wiper_position((ts)->v_, (uint16_t)wanbeiyu_internal_remap((y), WANBEIYU_TOUCHSCREEN_Y_MIN, WANBEIYU_TOUCHSCREEN_Y_MAX, 0, UINT16_MAX)), \
                                                    (ts)->h_->power_on((ts)->h_),                                                                                                                          \
                                                    (ts)->v_->power_on((ts)->v_),                                                                                                                          \
                                                    (ts)->sw_->on((ts)->sw_))                                                                                                                              \
                                                 : (void)0)
#define wanbeiyu_touchscreen_release(ts) ((ts) != NULL ? ((ts)->sw_->off((ts)->sw_),     \
                                                          (ts)->v_->power_off((ts)->v_), \
                                                          (ts)->h_->power_off((ts)->h_)) \
                                                       : (void)0)
#define wanbeiyu_touchscreen_init(ts, h, v, sw) (((ts) != NULL &&                           \
                                                  (h) != NULL &&                            \
                                                  (v) != NULL &&                            \
                                                  (sw) != NULL)                             \
                                                     ? ((ts)->h_ = (h),                     \
                                                        (ts)->v_ = (v),                     \
                                                        (ts)->sw_ = (sw),                   \
                                                        wanbeiyu_touchscreen_release((ts)), \
                                                        WANBEIYU_OK)                        \
                                                     : WANBEIYU_EINVAL)

#ifdef __cplusplus
}
#endif

#endif // WANBEIYU_H_