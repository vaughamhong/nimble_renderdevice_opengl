//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_math_vector_h__
#define __nimble_math_vector_h__

//////////////////////////////////////////////////////////////////////////

#include <nimble/core/assert.h>
#include <nimble/math/vectorops.h>

//////////////////////////////////////////////////////////////////////////

namespace nimble{
	namespace math{

		//! templated vector
		template <typename T, int N> 
        class Vector{
		private:

			vector_t<T, N> m_data;

		public:
            
			//! Constructor
			Vector();
			//! copy constructor
			Vector(Vector<T, N-1> const& v1);
			//! copy constructor
			Vector(Vector<T, N> const& v1);
			//! copy constructor
			Vector(Vector<T, N+1> const& v1);
			//! Destructor
			~Vector();

		public:
            
            //! data access
			T operator[](int i) const;
			//! data access
			T& operator[](int i);
			
            //! data access
			T* getData();
			//! data access
			const T* getConstData() const;
            
            //! returns the dimensions of the vector
			int getDimension() const;
            
		public:
            
			bool operator==(Vector<T, N> const& v1) const;
			bool operator!=(Vector<T, N> const& v1) const;

			Vector<T, N> operator=(Vector<T, N-1> const& v1);
			Vector<T, N> operator=(Vector<T, N> const& v1);
			Vector<T, N> operator=(Vector<T, N+1> const& v1);
			Vector<T, N> operator+(Vector<T, N> const& v1) const;
			Vector<T, N> operator+=(Vector<T, N> const& v1);
			Vector<T, N> operator-(Vector<T, N> const& v1) const;
			Vector<T, N> operator-=(Vector<T, N> const& v1);
			Vector<T, N> operator*(T scaler) const;
			Vector<T, N> operator*=(T scaler);
			Vector<T, N> operator/(T scaler) const;
			Vector<T, N> operator/=(T scaler);

			Vector<T, N> operator^(Vector<T, N> const& v1) const;
			Vector<T, N> operator^=(Vector<T, N> const& v1);
            
		public:
            
			// assignment
			void assignment(Vector<T, N-1> const& v1);
			void assignment(Vector<T, N> const& v1);
			void assignment(Vector<T, N+1> const& v1);

			// comparison
			bool equal(Vector<T, N> const& v1) const;
			bool notEqual(Vector<T, N> const& v1) const;

			// arithmetic
			void add(Vector<T, N> const& v1);
			void subtract(Vector<T, N> const& v1);
			void multiply(T scaler);
			void divide(T scaler);

			// misc
			float dot(Vector<T, N> const& v1) const;
			float dot(T const v[N]) const;
			void cross(Vector<T, N> const& v1, Vector<T, N> const& v2);
			float length() const;
			void normalize();

		public:
            
			static Vector<T, N> zero();
            static Vector<T, N> center(Vector<T, N> const& p1, Vector<T, N> const& p2);
            static Vector<T, N> unit();
		};

		//! vector2
		template <typename T = float> class Vector2
        : public Vector<T, 2>{
		public:
            
			Vector2(){(*this)[0] = (T)0; (*this)[1] = (T)0;}
			Vector2(Vector<T, 2-1> const& v1){this->assignment(v1);}
			Vector2(Vector<T, 2> const& v1){this->assignment(v1);}
			Vector2(Vector<T, 2+1> const& v1){this->assignment(v1);}
			Vector2(T x, T y){(*this)[0] = x; (*this)[1] = y;}

		public:
            
			bool operator==(Vector<T, 2> const& v1) const{return this->equal(v1);}
			bool operator!=(Vector<T, 2> const& v1) const{return this->notEqual(v1);}

			Vector<T, 2> operator=(Vector<T, 2-1> const& v1){this->assignment(v1); return Vector<T, 2>(*this);}
			Vector<T, 2> operator=(Vector<T, 2> const& v1){this->assignment(v1); return Vector<T, 2>(*this);}
			Vector<T, 2> operator=(Vector<T, 2+1> const& v1){this->assignment(v1); return Vector<T, 2>(*this);}
			Vector<T, 2> operator+(Vector<T, 2> const& v1){Vector<T, 2> retVect(*this); retVect.add(v1); return retVect;}
			Vector<T, 2> operator+=(Vector<T, 2> const& v1){this->add(v1); return *this;}
			Vector<T, 2> operator-(Vector<T, 2> const& v1){Vector<T, 2> retVect(*this); retVect.subtract(v1); return retVect;}
			Vector<T, 2> operator-=(Vector<T, 2> const& v1){this->subtract(v1); return *this;}
			Vector<T, 2> operator*(T scaler){Vector<T, 2> retVect(*this); retVect.multiply(scaler); return retVect;}
			Vector<T, 2> operator*=(T scaler){this->multiply(scaler); return *this;}
			Vector<T, 2> operator/(T scaler){Vector<T, 2> retVect(*this); retVect.divide(scaler); return retVect;}
			Vector<T, 2> operator/=(T scaler){this->divide(scaler); return *this;}
			Vector<T, 2> operator^(Vector<T, 2> const& v1){Vector<T, 2> retVect; retVect.cross(*this, v1); return retVect;}
			Vector<T, 2> operator^=(Vector<T, 2> const& v1){Vector<T, 2> v2(*this); cross(v2, v1); return *this;}
		};
        
