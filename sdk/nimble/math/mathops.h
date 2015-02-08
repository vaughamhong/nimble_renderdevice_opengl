//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_math_mathops_h__
#define __nimble_math_mathops_h__

//////////////////////////////////////////////////////////////////////////

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

//////////////////////////////////////////////////////////////////////////

namespace nimble{
	namespace math{
        
        // useful constants
        static const float kPI = 3.14159265358979323846f;
        static const float kHalfPI = math::kPI / 2.0f;

		//! absolute value
		template <typename T> T abs(T value){
            if(value < (T)0){
                return (T)-1 * value;
            }else{
                return value;
            }
        }
        //! clamp value
        template <typename T> T clamp(T value, T min, T max){
            if(value < min){
                value = min;
            }
            if(value > max){
                value = max;
            }
            return value;
        }
        //! power
        template <typename T> T power(T base, T exponent){
            return ::pow(base, exponent);
        }
		//! min
        template <typename T> T min(T value1, T value2){
            if(value1 < value2){
                return value1;
            }else{
                return value2;
            }
        }
        //! max
        template <typename T> T max(T value1, T value2){
            if(value1 > value2){
                return value1;
            }else{
                return value2;
            }
        }
        
		//! calculates floating point tangent
		inline float tanf(float rad){
            return ::tanf(rad);
        }
        //! calculates floating point atan
		inline float atanf(float rad){
            return ::atanf(rad);
        }
		//! calculates floating point sine
		inline float sinf(float rad){
            return ::sinf(rad);
        }
		//! calculates floating point cosine
		inline float cosf(float rad){
            return ::cosf(rad);
        }
		//! calculates floating point acosine
		inline float acosf(float rad){
            return ::acosf(rad);
        }
        
		//! calculates degrees to radians
		inline float degToRad(float deg){
            return deg * math::kPI / 180.0f;
        }
		//! calculates radians to degrees
		inline float radToDeg(float rad){
            return rad * 180.0f / math::kPI;
        }
        
        //! calculates the log
        inline float logf(float value){
            return ::logf(value);
        }
        
        //! calculates the square root
        inline float sqrt(float x){
            return ::sqrtf(x);
        }
        //! fast Square Root algorithms
		//! ref: http://en.wikipedia.org/wiki/Methods_of_computing_square_roots
		inline float fastsqrt(float x){
			int tmp = *(int *)&x;
			tmp -= 1<<23;	/* Remove last bit to not let it go to mantissa */
            /* tmp is now an approximation to logbase2(val) */
			tmp = tmp >> 1; /* divide by 2 */
			tmp += 1<<29;	/* add 64 to exponent: (e+127)/2 =(e/2)+63, */
            /* that represents (e/2)-64 but we want e/2 */
			return *(float *)&tmp;
		}
        
        //! Fast inverse square root
		inline float invsqrt(float x){
			float xhalf = 0.5f*x;
			int i = *(int *)&x;
			i = 0x5f3759df - (i >> 1);
			x = *(float *)&i;
			x = x * (1.5f - xhalf * x * x);
			return x;
		}
        
        // round a double
        inline double roundUp(double number){
            return number < 0.0 ? ceil(number) : floor(number);
        }
        // round a double down
        inline double roundDown(double number){
            return number < 0.0 ? ceil(number) : floor(number);
        }

        //! returns true if NaN
        inline bool isNaN(float x){
            return x != x;
        }
        //! returns true if NaN
        inline bool isNaN(double x){
            return x != x;
        }
		//! returns true if infinite
        inline bool isInfinite(float x){
            return !isNaN(x) && isNaN(x - x);
        }
        //! returns true if infinite
        inline bool isInfinite(double x){
            return !isNaN(x) && isNaN(x - x);
        }
        //! returns true if infinite
        inline bool isFinite(float x){
            return !isInfinite(x);
        }
        //! returns true if infinite
        inline bool isFinite(double x){
            return !isInfinite(x);
        }
        
        //! seeds our random number generator
        inline void seedRandom(unsigned int seed){
            ::srand(seed);
        }
		//! returns a random number
		inline int random(int min, int max){ 
            assert(min < max);
            int size = max - min;
            return min + (::rand() % size);
        }
        //! linear interpolate between two values
        inline float lerp(float t, float a, float b){
            return a + t * (b - a);
        }
        //! cubic hermite spline
        //! \param t scaler value in the range [0, 1]
        //! \param p0 the starting point
        //! \param p1 the ending point
        //! \param m0 the starting tangent
        //! \param m1 the ending tangent
        //! \return the value on our cubic hermite curve at time t
        inline float cubicHermite(float t, float p0, float p1, float m0, float m1){
            float t2 = t * t;
            float t3 = t2 * t;
            return (2 * t3 - 3 * t2 + 1) * p0 + (t3 - 2 * t2 + t) * m0 + (-2 * t3 + 3 * t2) * p1 + (t3 - t2) * m1;
        }
        //! interpolate
        //! \param timeToAccelerate amount of time to accelerate
        //! \param t2 amount of time to cruise
        //! \param t3 amount of time to decelerate
        //! \param x final position
        //! \param t scaler value in the range [0, 1]
        //! \return the final interpolation value at time t
        inline float scalerEaseInEaseOut(float timeToAccelerate, float timeToCruise, float timeToDecelerate, float x, float t){
            float cruisingSpeed = x / (timeToAccelerate / 2 + timeToCruise + timeToDecelerate / 2);
            float x1 = cruisingSpeed * timeToAccelerate / 2;   // distance accelerating
            float x2 = cruisingSpeed * timeToCruise;           // distance cruising
            float tt;
            
            if(t <= timeToAccelerate){
                // Acceleration
                tt = cubicHermite(t / timeToAccelerate,
                                  0, x1,
                                  0, x2 / timeToCruise * timeToAccelerate);
            }else if(t <= timeToAccelerate + timeToCruise){
                // Cruising
                tt = x1 + x2 * (t - timeToAccelerate) / timeToCruise;
            }else{
                // Deceleration
                tt = cubicHermite((t - timeToAccelerate - timeToCruise) / timeToDecelerate,
                                  x1 + x2, x,
                                  x2 / timeToCruise * timeToDecelerate, 0);
            }
            return tt;
        }

        //! nearest power of 2 rounded up
#if defined(__LP64__)
        inline int64_t pow2RoundUp(int64_t x){
#else
		inline int32_t pow2RoundUp(int32_t x){
#endif
            if(x < 0){
                return 0;
            }else{
                // the idea is to fill the lower bits with 1 and
                // do an increment at the end
                x |= x >> 1;    // eg. 10110 | 1011 = 11110
                x |= x >> 2;    // eg. 11110 | 11   = 11111
                x |= x >> 4;    // eg. 11111 | 0    = 11111
                x |= x >> 8;    // eg. 11111 | 0    = 11111
                x |= x >> 16;   // eg. 11111 | 0    = 11111
#if defined(__LP64__)
                x |= x >> 32;   // eg. 11111 | 0    = 11111
#endif
                return x + 1;   // eg. 11111 + 1    = 100000
            }
        }
	};
};

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////