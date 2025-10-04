#include <mdm.h>
#include <constants.h>

#include <stdio.h>
#include <stdlib.h>

#include <iostream>

namespace mdm{
   namespace Common
   {

    //Tool Function
    double int_pow(double x, __int64 n) {
        double result = 1.0;
        while (n > 0) {
            if (n & 1) result *= x;
            x *= x;
            n >>= 1;
        }
        return result;
    }

    double nth_root(double x, int n, int iterations) {
        if (x == 0.0) return 0.0;
        double guess = x / n;
        for (int i = 0; i < iterations; i++) {
            double num = (n - 1) * guess + x / int_pow(guess, n - 1);
            guess = num / n;
        }
        return guess;
    }

    int is_integer(double y) {
        __int64 yi = (__int64)y;
        return (double)yi == y;
    }

    int is_odd_integer(__int64 y) {
        return (y % 2 != 0);
    }

    void approximate_fraction_cf(double value, int max_den, __int64 *p, __int64 *q) {
        __int64 n0 = 0, d0 = 1, n1 = 1, d1 = 0;
        double x = value;
        while (1) {
            __int64 a = (__int64)x;
            __int64 n2 = a * n1 + n0;
            __int64 d2 = a * d1 + d0;

            if (d2 > max_den) break;

            n0 = n1; d0 = d1;
            n1 = n2; d1 = d2;

            x = 1.0 / (x - a);
            if (x > 1e9) break;
        }

        *p = n1;
        *q = d1;
    }

    //First Part
    float Pow(float x, float y) {
        if (y == 0.0) return 1.0;
        if (x == 0.0) return (y > 0.0) ? 0.0 : 1e308; 

        if (x < 0.0) {
            if (!is_integer(y)) {
                return 0.0; // NaN
            }
            __int64 yi = (__int64)y;
            double base = int_pow(-x, yi);
            if (y < 0) base = 1.0 / base;
            return is_odd_integer(yi) ? -base : base;
        }

        if (is_integer(y)) {
            __int64 yi = (__int64)y;
            if (y < 0) return 1.0 / int_pow(x, -yi);
            return int_pow(x, yi);
        }

        __int64 ipart = (__int64)y;
        double fpart = y - (double)ipart;

        double result = (ipart >= 0) ? int_pow(x, ipart) : 1.0 / int_pow(x, -ipart);

        __int64 p, q;
        approximate_fraction_cf(fpart, 1000, &p, &q); // limits 1000

        //x^(p/q) = (x^p)^(1/q)
        double base = int_pow(x, p);
        double root = nth_root(base, (int)q, 40);

        return result * root;
    }
    
        float Pow(float x, int n)
        {
            float result = 1.0f;
            for (int i = 0; i < n; i++)
            {
                result *= x;
            }
            
            return result;
        }
    
        int Factorial(int x)
        {
            int result = 1;
            for (int i = 1; i < x; i++)
            {
                result *= i + 1;
            }

            return result;
            
        }

        float Abs(float x)
        {
            return (x > 0.0f)? x : -x;
        }

        float Mod(float x, float y)
        {
            if(y == 0.0f)
                return 0.0f;

            int temp = (int)(x / y);
            return x - (float)temp * y;
        }

///////////////////////////////////////////////////////////////////////////////////////////////////        

        float Ceil(float x)
        {
            return (Mod(x, 2.0f) == 0.0f)? x : (int)x + 1;
        }

        float Floor(float x)
        {
            return (int)x;
        }

///////////////////////////////////////////////////////////////////////////////////////////////////
        //From https://github.com/id-Software/Quake-III-Arena/blob/master/code/game/q_math.c#L552
        float Rsqrt(float x)
        {
            long i;
	        float x2, y;
	        const float threehalfs = 1.5F;

	        x2 = x * 0.5F;
	        y  = x;
    	    i  = * ( long * ) &y;						// evil floating point bit level hacking
    	    i  = 0x5f375a86 - ( i >> 1 );               // what the fuck?
    	    y  = * ( float * ) &i;
    	    y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration
    	    y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed
    
	        return y;
        }

        float Sqrt(float x)
        {
            long i;
	        float y;

	        y  = x;
	        i  = * ( long * ) &y;						// evil floating point bit level hacking
	        i  = ( i >> 1 ) + 0x1fc00000;               // new magic number
	        y  = * ( float * ) &i;
            y = 0.5f * ( y + x / y);// 1st iteration
            y = 0.5f * ( y + x / y);// 2nd iteration
            //y = 0.5f * ( y + number / y);// 3rd iteration

	        return y;
        }

/////////////////////////////////////////////////////////////////////////////////////////////////