		//! vector3
		template <typename T = float> class Vector3
        : public Vector<T, 3>{
		public:
            
			Vector3(){(*this)[0] = (T)0; (*this)[1] = (T)0; (*this)[2] = (T)0;}
			Vector3(Vector<T, 3-1> const& v1){this->assignment(v1);}
			Vector3(Vector<T, 3> const& v1){this->assignment(v1);}
			Vector3(Vector<T, 3+1> const& v1){this->assignment(v1);}
			Vector3(T x, T y, T z){(*this)[0] = x; (*this)[1] = y; (*this)[2] = z;}

		public:
            
			bool operator==(Vector<T, 3> const& v1) const{return this->equal(v1);}
			bool operator!=(Vector<T, 3> const& v1) const{return this->notEqual(v1);}

			Vector<T, 3> operator=(Vector<T, 3-1> const& v1){this->assignment(v1); return Vector<T, 3>(*this);}
			Vector<T, 3> operator=(Vector<T, 3> const& v1){this->assignment(v1); return Vector<T, 3>(*this);}
			Vector<T, 3> operator=(Vector<T, 3+1> const& v1){this->assignment(v1); return Vector<T, 3>(*this);}
			Vector<T, 3> operator+(Vector<T, 3> const& v1) const{Vector<T, 3> retVect(*this); retVect.add(v1); return retVect;}
			Vector<T, 3> operator+=(Vector<T, 3> const& v1){this->add(v1); return *this;}
			Vector<T, 3> operator-(Vector<T, 3> const& v1) const{Vector<T, 3> retVect(*this); retVect.subtract(v1); return retVect;}
			Vector<T, 3> operator-=(Vector<T, 3> const& v1){this->subtract(v1); return *this;}
			Vector<T, 3> operator*(T scaler) const{Vector<T, 3> retVect(*this); retVect.multiply(scaler); return retVect;}
			Vector<T, 3> operator*=(T scaler){this->multiply(scaler); return *this;}
			Vector<T, 3> operator/(T scaler) const{Vector<T, 3> retVect(*this); retVect.divide(scaler); return retVect;}
			Vector<T, 3> operator/=(T scaler){this->divide(scaler); return *this;}
			Vector<T, 3> operator^(Vector<T, 3> const& v1) const{Vector<T, 3> retVect; retVect.cross(*this, v1); return retVect;}
			Vector<T, 3> operator^=(Vector<T, 3> const& v1){Vector<T, 3> v2(*this); cross(v2, v1); return *this;}
		};

		//! vector4
		template <typename T = float> class Vector4
        : public Vector<T, 4>{
		public:
            
            Vector4(){(*this)[0] = (T)0; (*this)[1] = (T)0; (*this)[2] = (T)0; (*this)[3] = (T)0;}
			Vector4(Vector<T, 4-1> const& v1){this->assignment(v1);}
			Vector4(Vector<T, 4> const& v1){this->assignment(v1);}
			Vector4(Vector<T, 4+1> const& v1){this->assignment(v1);}
			Vector4(T x, T y, T z, T w){(*this)[0] = x; (*this)[1] = y; (*this)[2] = z; (*this)[3] = w;}

		public:
            
			bool operator==(Vector<T, 4> const& v1) const{return this->equal(v1);}
			bool operator!=(Vector<T, 4> const& v1) const{return this->notEqual(v1);}

			Vector<T, 4> operator=(Vector<T, 4-1> const& v1){this->assignment(v1); return Vector<T, 4>(*this);}
			Vector<T, 4> operator=(Vector<T, 4> const& v1){this->assignment(v1); return Vector<T, 4>(*this);}
			Vector<T, 4> operator=(Vector<T, 4+1> const& v1){this->assignment(v1); return Vector<T, 4>(*this);}
			Vector<T, 4> operator+(Vector<T, 4> const& v1) const{Vector<T, 4> retVect(*this); retVect.add(v1); return retVect;}
			Vector<T, 4> operator+=(Vector<T, 4> const& v1){this->add(v1); return *this;}
			Vector<T, 4> operator-(Vector<T, 4> const& v1) const{Vector<T, 4> retVect(*this); retVect.subtract(v1); return retVect;}
			Vector<T, 4> operator-=(Vector<T, 4> const& v1){this->subtract(v1); return *this;}
			Vector<T, 4> operator*(T scaler) const{Vector<T, 4> retVect(*this); retVect.multiply(scaler); return retVect;}
			Vector<T, 4> operator*=(T scaler){this->multiply(scaler); return *this;}
			Vector<T, 4> operator/(T scaler) const{Vector<T, 4> retVect(*this); retVect.divide(scaler); return retVect;}
			Vector<T, 4> operator/=(T scaler){this->divide(scaler); return *this;}
			Vector<T, 4> operator^(Vector<T, 4> const& v1) const{Vector<T, 4> retVect; retVect.cross(*this, v1); return retVect;}
			Vector<T, 4> operator^=(Vector<T, 4> const& v1){Vector<T, 4> v2(*this); cross(v2, v1); return *this;}
		};
        
        //! vector types
        typedef Vector2<float> Vector2f;
        typedef Vector3<float> Vector3f;
        typedef Vector4<float> Vector4f;
        typedef Vector2<int> Vector2i;
        typedef Vector3<int> Vector3i;
        typedef Vector4<int> Vector4i;
        typedef Vector2<short> Vector2s;
        typedef Vector3<short> Vector3s;
        typedef Vector4<short> Vector4s;
        typedef Vector2<unsigned char> Vector2c;
        typedef Vector3<unsigned char> Vector3c;
        typedef Vector4<unsigned char> Vector4c;
                
        // Vector inline
        #include "vector.inline.h"
	};
};

//////////////////////////////////////////////////////////////////////////

#endif

///////////////////////////////////////////////////////////////////////////////