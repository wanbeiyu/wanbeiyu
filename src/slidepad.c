#include <wanbeiyu.h>
#include "internal.h"

#include <assert.h>

wanbeiyu_error_t wanbeiyu_slidepad_init(wanbeiyu_slidepad_t *sp, wanbeiyu_idac_t *h, wanbeiyu_idac_t *v)
{
    if (sp == NULL ||
        h == NULL ||
        v == NULL)
    {
        return WANBEIYU_EINVAL;
    }

    sp->h_ = h;
    sp->v_ = v;

    return WANBEIYU_OK;
}

wanbeiyu_error_t wanbeiyu_slidepad_hold(wanbeiyu_slidepad_t *sp, uint8_t x, uint8_t y)
{
    if (sp == NULL)
    {
        return WANBEIYU_EINVAL;
    }
    assert(sp->h_ != NULL &&
           sp->v_ != NULL);

    wanbeiyu_error_t h_ret = WANBEIYU_SLIDEPAD_NEUTRAL < x
                                 ? /* 129, 130, ..., 255 */ sp->h_->set_sink(sp->h_, (uint8_t)wanbeiyu_internal_remap(x, 129, UINT8_MAX, 0, UINT8_MAX))
                                 : /* 128, 127, ..., 0 */ sp->h_->set_source(sp->h_, (uint8_t)wanbeiyu_internal_remap(x, 128, 0, 0, UINT8_MAX));
    wanbeiyu_error_t v_ret = WANBEIYU_SLIDEPAD_NEUTRAL < y
                                 ? sp->v_->set_sink(sp->v_, (uint8_t)wanbeiyu_internal_remap(y, 129, UINT8_MAX, 0, UINT8_MAX))
                                 : sp->v_->set_source(sp->v_, (uint8_t)wanbeiyu_internal_remap(y, 128, 0, 0, UINT8_MAX));
    if (h_ret != WANBEIYU_OK ||
        v_ret != WANBEIYU_OK)
    {
        return WANBEIYU_EIO;
    }

    return WANBEIYU_OK;
}

wanbeiyu_error_t wanbeiyu_slidepad_release(wanbeiyu_slidepad_t *sp)
{
    return wanbeiyu_slidepad_hold(sp, WANBEIYU_SLIDEPAD_NEUTRAL, WANBEIYU_SLIDEPAD_NEUTRAL);
}