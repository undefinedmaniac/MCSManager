#include "mcscpperformancereport.h"

McscpPerformanceReport::McscpPerformanceReport()
{
}

void McscpPerformanceReport::setTps(float value)
{
    mTps = roundToTenths(value);
}

void McscpPerformanceReport::setMaxRam(float value)
{
    mMaxRam = roundToTenths(value);
}

void McscpPerformanceReport::setTotalRam(float value)
{
    mTotalRam = roundToTenths(value);
}

void McscpPerformanceReport::setFreeRam(float value)
{
    mFreeRam = roundToTenths(value);
}

void McscpPerformanceReport::setUsedRam(float value)
{
    mUsedRam = roundToTenths(value);
}

float McscpPerformanceReport::getTps() const
{
    return mTps;
}

float McscpPerformanceReport::getMaxRam() const
{
    return mMaxRam;
}

float McscpPerformanceReport::getTotalRam() const
{
    return mTotalRam;
}

float McscpPerformanceReport::getFreeRam() const
{
    return mFreeRam;
}

float McscpPerformanceReport::getUsedRam() const
{
    return mUsedRam;
}

float McscpPerformanceReport::roundToTenths(float value)
{
    value /= 10;
    return floor(value + .5) * 10;
}
