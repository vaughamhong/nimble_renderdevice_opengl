//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_math_matrixops_h__
#define __nimble_math_matrixops_h__

///////////////////////////////////////////////////////////////////////////////

#include <nimble/math/vectorops.h>

///////////////////////////////////////////////////////////////////////////////

namespace nimble{
	namespace math{

		//! matrix x matrix unrolled
		template <typename T, int R, int C> void matMulMatUnrolled(T* m1, T const* m2);
		//! matrix x matrix
		template <typename T, int R, int C> void matMulMat(T* m1, T const* m2);
		//! matrix x matrix unrolled
		template <typename T, int R, int C> void matMulMatUnrolled(T* m1, T const* m2, T const* m3);
		//! matrix x matrix
		template <typename T, int R, int C> void matMulMat(T* m1, T const* m2, T const* m3);
		//! matrix x scaler
		template <typename T, int R, int C> void matMulMat(T* m1, T const* m2, T s);
		//! matrix x vector unrolled
		template <typename T, int R, int C> void matMulVecUnrolled(T* v1, T const* m1);
		//! matrix x vector
		template <typename T, int R, int C> void matMulVec(T* v1, T const* m1);
		//! matrix x vector unrolled
		template <typename T, int R, int C> void matMulVecUnrolled(T* v1, T const* m1, T const* v2);
		//! matrix x vector
		template <typename T, int R, int C> void matMulVec(T* v1, T const* m1, T const* v2);
		//! matrix transposed unrolled
		template <typename T, int R, int C> void matTpoUnrolled(T* m1, T const* m2);
		//! matrix transposed
		template <typename T, int R, int C> void matTpo(T* m1, T const* m2);
		//! matrix transposed
		template <typename T, int R, int C> void matTpo(T* m1);
		//! matrix translate unrolled
		template <typename T, int R, int C> void matTraUnrolled(T* m1, T const* m2);
		//! matrix translate
		template <typename T, int R, int C> void matTra(T* m1, T const* m2);
		//! matrix identityunrolled
		template <typename T, int R, int C> void matIdeUnrolled(T* m1);
		//! matrix identity
		template <typename T, int R, int C> void matIde(T* m1);
		//! matrix set column
		template <typename T, int R, int C> void matSetCol(T* m1, int column, T const* m2);
		//! matrix get column
		template <typename T, int R, int C> void matGetCol(T* v1, int column, T const* m1);
		//! matrix set row
		template <typename T, int R, int C> void matSetRow(T* m1, int row, T const* m2);
		//! matrix get row
		template <typename T, int R, int C> void matGetRow(T* v1, int row, T const* m1);
		//! matrix set diagonal
		template <typename T, int R, int C> void matSetDiag(T* m1, T const* m2);
		//! matrix get diagonal
		template <typename T, int R, int C> void matGetDiag(T* v1, T const* m1);
        //! matrix get submatrix
        template <typename T, int R, int C> void matSubMat(T *m1, T const* m2, int i, int j);
        //! matrix adjugate
        template <typename T, int R, int C> void matAdj(T *m1, T const* m2);
        //! matrix cofactor
        template <typename T, int R, int C> void matCof(T *m1, T const* m2);
        //! matrix determinant
        template <typename T, int R, int C> void matDet(float* retValue, T const* m1);
        //! matrix inverse
        template <typename T, int R, int C> void matInv(T *m1, T const* m2);
		
		//! Matrix inline functions
		#include "matrixops.inline.h"
	};
};

///////////////////////////////////////////////////////////////////////////////

#endif

///////////////////////////////////////////////////////////////////////////////