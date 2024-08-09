#include <Arduino.h>
#include "filters.h"

Filters::Filters() {
}

float Filters::RunningAverage(float* values, int numValues) {
  float sum = 0;
  for (int i = 0; i < numValues; i++) {
    sum += values[i];
  }
  return sum / numValues;
}

float Filters::ExponentialMovingAverage(float newValue, float prevEMA, float alpha) {
  return alpha * newValue + (1 - alpha) * prevEMA;
}

float Filters::LowPassFilter(float newValue, float prevValue, float alpha) {
  return alpha * newValue + (1 - alpha) * prevValue;
}

float Filters::HighPassFilter(float newValue, float prevValue, float alpha) {
  return alpha * (prevValue + newValue - prevValue);
}

float Filters::MedianFilter(float* values, int numValues) {
  for (int i = 0; i < numValues - 1; i++) {
    for (int j = i + 1; j < numValues; j++) {
      if (values[i] > values[j]) {
        float temp = values[i];
        values[i] = values[j];
        values[j] = temp;
      }
    }
  }
  
  if (numValues % 2 == 0) {
    return (values[numValues / 2 - 1] + values[numValues / 2]) / 2;
  } else {
    return values[numValues / 2];
  }
}