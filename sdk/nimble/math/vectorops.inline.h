//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

/************************************************************************
Addition
************************************************************************/

// type T, N elements, v1 = v2 + v3 (unrolls operation)
template <typename T, int N> inline void vecAddUnrolled(T* v1, T const* v2, T const* v3){
	VectorOps<T, N>::add(v1, v2, v3);
}
// type T, N elements, v1 = v2 + v3
template <typename T, int N> inline void vecAdd(T* v1, T const* v2, T const* v3){
	for(int i = 0; i < N; ++i){
		v1[i] = v2[i] + v3[i];
	}
}
// type T, N elements, v1 = v2 + v3 (array)
template <typename T, int N> inline void vecAdd(T* v1, T const* v2, T const* v3, unsigned int size){
	for(unsigned int i = 0; i < size; ++i){
		vecAddUnrolled<T, N>(
			&v1[i * sizeof(T) * N], 
			&v2[i * sizeof(T) * N], 
			&v3[i * sizeof(T) * N]);
	}
}

/************************************************************************
Subtraction
************************************************************************/

// type T, N elements, v1 = v2 - v3 (unrolls operation)
template <typename T, int N> inline void vecSubUnrolled(T* v1, T const* v2, T const* v3){
	VectorOps<T, N>::sub(v1, v2, v3);
}
// type T, N elements, v1 = v2 - v3
template <typename T, int N> inline void vecSub(T* v1, T const* v2, T const* v3){
	for(int i = 0; i < N; ++i){
		v1[i] = v2[i] - v3[i];
	}
}
// type T, N elements, v1 = v2 - v3 (array)
template <typename T, int N> inline void vecSub(T* v1, T const* v2, T const* v3, unsigned int size){
	for(unsigned int i = 0; i < size; ++i){
		vecSubUnrolled<T, N>(
			&v1[i * sizeof(T) * N], 
			&v2[i * sizeof(T) * N], 
			&v3[i * sizeof(T) * N]);
	}
}

/************************************************************************
Min / max
************************************************************************/

// type T, N elements, v1 = min(v2, m3)
template <typename T, int N> void vecMin(T* v1, T const* v2, T const* v3){
    for(int i = 0; i < N; ++i){
        if(v2[i] < v3[i]){
            v1[i] = v2[i];
        }else{
            v1[i] = v3[i];
        }
    }
}
// type T, N elements, v1 = max(v2, m3)
template <typename T, int N> void vecMax(T* v1, T const* v2, T const* v3){
    for(int i = 0; i < N; ++i){
        if(v2[i] > v3[i]){
            v1[i] = v2[i];
        }else{
            v1[i] = v3[i];
        }
    }
}

/************************************************************************
Multiplication
************************************************************************/

// type T, N elements, v1 = v2 * v3 (unrolls operation)
template <typename T, int N> inline void vecMulUnrolled(T* v1, T const* v2, T const* v3){
	VectorOps<T, N>::mul(v1, v2, v3);
}
// type T, N elements, v1 = v2 * v3
template <typename T, int N> inline void vecMul(T* v1, T const* v2, T const* v3){
	for(int i = 0; i < N; ++i){
		v1[i] = v2[i] * v3[i];
	}
}
// type T, N elements, v1 = v2 * v3 (array)
template <typename T, int N> inline void vecMul(T* v1, T const* v2, T const* v3, unsigned int size){
	for(unsigned int i = 0; i < size; ++i){
		vecMulUnrolled<T, N>(
			&v1[i * sizeof(T) * N], 
			&v2[i * sizeof(T) * N], 
			&v3[i * sizeof(T) * N]);
	}
}

/************************************************************************
Multiplication
************************************************************************/

// type T, N elements, v1 = v2 * v3 (unrolls operation)
template <typename T, int N> inline void vecMulUnrolled(T* v1, T const* v2, T value){
	VectorOps<T, N>::mul(v1, v2, value);
}
// type T, N elements, v1 = v2 * v3
template <typename T, int N> inline void vecMul(T* v1, T const* v2, T value){
	for(int i = 0; i < N; ++i){
		v1[i] = v2[i] * value;
	}
}
// type T, N elements, v1 = v2 * v3
template <typename T, int N> inline void vecMul(T* v1, T value){
	for(int i = 0; i < N; ++i){
		v1[i] *= value;
	}
}
// type T, N elements, v1 = v2 * v3 (array)
template <typename T, int N> inline void vecMul(T* v1, T const* v2, T value, unsigned int size){
	for(unsigned int i = 0; i < size; ++i){
		vecMulUnrolled<T, N>(
			&v1[i * sizeof(T) * N], 
			&v2[i * sizeof(T) * N], 
			value);
	}
}

