#ifndef WANBEIYU_INTERNAL_H
#define WANBEIYU_INTERNAL_H

#ifdef __cplusplus
extern "C"
{
#endif

    static inline double wanbeiyu_internal_remap(double val, double in_min, double in_max, double out_min, double out_max)
    {
        return (val - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
    }

#ifdef __cplusplus
}
#endif

#endif // WANBEIYU_INTERNAL_H