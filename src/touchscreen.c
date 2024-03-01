#include <wanbeiyu.h>
#include "internal.h"

#include <assert.h>

WanbeiyuErrNo wanbeiyu_touchscreen_init(WanbeiyuTouchscreen *ts, WanbeiyuRDAC *horizontal, WanbeiyuRDAC *vertical, WanbeiyuSPSTSwitch *switch_)
{
    if (ts == NULL ||
        horizontal == NULL ||
        vertical == NULL ||
        switch_ == NULL)
    {
        return WANBEIYU_EINVAL;
    }

    ts->horizontal = horizontal;
    ts->vertical = vertical;
    ts->switch_ = switch_;

    return WANBEIYU_OK;
}

WanbeiyuErrNo wanbeiyu_touchscreen_hold(WanbeiyuTouchscreen *ts, uint16_t x, uint8_t y)
{
    if (ts == NULL ||
        WANBEIYU_TOUCHSCREEN_X_MAX < x ||
        WANBEIYU_TOUCHSCREEN_Y_MAX < y)
    {
        return WANBEIYU_EINVAL;
    }
    assert(ts->horizontal != NULL &&
           ts->vertical != NULL &&
           ts->switch_ != NULL);

    WanbeiyuErrNo horizontal_ret = ts->horizontal->set_wiper_position(ts->horizontal, (uint16_t)wanbeiyu_internal_remap(x, 0, WANBEIYU_TOUCHSCREEN_X_MAX, 0, UINT16_MAX));
    WanbeiyuErrNo vertical_ret = ts->vertical->set_wiper_position(ts->vertical, (uint16_t)wanbeiyu_internal_remap(y, 0, WANBEIYU_TOUCHSCREEN_Y_MAX, 0, UINT16_MAX));
    WanbeiyuErrNo switch_ret = ts->switch_->on(ts->switch_);
    if (horizontal_ret != WANBEIYU_OK ||
        vertical_ret != WANBEIYU_OK ||
        switch_ret != WANBEIYU_OK)
    {
        return WANBEIYU_EIO;
    }

    return WANBEIYU_OK;
}

WanbeiyuErrNo wanbeiyu_touchscreen_release(WanbeiyuTouchscreen *ts)
{
    if (ts == NULL)
    {
        return WANBEIYU_EINVAL;
    }
    assert(ts->switch_ != NULL);

    WanbeiyuErrNo ret = ts->switch_->off(ts->switch_);
    if (ret != WANBEIYU_OK)
    {
        return WANBEIYU_EIO;
    }

    return WANBEIYU_OK;
}