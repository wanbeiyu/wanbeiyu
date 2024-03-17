#include <wanbeiyu/slidepad.h>
#include "internal.h"

#include <assert.h>

errno_t wanbeiyu_slidepad_init(WanbeiyuSlidepad *sp, WanbeiyuIDAC *horizontal, WanbeiyuIDAC *vertical)
{
    if (sp == NULL ||
        horizontal == NULL ||
        vertical == NULL)
    {
        return EINVAL;
    }

    sp->horizontal = horizontal;
    sp->vertical = vertical;

    return 0;
}

errno_t wanbeiyu_slidepad_hold(WanbeiyuSlidepad *sp, uint8_t x, uint8_t y)
{
    if (sp == NULL)
    {
        return EINVAL;
    }
    assert(sp->horizontal != NULL &&
           sp->vertical != NULL);

    errno_t horizontal_err = WANBEIYU_SLIDEPAD_AXIS_NEUTRAL < x
                                 ? /* 129, 130, ..., 255 */ sp->horizontal->set_sink(sp->horizontal, (uint8_t)wanbeiyu_internal_remap(x, 129, UINT8_MAX, 0, UINT8_MAX))
                                 : /* 128, 127, ..., 0 */ sp->horizontal->set_source(sp->horizontal, (uint8_t)wanbeiyu_internal_remap(x, 128, 0, 0, UINT8_MAX));
    errno_t vertical_err = WANBEIYU_SLIDEPAD_AXIS_NEUTRAL < y
                               ? sp->vertical->set_sink(sp->vertical, (uint8_t)wanbeiyu_internal_remap(y, 129, UINT8_MAX, 0, UINT8_MAX))
                               : sp->vertical->set_source(sp->vertical, (uint8_t)wanbeiyu_internal_remap(y, 128, 0, 0, UINT8_MAX));
    if (horizontal_err != 0 ||
        vertical_err != 0)
    {
        return EIO;
    }

    return 0;
}

errno_t wanbeiyu_slidepad_release(WanbeiyuSlidepad *sp)
{
    return wanbeiyu_slidepad_hold(sp, WANBEIYU_SLIDEPAD_AXIS_NEUTRAL, WANBEIYU_SLIDEPAD_AXIS_NEUTRAL);
}