//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_math_vectorops_h__
#define __nimble_math_vectorops_h__

///////////////////////////////////////////////////////////////////////////////

#include <math.h>
#include <cstring>

///////////////////////////////////////////////////////////////////////////////

// TODO: split inline template code into separate inline file

///////////////////////////////////////////////////////////////////////////////

namespace nimble{
	namespace math{

		// template data
		template <typename T, int N>
        struct vector_t{
		public:
            T m_array[N];
		public:
			vector_t(){
				memset(m_array, 0, sizeof(m_array));
			}
		};

		// template meta
		template <typename T, int N>
		class VectorOps{
		public:
			static void add(T* v1, T const* v2, T const* v3){
				v1[N - 1] = v2[N - 1] + v3[N - 1];
				VectorOps<T, N - 1>::add(v1, v2, v3);
			}
			static void sub(T* v1, T const* v2, T const* v3){
				v1[N - 1] = v2[N - 1] - v3[N - 1];
				VectorOps<T, N - 1>::sub(v1, v2, v3);
			}
			static void mul(T* v1, T const* v2, T const* v3){
				v1[N - 1] = v2[N - 1] * v3[N - 1];
				VectorOps<T, N - 1>::mul(v1, v2, v3);
			}
			static void mul(T* v1, T const* v2, T value){
				v1[N - 1] = v2[N - 1] * value;
				VectorOps<T, N - 1>::mul(v1, v2, value);
			}
			static void div(T* v1, T const* v2, T const* v3){
				v1[N - 1] = v2[N - 1] / v3[N - 1];
				VectorOps<T, N - 1>::div(v1, v2, v3);
			}
			static void div(T* v1, T const* v2, T value){
				v1[N - 1] = v2[N - 1] / value;
				VectorOps<T, N - 1>::div(v1, v2, value);
			}
			static void center(T* v1, T const* v2, T const* v3){
				v1[N - 1] = v2[N - 1] + (v3[N - 1] - v2[N - 1]) / 2;
				VectorOps<T, N - 1>::copy(v1, v2, v3);
			}
			static void copy(T* v1, T const* v2){
				v1[N - 1] = v2[N - 1];
				VectorOps<T, N - 1>::copy(v1, v2);
			}
			static void copy(T* v1, T value){
				v1[N - 1] = value;
				VectorOps<T, N - 1>::copy(v1, value);
			}
			static float dot(T const* v1, T const* v2){
				return v1[N - 1] * v2[N - 1] + VectorOps<T, N - 1>::dot(v1, v2);
			}
			static bool eq(T const* v1, T const* v2){
				return v1[N - 1] == v2[N - 1] && VectorOps<T, N - 1>::eq(v1, v2);
			}
			static void zero(T* v1){
				return v1[N - 1] == static_cast<T>(0) && VectorOps<T, N - 1>::zero(v1);
			}
		};
		// template base case
		template <typename T>
		class VectorOps <T, 1>{
		public:
			static void add(T* v1, T const* v2, T const* v3){
				v1[0] = v2[0] + v3[0];
			}
			static void sub(T* v1, T const* v2, T const* v3){
				v1[0] = v2[0] - v3[0];
			}
			static void mul(T* v1, T const* v2, T const* v3){
				v1[0] = v2[0] * v3[0];
			}
			static void mul(T* v1, T const* v2, T value){
				v1[0] = v2[0] * value;
			}
			static void div(T* v1, T const* v2, T const* v3){
				v1[0] = v2[0] / v3[0];
			}
			static void div(T* v1, T const* v2, T value){
				v1[0] = v2[0] / value;
			}
			static void center(T* v1, T const* v2, T const* v3){
				v1[0] = v2[0] + (v3[0] - v2[0]) / 2;
			}
			static void copy(T* v1, T const* v2){
				v1[0] = v2[0];
			}
			static void copy(T* v1, T value){
				v1[0] = value;
			}
			static float dot(T const* v1, T const* v2){
				return v1[0] * v2[0];
			}
			static bool eq(T const* v1, T const* v2){
				return v1[0] == v2[0];
			}
			static void zero(T* v1){
				return v1[0] == static_cast<T>(0);
			}
		};

