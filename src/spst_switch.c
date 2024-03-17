#include <wanbeiyu/spst_switch.h>

#include <assert.h>

errno_t wanbeiyu_spst_switch_on(WanbeiyuSPSTSwitch *sw)
{
    if (sw == NULL)
    {
        return EINVAL;
    }
    assert(sw->on != NULL);

    return sw->on(sw);
}

errno_t wanbeiyu_spst_switch_off(WanbeiyuSPSTSwitch *sw)
{
    if (sw == NULL)
    {
        return EINVAL;
    }
    assert(sw->off != NULL);

    return sw->off(sw);
}