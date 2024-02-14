#include "wanbeiyu.h"

#include <stdlib.h>

void wby_touchscreen_hold(wby_touchscreen_t *ts, uint16_t x, uint16_t y)
{
    if (ts == NULL)
    {
        return;
    }

    ts->vertical->set_wiper_position(ts->vertical, y);
    ts->horizontal->set_wiper_position(ts->horizontal, x);

    ts->vertical->power_on(ts->vertical);
    ts->horizontal->power_on(ts->horizontal);
    ts->sw->on(ts->sw);
}

void wby_touchscreen_release(wby_touchscreen_t *ts)
{
    if (ts == NULL)
    {
        return;
    }

    ts->sw->off(ts->sw);
    ts->vertical->shutdown(ts->vertical);
    ts->horizontal->shutdown(ts->horizontal);
}

wby_touchscreen_t *wby_touchscreen_new(wby_rdac_t *vertical, wby_rdac_t *horizontal, wby_spst_switch_t *sw)
{
    if (vertical == NULL || horizontal == NULL || sw == NULL)
    {
        return NULL;
    }

    wby_touchscreen_t *ts = (wby_touchscreen_t *)malloc(sizeof(wby_touchscreen_t));
    if (ts == NULL)
    {
        return NULL;
    }

    ts->vertical = vertical;
    ts->horizontal = horizontal;
    ts->sw = sw;

    wby_touchscreen_release(ts);

    return ts;
}

void wby_touchscreen_delete(wby_touchscreen_t *ts)
{
    if (ts == NULL)
    {
        return;
    }

    free(ts);
}