/************************************************************************
Division
************************************************************************/

// type T, N elements, v1 = v2 / v3 (unrolls operation)
template <typename T, int N> inline void vecDivUnrolled(T* v1, T const* v2, T const* v3){
	VectorOps<T, N>::div(v1, v2, v3);
}
// type T, N elements, v1 = v2 / v3
template <typename T, int N> inline void vecDiv(T* v1, T const* v2, T const* v3){
	for(int i = 0; i < N; ++i){
		v1[i] = v2[i] / v3[i];
	}
}
// type T, N elements, v1 = v2 / v3 (array)
template <typename T, int N> inline void vecDiv(T* v1, T const* v2, T const* v3, unsigned int size){
	for(unsigned int i = 0; i < size; ++i){
		vecDivUnrolled<T, N>(
			&v1[i * sizeof(T) * N], 
			&v2[i * sizeof(T) * N], 
			&v3[i * sizeof(T) * N]);
	}
}

/************************************************************************
Division
************************************************************************/

// type T, N elements, v1 = v2 / value (unrolls operation)
template <typename T, int N> inline void vecDivUnrolled(T* v1, T const* v2, T value){
	VectorOps<T, N>::div(v1, v2, value);
}
// type T, N elements, v1 = v2 / value
template <typename T, int N> inline void vecDiv(T* v1, T const* v2, T value){
	for(int i = 0; i < N; ++i){
		v1[i] = v2[i] / value;
	}
}
// type T, N elements, v1 = v2 / value (array)
template <typename T, int N> inline void vecDiv(T* v1, T const* v2, T value, unsigned int size){
	for(unsigned int i = 0; i < size; ++i){
		vecDivUnrolled<T, N>(
			&v1[i * sizeof(T) * N], 
			&v2[i * sizeof(T) * N], 
			value);
	}
}
// type T, N elements, v1 /= value (unrolls operation)
template <typename T, int N> inline void vecDivUnrolled(T* v1, T value){
	vecDivUnrolled<T, N>(v1, v1, value);
}
// type T, N elements, v1 = v2 / value
template <typename T, int N> inline void vecDiv(T* v1, T value){
	vecDiv<T, N>(v1, v1, value);
}

/************************************************************************
Center
************************************************************************/

template <typename T, int N> inline void vecCenterUnrolled(T* v1, T const* v2, T const* v3){
	VectorOps<T, N>::center(v1, v2, v3);
}

template <typename T, int N> inline void vecCenter(T* v1, T const* v2, T const* v3){
	for(int i = 0; i < N; ++i){
		v1[i] = v2[i] + (v3[i] - v2[i]) / 2;
	}
}

/************************************************************************
Copy
************************************************************************/

// type T, N elements, v1 = v2 (unrolls operation)
template <typename T, int N> inline void vecCopyUnrolled(T* v1, T const* v2){
	VectorOps<T, N>::copy(v1, v2);
}
// type T, N elements, v1 = v2
template <typename T, int N> inline void vecCopy(T* v1, T const* v2){
	memcpy(v1, v2, sizeof(T) * N);
}
// type T, N elements, v1 = v2 (array)
template <typename T, int N> inline void vecCopy(T* v1, T const* v2, unsigned int size){
	for(unsigned int i = 0; i < size; ++i){
		vecCopyUnrolled<T, N>(
			&v1[i * sizeof(T) * N], 
			&v2[i * sizeof(T) * N]);
	}
}

/************************************************************************
Copy
************************************************************************/

// type T, N elements, v1 = v2 (unrolls operation)
template <typename T, int N> inline void vecCopyUnrolled(T* v1, T value){
	VectorOps<T, N>::copy(v1, value);
}
// type T, N elements, v1 = v2
template <typename T, int N> inline void vecCopy(T* v1, T value){
	for(int i = 0; i < N; ++i){
		v1[i] = value;
	}
}
// type T, N elements, v1 = v2 (array)
template <typename T, int N> inline void vecCopy(T* v1, T value, unsigned int size){
	for(unsigned int i = 0; i < size; ++i){
		vecCopyUnrolled<T, N>(
			&v1[i * sizeof(T) * N], 
			value);
	}
}

/************************************************************************
Dot
************************************************************************/

