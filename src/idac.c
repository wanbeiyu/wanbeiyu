#include <wanbeiyu/idac.h>

#include <assert.h>

errno_t wanbeiyu_idac_set_sink(WanbeiyuIDAC *idac, uint8_t val)
{
    if (idac == NULL)
    {
        return EINVAL;
    }
    assert(idac->set_sink != NULL);

    return idac->set_sink(idac, val);
}

errno_t wanbeiyu_idac_set_source(WanbeiyuIDAC *idac, uint8_t val)
{
    if (idac == NULL)
    {
        return EINVAL;
    }
    assert(idac->set_source != NULL);

    return idac->set_source(idac, val);
}