#include <Arduino.h>
#include "math_lib.h"

MathLib::MathLib(void) {
}

float MathLib::Add(float a, float b) {
  return a + b;
}

float MathLib::Subtract(float a, float b) {
  return a - b;
}

float MathLib::Multiply(float a, float b) {
  return a * b;
}

float MathLib::Divide(float a, float b) {
  if (b != 0){
    return a/b;
  }else{
    return 0;
  }  
}

float MathLib::Sin(float angle) {
  return sinf(angle);
}

float MathLib::Cos(float angle) {
  return cosf(angle);
}

float MathLib::Tan(float angle) {
  return tanf(angle);
}

float MathLib::Asin(float angle) {
  return asinf(angle);
}

float MathLib::Acos(float angle) {
  return acosf(angle);
}

float MathLib::Atan(float angle) {
  return atanf(angle);
}

float MathLib::Pow(float base, float exponent) {
  return powf(base, exponent);
}

float MathLib::Sqrt(float value) {
  return sqrtf(value);
}

float MathLib::Cbrt(float value) {
  return cbrtf(value);
}

float MathLib::Exp(float value) {
  return expf(value);
}

float MathLib::Log(float value) {
  return logf(value);
}

float MathLib::Log10(float value) {
  return log10f(value);
}

float MathLib::Round(float value) {
  return roundf(value);
}

float MathLib::Floor(float value) {
  return floorf(value);
}

float MathLib::Ceil(float value) {
  return ceilf(value);
}

float MathLib::Min(float a, float b) {
  if (a < b){
    return a;
  }else{
    return b;
  }   
}

float MathLib::Max(float a, float b) {
  if (a > b){
    return a;
  }else{
    return b;
  }  
}

float MathLib::Abs(float value) {
  return fabsf(value);
}

float MathLib::Mod(float a, float b) {
  return fmodf(a, b);
}

float MathLib::Map(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

float MathLib::Clamp(float value, float min_val, float max_val) {
  return max(min_val, min(max_val, value));
}

float MathLib::Lerp(float a, float b, float t) {
  return a + t * (b - a);
}