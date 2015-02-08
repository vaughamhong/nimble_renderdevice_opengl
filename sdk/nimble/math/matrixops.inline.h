//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

/************************************************************************
Multiplication matrix
************************************************************************/

//! type T, N elements, v1 = v2 * v3 (unrolls operation)
template <typename T, int R, int C> inline void matMulMatUnrolled(T* v1, T const* v2){
	vecMulUnrolled<T, R * C>(v1, v1, v2);
}
//! type T, N elements, v1 = v2 * v3
template <typename T, int R, int C> inline void matMulMat(T* v1, T const* v2){
	vecMul<T, R * C>(v1, v1, v2);
}

/************************************************************************
Multiplication matrix (R x C) * (C x R) = (R x R)
************************************************************************/

//! type T, N elements, v1 = v2 * v3 (unrolls operation)
template <typename T, int R, int C> inline void matMulMatUnrolled(T* v1, T const* v2, T const* v3){
	matMulMat<T, R, C>(v1, v2, v3);
}
//! type T, N elements, v1 = v2 * v3
template <typename T, int R, int C> inline void matMulMat(T* v1, T const* v2, T const* v3){
	static T v4[R * C];
	static T v5[R * C];
	matTpo<T, R, C>(v4, v3);
	vecCopy<T, R * C>(v5, v2);
	float retValue;
	for(int r = 0; r < R; ++r){
		for(int c = 0; c < C; ++c){
			// v2 row r
			// v4 col c
			vecDot<T, C>(&retValue, &v5[r * C], &v4[c * R]);
			// Note: row major
			v1[r * C + c] = static_cast<T>(retValue);
		}
	}
}
//! matrix x scaler
template <typename T, int R, int C> void matMulMat(T* m1, T const* m2, T s){
    for(int r = 0; r < R; ++r){
		for(int c = 0; c < C; ++c){
            m1[r * C + c] = m2[r * C + c] * s;
        }
	}
}

/************************************************************************
Multiplication vector
************************************************************************/

//! type T, N elements, v1 = v2 * v3 (unrolls operation)
template <typename T, int R, int C> inline void matMulVecUnrolled(T* v1, T const* m1){
	vecMulUnrolled<T, R * C>(v1, m1, v1);
}
//! type T, N elements, v1 = v2 * v3
template <typename T, int R, int C> inline void matMulVec(T* v1, T const* m1){
	vecMul<T, R * C>(v1, m1, v1);
}

/************************************************************************
Multiplication vector (R x C) * (C x R) = (R x R)
************************************************************************/

//! type T, N elements, v1 = v2 * v3 (unrolls operation)
template <typename T, int R, int C> inline void matMulVecUnrolled(T* v1, T const* m1, T const* v2){
	matMulVec<T, R, C>(v1, m1, v2);
}
//! type T, N elements, v1 = v2 * v3
template <typename T, int R, int C> inline void matMulVec(T* v1, T const* m1, T const* v2){
	T v3[R * C];
	matTpo<T, R, C>(v3, v2);
	float retValue;
	for(int r = 0; r < 1; ++r){
		for(int c = 0; c < R; ++c){
			vecDot<T, C>(&retValue, &v2[0], &m1[c * C]);
			// Note: row major
			v1[c] = static_cast<T>(retValue);
		}
	}
}

/************************************************************************
Transpose
************************************************************************/

//! type T, N elements, v1 = v2 (unrolls operation)
template <typename T, int R, int C> inline void matTpoUnrolled(T* v1, T const* v2){
	matTpo<T, R, C>(v1, v2);
}
//! type T, N elements, v1 = v2
template <typename T, int R, int C> inline void matTpo(T* v1, T const* v2){
	T v3[R * C];
	vecCopy<T, R * C>(v3, v2);
	for(int r = 0; r < R; ++r){
		for(int c = 0; c < C; ++c){
			// Note: row major
			v1[r * C + c] = v3[c * R + r];
		}
	}
}
//! type T, N elements, v1 = v2
template <typename T, int R, int C> inline void matTpo(T* v1){
	matTpo<T, R, C>(v1, v1);
}

/************************************************************************
Translate
************************************************************************/

//! type T, N elements, creates translation matrix m1 (unrolls operation)
template <typename T, int R, int C> void matTraUnrolled(T* m1, T const* m2){
	matTra<T, R, C>(m1, m2);
}

//! type T, N elements, creates translation matrix m1
template <typename T, int R, int C> inline void matTra(T* m1, T const* v1){
	matIde<T, R, C>(m1);
	for(int r = 0; r < R; ++r){
		m1[r * C + (C - 1)] = v1[r];
	}
}

/************************************************************************
Identity
************************************************************************/