        float Exp(float x)
        {
            return Pow(MDM_E, x);
        }

        float Ln(float x)
        {
            union { float d; unsigned __int64 i; } vx = { x };
            __int64 exp = ((vx.i >> 23) & 0xFF) - 127;
            vx.i = (vx.i & 0x7FFFFF) | 0x3F800000;
            float y = vx.d;

            float t = (y - 1.0) / (y + 1.0);
            float t2 = t * t;
            float t3 = t2 * t;
            float t5 = t3 * t2;
            float t7 = t5 * t2;
            float t9 = t7 * t2;
            float t11 = t9 * t2;
            float t13 = t11 * t2;

            float ln_y = 2.0 * ( t + t3/3.0 + t5/5.0 + t7/7.0 + t9/9.0 + t11/11.0 + t13/13.0 );

            float ln_x = ln_y + exp * MDM_LN2;
            return ln_x;
        }

        double Ln(double x)
        {
            union { double d; unsigned __int64 i; } vx = { x };
            __int64 exp = ((vx.i >> 52) & 0x7FF) - 1023;
            vx.i = (vx.i & (unsigned __int64)0xFFFFFFFFFFFFF) | (unsigned __int64)0x3FF0000000000000;
            double y = vx.d;

            double t = (y - 1.0) / (y + 1.0);
            double t2 = t * t;
            double t3 = t2 * t;
            double t5 = t3 * t2;
            double t7 = t5 * t2;
            double t9 = t7 * t2;
            double t11 = t9 * t2;
            double t13 = t11 * t2;

            double ln_y = 2.0 * ( t + t3/3.0 + t5/5.0 + t7/7.0 + t9/9.0 + t11/11.0 + t13/13.0 );

            double ln_x = ln_y + exp * (double)MDM_LN2;
            return ln_x;
        }

        float Log2(float x)
        {
            return Ln(x) / MDM_LN2;
        }

        float Log10(float x)
        {
            return Ln(x) / MDM_LN10;
        }

        float Ldexp(float x, int exponent)
        {
            return x * Pow(2.0f, exponent);
        }

////////////////////////////////////////////////////////////////////////////////////////////////        
        //From DeepSeek :-)
        float Rexp(float x, int* exponent)
        {
            unsigned int bits;
            memcpy(&bits, &x, sizeof(bits));

            unsigned int sign_mask = 0x80000000;
            unsigned int exp_mask  = 0x7F800000;
            unsigned int mant_mask = 0x007FFFFF;

            int sign_bit = (bits & sign_mask) != 0;
            int exp_bits = (bits & exp_mask) >> 23;
            unsigned int mant_bits = bits & mant_mask;

            const int bias = 127;

            int real_exp = exp_bits - bias;

            *exponent = real_exp + 1;

            unsigned int new_exp_bits = (bias - 1) << 23;
            unsigned int new_bits = (sign_bit ? sign_mask : 0) | new_exp_bits | mant_bits;

            float result;
            memcpy(&result, &new_bits, sizeof(result));
            return result;
        }

        float Decompose(float x, int* integer)
        {
            *integer = (int)x;
            return x - *integer;
        }
/////////////////////////////////////////////////////////////////////////////////////////////////////

        float Sin(float x)
        {
            x = Mod(x, MDM_2PI);
           if (x > MDM_PI) {
                x -= MDM_2PI;
            } else if (x < -MDM_PI) {
                x += MDM_2PI;
            }

            float term = x;
            float result = term;
 
            for (int n = 1; n < 20; ++n) {
                //(-1)^n * x^(2n+1) / (2n+1)!
                term *= -x * x / ((2 * n) * (2 * n + 1));
                result += term;
            }
    
            return result;
        }

        float Cos(float x)
        {
            x = Mod(x, MDM_2PI);

            if (x > MDM_PI) {
                x -= MDM_2PI;
            } else if (x < -MDM_PI) {
                x += MDM_2PI;
            }

            float term = 1.0f;
            float result = term;
 
            for (int n = 1; n < 20; ++n) {
                //(-1)^n * x^(2n) / (2n)!
                term *= -x * x / ((2 * n) * (2 * n - 1));
                result += term;
            }
    
            return result;
        }

