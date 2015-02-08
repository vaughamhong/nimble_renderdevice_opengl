//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_math_curve_h__
#define __nimble_math_curve_h__

//////////////////////////////////////////////////////////////////////////

#include <stdint.h>
#include <nimble/core/assert.h>
#include <nimble/math/mathops.h>

//////////////////////////////////////////////////////////////////////////

namespace nimble{
	namespace math{
        
        //! animation curves
        enum eCurve{
            kCurveEaseInOut,
            kCurveEaseIn,
            kCurveEaseOut,
            kCurveLinear
        };
        
        //! interpolate curve
        template <typename T>
        T interpolate(float t, T &p0, T &p1, eCurve curve){
            if(t == 0.0){
                return p0;
            }else if(t == 1.0f){
                return p1;
            }else if(curve == kCurveEaseInOut){
                float t1 = 4.0f / 10.0f;
                float t2 = 2.0f / 10.0f;
                float t3 = 4.0f / 10.0f;
                float tt = math::scalerEaseInEaseOut(t1, t2, t3, 1.0f, t);
                return p0 * (1 - tt) + p1 * (tt);
            }else if(curve == kCurveEaseIn){
                float t1 = 1.0f / 2.0f;
                float t2 = 1.0f / 2.0f;
                float t3 = 0.0f;
                float tt = math::scalerEaseInEaseOut(t1, t2, t3, 1.0f, t);
                return p0 * (1 - tt) + p1 * (tt);
            }else if(curve == kCurveEaseOut){
                float t1 = 0.0f;
                float t2 = 1.0f / 2.0f;
                float t3 = 1.0f / 2.0f;
                float tt = math::scalerEaseInEaseOut(t1, t2, t3, 1.0f, t);
                return p0 * (1 - tt) + p1 * (tt);
            }else if(curve == kCurveLinear){
                return p0 * (1 - t) + p1 * (t);
            }else{
                return p1;
            }
        }
        //! interpolate curve
        template <typename T>
        T interpolateScaler(float t, T p0, T p1, eCurve curve){
            if(t == 0.0){
                return p0;
            }else if(t == 1.0f){
                return p1;
            }else if(curve == kCurveEaseInOut){
                float t1 = 4.0f / 10.0f;
                float t2 = 2.0f / 10.0f;
                float t3 = 4.0f / 10.0f;
                float tt = math::scalerEaseInEaseOut(t1, t2, t3, 1.0f, t);
                return p0 * (1 - tt) + p1 * (tt);
            }else if(curve == kCurveEaseIn){
                float t1 = 1.0f / 2.0f;
                float t2 = 1.0f / 2.0f;
                float t3 = 0.0f;
                float tt = math::scalerEaseInEaseOut(t1, t2, t3, 1.0f, t);
                return p0 * (1 - tt) + p1 * (tt);
            }else if(curve == kCurveEaseOut){
                float t1 = 0.0f;
                float t2 = 1.0f / 2.0f;
                float t3 = 1.0f / 2.0f;
                float tt = math::scalerEaseInEaseOut(t1, t2, t3, 1.0f, t);
                return p0 * (1 - tt) + p1 * (tt);
            }else if(curve == kCurveLinear){
                return p0 * (1 - t) + p1 * (t);
            }else{
                return p1;
            }
        }
	};
};

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////