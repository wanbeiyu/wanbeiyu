#include <wanbeiyu.h>
#include "internal.h"

#include <assert.h>

WanbeiyuErrNo wanbeiyu_slidepad_init(WanbeiyuSlidepad *sp, WanbeiyuIDAC *horizontal, WanbeiyuIDAC *vertical)
{
    if (sp == NULL ||
        horizontal == NULL ||
        vertical == NULL)
    {
        return WANBEIYU_EINVAL;
    }

    sp->horizontal = horizontal;
    sp->vertical = vertical;

    return WANBEIYU_OK;
}

WanbeiyuErrNo wanbeiyu_slidepad_hold(WanbeiyuSlidepad *sp, uint8_t x, uint8_t y)
{
    if (sp == NULL)
    {
        return WANBEIYU_EINVAL;
    }
    assert(sp->horizontal != NULL &&
           sp->vertical != NULL);

    WanbeiyuErrNo horizontal_ret = WANBEIYU_SLIDEPAD_AXIS_NEUTRAL < x
                                       ? /* 129, 130, ..., 255 */ sp->horizontal->set_sink(sp->horizontal, (uint8_t)wanbeiyu_internal_remap(x, 129, UINT8_MAX, 0, UINT8_MAX))
                                       : /* 128, 127, ..., 0 */ sp->horizontal->set_source(sp->horizontal, (uint8_t)wanbeiyu_internal_remap(x, 128, 0, 0, UINT8_MAX));
    WanbeiyuErrNo vertical_ret = WANBEIYU_SLIDEPAD_AXIS_NEUTRAL < y
                                     ? sp->vertical->set_sink(sp->vertical, (uint8_t)wanbeiyu_internal_remap(y, 129, UINT8_MAX, 0, UINT8_MAX))
                                     : sp->vertical->set_source(sp->vertical, (uint8_t)wanbeiyu_internal_remap(y, 128, 0, 0, UINT8_MAX));
    if (horizontal_ret != WANBEIYU_OK ||
        vertical_ret != WANBEIYU_OK)
    {
        return WANBEIYU_EIO;
    }

    return WANBEIYU_OK;
}

WanbeiyuErrNo wanbeiyu_slidepad_release(WanbeiyuSlidepad *sp)
{
    return wanbeiyu_slidepad_hold(sp, WANBEIYU_SLIDEPAD_AXIS_NEUTRAL, WANBEIYU_SLIDEPAD_AXIS_NEUTRAL);
}