// type T, N elements, v1 dot v2 (unrolls operation)
template <typename T, int N> inline void vecDotUnrolled(float* retValue, T const* v1, T const* v2){
	*retValue = VectorOps<T, N>::dot(v1, v2);
}
// type T, N elements, v1 dot v2
template <typename T, int N> inline void vecDot(float* retValue, T const* v1, T const* v2){
	*retValue = 0.0f;
	for(int i = 0; i < N; ++i){
		*retValue += (float)v1[i] * v2[i];
	}
}
// type T, N elements, v1 dot v2 (array)
template <typename T, int N> inline void vecDot(float* retValue, T const* v1, T const* v2, unsigned int size){
	for(unsigned int i = 0; i < size; ++i){
		vecDotUnrolled<T, N>(
			&retValue[i], 
			&v1[i * sizeof(T) * N],
			&v2[i * sizeof(T) * N]);
	}
}

/************************************************************************
Length
************************************************************************/

// type T, N elements, v1 length (unrolls operation)
template <typename T, int N> inline void vecLenUnrolled(float* retValue, T const* v1){
	*retValue = sqrtf(VectorOps<T, N>::dot(v1, v1));
}
// type T, N elements, v1 length
template <typename T, int N> inline void vecLen(float* retValue, T const* v1){
	*retValue = 0.0f;
	for(int i = 0; i < N; ++i){
		*retValue += (float)v1[i] * v1[i];
	}
	
	if(*retValue > 0.0f){
		*retValue = sqrtf(*retValue);
	}else{
		*retValue = -1.0f;
	}
}
// type T, N elements, v1 length (array)
template <typename T, int N> inline void vecLen(float* retValue, T const* v1, unsigned int size){
	for(unsigned int i = 0; i < size; ++i){
		vecLenUnrolled<T, N>(
			&retValue[i], 
			&v1[i * sizeof(T) * N]);
	}
}

/************************************************************************
Normalize
************************************************************************/

// type T, N elements, v1 normalize (unrolls operation)
template <typename T, int N> inline void vecNorUnrolled(T* v1){
	float length = 1.0f;
	vecLenUnrolled<T, N>(&length, v1);
	vecDivUnrolled<T, N>(v1, static_cast<T>(length));
}
// type T, N elements, v1 normalize
template <typename T, int N> inline void vecNor(T* v1){
	float length = 1.0f;
	vecLen<T, N>(&length, v1);
	vecDiv<T, N>(v1, static_cast<T>(length));
}
// type T, N elements, v1 normalize (array)
template <typename T, int N> inline void vecNor(T* v1, unsigned int size){
	for(unsigned int i = 0; i < size; ++i){
		vecNorUnrolled<T, N>(
			&v1[i * sizeof(T) * N]);
	}
}

/************************************************************************
Equal
************************************************************************/

// type T, N elements, v1 == v2 (unrolls operation)
template <typename T, int N> inline bool vecEqUnrolled(T* v1, T const* v2){
	return VectorOps<T, N>::eq(v1, v2);
}

// type T, N elements, v1 == v2
template <typename T, int N> inline bool vecEq(T const* v1, T const* v2){
	for(unsigned int i = 0; i < N; ++i){
		if(v1[i] != v2[i]){return false;}
	}
	return true;
}

/************************************************************************
Zero
************************************************************************/

// type T, N elements, v1 = 0 (unrolls operation)
template <typename T, int N> inline void vecZeroUnrolled(T* v1){
	return VectorOps<T, N>::zero(v1);
}

// type T, N elements, v1 = 0
template <typename T, int N> inline void vecZero(T* v1){
	for(unsigned int i = 0; i < N; ++i){
		v1[i] = static_cast<T>(0);
	}
}

// type T, N elements, v1 = 0 (array)
template <typename T, int N> inline void vecZero(T* v1, unsigned int size){
	for(unsigned int i = 0; i < size; ++i){
		vecZeroUnrolled<T, N>(
			&v1[i * sizeof(T) * N]);
	}
}

/************************************************************************
Cross product
************************************************************************/

template <typename T, int N> inline void vecCrs(T* v1, T const* v2, T const* v3){
	if(N == 3){
		v1[0] = v2[1] * v3[2] - v2[2] * v3[1];
		v1[1] = v2[2] * v3[0] - v2[0] * v3[2];
		v1[2] = v2[0] * v3[1] - v2[1] * v3[0];
	}
}

/************************************************************************
Set / Unit values
************************************************************************/

template <typename T, int N> void vecSet(T* v1, T value){
    for(unsigned int i = 0; i < N; ++i){
        v1[i] = static_cast<T>(value);
    }
}
template <typename T, int N> void vecUnit(T* v1){
    vecSet<T, N>(v1, 1);
}