        float ArcSin(float x)
        {
            float result = 0.0f;

            for (int i = 0; i < 8; i++)
            {
                result += ( (float)Factorial(2 * i) / 
                            (Pow(4.0f, i) * (2 * i + 1) * Pow((float)Factorial(i), 2) ) )
                            * Pow(x, 2 * i + 1);
            }
            
            return result;
        }

        float ArcCos(float x)
        {
            return MDM_PI_2 - ArcSin(x);
        }

        float ArcTan(float x)
        {
            float result = 0.0f;

            for (int i = 0; i < 24; i++)
            {
                result += (Pow(-1.0f, i) / (2 * i + 1)) * Pow(x, 2 * i + 1);
            }
            
            return result;
        }

        float ArcTan2(float y, float x)
        {
            return ArcTan(y / x);
        }

        float Sinh(float x)
        {
            float term = x;
            float result = term;

            for (int i = 1; i < 20; i++)
            {
                term *= (x * x) / ((2 * i) * (2 * i + 1));
                result += term;
            }
            
            return result;
        }

        float Cosh(float x)
        {
            float term = 1.0f;
            float result = term;

            for (int i = 1; i < 20; i++)
            {
                term *= (x * x) / ((2 * i) * (2 * i - 1));
                result += term;
            }
            
            return result;
        }

        float Tanh(float x)
        {
            return Sinh(x) / Cosh(x);
        }

        //Second Part
        float Max(float a, float b)
        {
            return (a > b)? a : b;
        }

        float Min(float a, float b)
        {
            return (a < b)? a :b;
        }

        float Hypot(float x, float y)
        {
            return Sqrt(x * x + y * y);
        }        

        float Cbrt(float x)
        {
            long i;
	        float y;

	        y  = x;
	        i  = * ( long * ) &y;					 // evil floating point bit level hacking
	        i  = ( i / 3 ) + 0x2a9f84fe;               // new magic number
	        y  = * ( float * ) &i;
            y = MDM_THIRD * (2.0f * y + x / (y*y));// 1st iteration
            y = MDM_THIRD * (2.0f * y + x / (y*y));// 2nd iteration
            y = MDM_THIRD * (2.0f * y + x / (y*y));// 3rd iteration
            y = MDM_THIRD * (2.0f * y + x / (y*y));// 4th iteration

	        return y;
        }

        float Expml(float x)
        {
            return Exp(x) - 1.0f;
        }

        float Lnlp(float x)
        {
            return Ln(1.0f + x);
        }

        float ArSinh(float x)
        {
            return Ln(x + Sqrt(x * x + 1.0f));
        }

        float ArCosh(float x)
        {
            return Ln(x + Sqrt(x * x - 1.0f));
        }

        float ArTanh(float x)
        {
            return 0.5f * Ln((1.0f + x) / (1.0f - x));
        }

        int Trunc(float x)
        {
            return (int)x;
        }

        int Round(float x)
        {
            int temp;
            float r;
            r = Decompose(x, &temp);
            return (r >= 0.5f)? (int)(x + 1.0f) : (int)x;
        }

        float PosInf()
        {
            unsigned __int64 pos_inf_bits = 0x7FF0000000000000;
            double pos_inf = *reinterpret_cast<double*>(&pos_inf_bits);
            return (float)pos_inf;
        }

        float NegInf()
        {
            unsigned __int64 neg_inf_bits = 0xFFF0000000000000;
            double neg_inf = *reinterpret_cast<double*>(&neg_inf_bits);
            return (float)neg_inf;
        }

        bool Isfinite(float x)
        {
            return (x != PosInf() && x != NegInf() && x == x)? true : false;
        }

        bool IsInf(float x)
        {
            return (x == PosInf() && x == NegInf()) ? true : false;
        }

        bool IsNaN(float x)
        {
            return x != x;
        }

        bool IsNormal(float x)
        {
            return (Isfinite(x) && x != 0.0f)? true : false;
        }

        bool Signbit(float x)
        {
            return (x < 0.0f)? true : false;
        }

        bool Equal(float a, float b)
        {
            return (Abs(a - b) < MDM_EPSILON)? true : false;
        }

        float ToRadian(float angle)
        {
            return angle * MDM_PI * MDM_OneHundredAndEighty;
        }

        float ToAngle(float radian)
        {
            return radian * 180.0f * MDM_PIReciprocal;
        }
   }
}