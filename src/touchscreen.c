#include <wanbeiyu.h>
#include "internal.h"

#include <assert.h>

wanbeiyu_error_t wanbeiyu_touchscreen_init(wanbeiyu_touchscreen_t *ts, wanbeiyu_rdac_t *h, wanbeiyu_rdac_t *v, wanbeiyu_spst_switch_t *sw)
{
    if (ts == NULL ||
        h == NULL ||
        v == NULL ||
        sw == NULL)
    {
        return WANBEIYU_EINVAL;
    }

    ts->h_ = h;
    ts->v_ = v;
    ts->sw_ = sw;

    return WANBEIYU_OK;
}

wanbeiyu_error_t wanbeiyu_touchscreen_hold(wanbeiyu_touchscreen_t *ts, uint16_t x, uint8_t y)
{
    if (ts == NULL ||
        WANBEIYU_TOUCHSCREEN_X_MAX < x ||
        WANBEIYU_TOUCHSCREEN_Y_MAX < y)
    {
        return WANBEIYU_EINVAL;
    }
    assert(ts->h_ != NULL &&
           ts->v_ != NULL &&
           ts->sw_ != NULL);

    wanbeiyu_error_t h_ret = ts->h_->set_wiper_position(ts->h_, (uint16_t)wanbeiyu_internal_remap(x, 0, WANBEIYU_TOUCHSCREEN_X_MAX, 0, UINT16_MAX));
    wanbeiyu_error_t v_ret = ts->v_->set_wiper_position(ts->v_, (uint16_t)wanbeiyu_internal_remap(y, 0, WANBEIYU_TOUCHSCREEN_Y_MAX, 0, UINT16_MAX));
    wanbeiyu_error_t sw_ret = ts->sw_->on(ts->sw_);
    if (h_ret != WANBEIYU_OK ||
        v_ret != WANBEIYU_OK ||
        sw_ret != WANBEIYU_OK)
    {
        return WANBEIYU_EIO;
    }

    return WANBEIYU_OK;
}

wanbeiyu_error_t wanbeiyu_touchscreen_release(wanbeiyu_touchscreen_t *ts)
{
    if (ts == NULL)
    {
        return WANBEIYU_EINVAL;
    }
    assert(ts->sw_ != NULL);

    wanbeiyu_error_t ret = ts->sw_->off(ts->sw_);
    if (ret != WANBEIYU_OK)
    {
        return WANBEIYU_EIO;
    }

    return WANBEIYU_OK;
}