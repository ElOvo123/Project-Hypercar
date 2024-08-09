#ifndef MATH_LIB_H
#define MATH_LIB_H

class MathLib
{
private:

public:
    MathLib();

    //Arithmetic
     // Basic Arithmetic
    float Add(float a, float b);
    float Subtract(float a, float b);
    float Multiply(float a, float b);
    float Divide(float a, float b);
    
    // Trigonometric Functions
    float Sin(float angle);
    float Cos(float angle);
    float Tan(float angle);
    float Asin(float value);
    float Acos(float value);
    float Atan(float value);
    
    // Power and Root Functions
    float Pow(float base, float exponent);
    float Sqrt(float value);
    float Cbrt(float value);
    
    // Exponential and Logarithmic Functions
    float Exp(float value);
    float Log(float value);
    float Log10(float value);
    
    // Rounding Functions
    float Round(float value);
    float Floor(float value);
    float Ceil(float value);
    
    // Min/Max Functions
    float Min(float a, float b);
    float Max(float a, float b);
    
    // Absolute Value
    float Abs(float value);
    
    // Modulus
    float Mod(float a, float b);
    
    // Map Function
    float Map(float x, float in_min, float in_max, float out_min, float out_max);
    
    // Utility Functions
    float Clamp(float value, float min_val, float max_val);
    float Lerp(float a, float b, float t);
    
};

#endif
