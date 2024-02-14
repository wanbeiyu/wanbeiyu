#include "wanbeiyu.h"

#include <stdlib.h>

void wby_slidepad_hold(wby_slidepad_t *sp, uint16_t x, uint16_t y)
{
    if (sp == NULL)
    {
        return;
    }

    if (x == WBY_SLIDEPAD_NEUTRAL)
    {
        sp->horizontal->source(sp->horizontal, 0);
    }
    else if (WBY_SLIDEPAD_NEUTRAL < x)
    {
        // 32768-65535
        // x - WBY_SLIDEPAD_NEUTRAL = 1-32768
        sp->horizontal->sink(sp->horizontal, (uint16_t)(((double)(x - WBY_SLIDEPAD_NEUTRAL) / 32768) * UINT16_MAX));
    }
    else
    {
        // 0-32766
        // WBY_SLIDEPAD_NEUTRAL - x = 1-32767
        sp->horizontal->source(sp->horizontal, (uint16_t)(((double)(WBY_SLIDEPAD_NEUTRAL - x) / 32767) * UINT16_MAX));
    }

    if (y == WBY_SLIDEPAD_NEUTRAL)
    {
        sp->vertical->source(sp->vertical, 0);
    }
    else if (WBY_SLIDEPAD_NEUTRAL < y)
    {
        sp->vertical->sink(sp->vertical, (uint16_t)(((double)(y - WBY_SLIDEPAD_NEUTRAL) / 32768) * UINT16_MAX));
    }
    else
    {
        sp->vertical->source(sp->vertical, (uint16_t)(((double)(WBY_SLIDEPAD_NEUTRAL - y) / 32767) * UINT16_MAX));
    }
}

void wby_slidepad_release(wby_slidepad_t *sp)
{
    if (sp == NULL)
    {
        return;
    }

    wby_slidepad_hold(sp, WBY_SLIDEPAD_NEUTRAL, WBY_SLIDEPAD_NEUTRAL);
}

wby_slidepad_t *wby_slidepad_new(wby_idac_t *vertical, wby_idac_t *horizontal)
{
    if (vertical == NULL || horizontal == NULL)
    {
        return NULL;
    }

    wby_slidepad_t *sp = (wby_slidepad_t *)malloc(sizeof(wby_slidepad_t));
    if (sp == NULL)
    {
        return NULL;
    }

    sp->vertical = vertical;
    sp->horizontal = horizontal;

    wby_slidepad_release(sp);

    return sp;
}

void wby_slidepad_delete(wby_slidepad_t *sp)
{
    if (sp == NULL)
    {
        return;
    }

    free(sp);
}