		// Vector functions
		template <typename T, int N> void vecAddUnrolled(T* v1, T const* v2, T const* v3);
		template <typename T, int N> void vecAdd(T* v1, T const* v2, T const* v3);
		template <typename T, int N> void vecAdd(T* v1, T const* v2, T const* v3, unsigned int size);
		template <typename T, int N> void vecSubUnrolled(T* v1, T const* v2, T const* v3);
		template <typename T, int N> void vecSub(T* v1, T const* v2, T const* v3);
		template <typename T, int N> void vecSub(T* v1, T const* v2, T const* v3, unsigned int size);
		template <typename T, int N> void vecMin(T* v1, T const* v2, T const* v3);
		template <typename T, int N> void vecMax(T* v1, T const* v2, T const* v3);
		template <typename T, int N> void vecMulUnrolled(T* v1, T const* v2, T const* v3);
		template <typename T, int N> void vecMul(T* v1, T const* v2, T const* v3);
		template <typename T, int N> void vecMul(T* v1, T const* v2, T const* v3, unsigned int size);
		template <typename T, int N> void vecMulUnrolled(T* v1, T const* v2, T value);
		template <typename T, int N> void vecMul(T* v1, T const* v2, T value);
		template <typename T, int N> void vecMul(T* v1, T value);
		template <typename T, int N> void vecMul(T* v1, T const* v2, T value, unsigned int size);
		template <typename T, int N> void vecDivUnrolled(T* v1, T const* v2, T const* v3);
		template <typename T, int N> void vecDiv(T* v1, T const* v2, T const* v3);
		template <typename T, int N> void vecDiv(T* v1, T const* v2, T const* v3, unsigned int size);
		template <typename T, int N> void vecDivUnrolled(T* v1, T const* v2, T value);
		template <typename T, int N> void vecDiv(T* v1, T const* v2, T value);
		template <typename T, int N> void vecDiv(T* v1, T const* v2, T value, unsigned int size);
		template <typename T, int N> void vecDivUnrolled(T* v1, T value);
		template <typename T, int N> void vecDiv(T* v1, T value);
		template <typename T, int N> void vecCenterUnrolled(T* v1, T const* v2, T const* v3);
		template <typename T, int N> void vecCenter(T* v1, T const* v2, T const* v3);
		template <typename T, int N> void vecCopyUnrolled(T* v1, T const* v2);
		template <typename T, int N> void vecCopy(T* v1, T const* v2);
		template <typename T, int N> void vecCopy(T* v1, T const* v2, unsigned int size);
		template <typename T, int N> void vecCopyUnrolled(T* v1, T value);
		template <typename T, int N> void vecCopy(T* v1, T value);
		template <typename T, int N> void vecCopy(T* v1, T value, unsigned int size);
		template <typename T, int N> void vecDotUnrolled(float* retValue, T const* v1, T const* v2);
		template <typename T, int N> void vecDot(float* retValue, T const* v1, T const* v2);
		template <typename T, int N> void vecDot(float* retValue, T const* v1, T const* v2, unsigned int size);
		template <typename T, int N> void vecLenUnrolled(float* retValue, T const* v1);
		template <typename T, int N> void vecLen(float* retValue, T const* v1);
		template <typename T, int N> void vecLen(float* retValue, T const* v1, unsigned int size);
		template <typename T, int N> void vecNorUnrolled(T* v1);
		template <typename T, int N> void vecNor(T* v1);
		template <typename T, int N> void vecNor(T* v1, unsigned int size);
		template <typename T, int N> bool vecEqUnrolled(T const* v1, T const* v2);
		template <typename T, int N> bool vecEq(T const* v1, T const* v2);
		template <typename T, int N> void vecZeroUnrolled(T* v1);
		template <typename T, int N> void vecZero(T* v1);
		template <typename T, int N> void vecZero(T* v1, unsigned int size);
		template <typename T, int N> void vecCrs(T* v1, T const* v2, T const* v3);
        template <typename T, int N> void vecSet(T* v1, T value);
        template <typename T, int N> void vecUnit(T* v1, T const* v2);

		// Vector inline
		#include "vectorops.inline.h"
	};
};

///////////////////////////////////////////////////////////////////////////////

#endif

///////////////////////////////////////////////////////////////////////////////