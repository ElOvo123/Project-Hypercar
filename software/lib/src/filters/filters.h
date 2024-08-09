#ifndef FILTERS_H
#define FILTERS_H

class Filters
{
private:

public:
    Filters();

    float RunningAverage(float* values, int numValues);
    float ExponentialMovingAverage(float newValue, float prevEMA, float alpha);
    float LowPassFilter(float newValue, float prevValue, float alpha);
    float HighPassFilter(float newValue, float prevValue, float alpha);
    float MedianFilter(float* values, int numValues);
};

#endif
