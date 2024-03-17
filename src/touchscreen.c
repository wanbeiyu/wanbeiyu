#include <wanbeiyu/touchscreen.h>
#include "internal.h"

#include <assert.h>

errno_t wanbeiyu_touchscreen_init(WanbeiyuTouchscreen *ts, WanbeiyuRDAC *horizontal, WanbeiyuRDAC *vertical, WanbeiyuSPSTSwitch *switch_)
{
    if (ts == NULL ||
        horizontal == NULL ||
        vertical == NULL ||
        switch_ == NULL)
    {
        return EINVAL;
    }

    ts->horizontal = horizontal;
    ts->vertical = vertical;
    ts->switch_ = switch_;

    return 0;
}

errno_t wanbeiyu_touchscreen_hold(WanbeiyuTouchscreen *ts, uint16_t x, uint8_t y)
{
    if (ts == NULL ||
        WANBEIYU_TOUCHSCREEN_X_MAX < x ||
        WANBEIYU_TOUCHSCREEN_Y_MAX < y)
    {
        return EINVAL;
    }
    assert(ts->horizontal != NULL &&
           ts->vertical != NULL &&
           ts->switch_ != NULL);

    errno_t horizontal_err = ts->horizontal->set_wiper_position(ts->horizontal, (uint16_t)wanbeiyu_internal_remap(x, 0, WANBEIYU_TOUCHSCREEN_X_MAX, 0, UINT16_MAX));
    errno_t vertical_err = ts->vertical->set_wiper_position(ts->vertical, (uint16_t)wanbeiyu_internal_remap(y, 0, WANBEIYU_TOUCHSCREEN_Y_MAX, 0, UINT16_MAX));
    errno_t switch_err = ts->switch_->on(ts->switch_);
    if (horizontal_err != 0 ||
        vertical_err != 0 ||
        switch_err != 0)
    {
        return EIO;
    }

    return 0;
}

errno_t wanbeiyu_touchscreen_release(WanbeiyuTouchscreen *ts)
{
    if (ts == NULL)
    {
        return EINVAL;
    }
    assert(ts->switch_ != NULL);

    errno_t err = ts->switch_->off(ts->switch_);
    if (err != 0)
    {
        return EIO;
    }

    return 0;
}