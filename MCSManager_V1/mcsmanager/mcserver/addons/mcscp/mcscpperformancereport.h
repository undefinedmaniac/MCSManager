#ifndef MCSCPPERFORMANCEREPORT_H
#define MCSCPPERFORMANCEREPORT_H

#include <math.h>

class McscpPerformanceReport
{
public:
    McscpPerformanceReport();

    void setTps(float value);
    void setMaxRam(float value);
    void setTotalRam(float value);
    void setFreeRam(float value);
    void setUsedRam(float value);

    float getTps() const;
    float getMaxRam() const;
    float getTotalRam() const;
    float getFreeRam() const;
    float getUsedRam() const;

private:
    float mTps, mMaxRam, mTotalRam, mFreeRam, mUsedRam;

    static float roundToTenths(float value);
};

#endif // MCSCPPERFORMANCEREPORT_H