//! type T, N elements, v1 = v2 (unrolls operation)
template <typename T, int R, int C> inline void matIdeUnrolled(T* v1){
	matIde<T, R, C>(v1);
}
//! type T, N elements, v1 = v2
template <typename T, int R, int C> inline void matIde(T* v1){
	for(int r = 0; r < R; ++r){
		for(int c = 0; c < C; ++c){
			// Note: Row major
			if(r == c){
				v1[r * C + c] = static_cast<T>(1.0f);
			}else{
				v1[r * C + c] = static_cast<T>(0.0f);
			}
		}
	}
}

/************************************************************************
Sets a column
************************************************************************/

//! type T, sets a matrix column
template <typename T, int R, int C> void matSetCol(T* m1, int column, T const* m2){
	for(int r = 0; r < R; ++r){
		m1[r * C + column] = m2[r];
	}
}

/************************************************************************
Gets column
************************************************************************/

//! type T, gets a matrix column
template <typename T, int R, int C> void matGetCol(T* m1, int column, T const* m2){
	for(int r = 0; r < R; ++r){
		m1[r] = m2[r * C + column];
	}
}

/************************************************************************
Sets a row
************************************************************************/

//! type T, sets a matrix row
template <typename T, int R, int C> void matSetRow(T* m1, int row, T const* m2){
	for(int c = 0; c < C; ++c){
		m1[row * C + c] = m2[c];
	}
}

/************************************************************************
Gets row
************************************************************************/

//! type T, gets a matrix row
template <typename T, int R, int C> void matGetRow(T* m1, int row, T const* m2){
	for(int c = 0; c < R; ++c){
		m1[c] = m2[row * C + c];
	}
}

/************************************************************************
Sets a diagonal
************************************************************************/

//! matrix set diagonal
template <typename T, int R, int C> void matSetDiag(T* m1, T const* m2){
	for(int c = 0; c < R && c < C; ++c){
		m1[c * C + c] = m2[c];
	}
}

/************************************************************************
Gets diagonal
************************************************************************/

//! matrix get diagonal
template <typename T, int R, int C> void matGetDiag(T* v1, T const* m1){
	for(int c = 0; c < R; ++c){
		v1[c] = m1[c * C + c];
	}
}

/************************************************************************
Sub matrix
************************************************************************/

//! matrix get submatrix, m1 = m2 without row i and col j
template <typename T, int R, int C> void matSubMat(T *m1, T const* m2, int i, int j){
    int cDest = 0;
	int rDest = 0;
    for(int c = 0; c < C; c++){
        if(c < j){cDest = c;}else if(c > j){cDest = (c - 1);}
        for(int r = 0; r < R; r++){
            if(r < i){rDest = r;}else if(r > i){rDest = (r - 1);}
            if(c != j && r != i){
                m1[rDest * (C-1) + cDest] = m2[r * C + c];
            }
        }
    }
}
template <> inline void matSubMat<float, 2, 2>(float *m1, float const* m2, int i, int j){
    int r = ((i + 1) % 2);
    int c = ((j + 1) % 2);
    m1[0] = m2[r * 2 + c];
}

/************************************************************************
Adjugate matrix
************************************************************************/

//! matrix adjugate
template <typename T, int R, int C> void matAdj(T *m1, T const* m2){
    T m3[R * C];
    matCof<T, R, C>(m3, m2);
    matTpo<T, R, C>(m1, m3);
}

/************************************************************************
Cofactor matrix
************************************************************************/

//! matrix cofactor
template <typename T, int R, int C> void matCof(T *m1, T const* m2){
    float detValue = 0.0f;
    T subMat[(R - 1) * (C - 1)];
    for(int c = 0; c < C; c++){
        for(int r = 0; r < R; r++){
            matSubMat<T, R, C>(subMat, m2, r, c);
            matDet<T, R - 1, C - 1>(&detValue, subMat);
            if((r + c) % 2){detValue *= -1;}
            m1[r * C + c] = detValue;
        }
    }
}

/************************************************************************
Determinant
************************************************************************/

//! matrix determinant
template <typename T, int R, int C> void matDet(float* retValue, T const* m1){   
    *retValue = 0.0;
    float detValue = 0.0;
    T subMat[(R - 1) * (C - 1)];
    for(int i = 0, k = 1; i < C; i++, k *= -1){
        matSubMat<T, R, C>(subMat, m1, 0, i);
        matDet<T, R - 1, C - 1>(&detValue, subMat);
        *retValue += m1[i] * detValue * k;
    }
}
template <> inline void matDet<float, 2, 2>(float* retValue, float const* m1){
    *retValue = m1[0] * m1[3] - m1[1] * m1[2];
}

/************************************************************************
Inverse
************************************************************************/

//! matrix inverse, M^-1 = (1 / det(M)) * Adj(M)
template <typename T, int R, int C> void matInv(T *m1, T const* m2){
    float detValue = 0.0;
    matDet<T, R, C>(&detValue, m2);
    if(detValue != 0.0f){
        T m3[R * C];
        matAdj<T, R, C>(m3, m2);
        matMulMat<T, R, C>(m1, m3, (1 / detValue));
    }else{
        matIde<T, R, C>(m1);
    }
}