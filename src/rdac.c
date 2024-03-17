#include <wanbeiyu/rdac.h>

#include <assert.h>

errno_t wanbeiyu_rdac_set_wiper_position(WanbeiyuRDAC *rdac, uint16_t pos)
{
    if (rdac == NULL)
    {
        return EINVAL;
    }
    assert(rdac->set_wiper_position != NULL);

    return rdac->set_wiper_position(rdac, pos);
}