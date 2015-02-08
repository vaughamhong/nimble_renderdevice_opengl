//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_math_quaternion_h__
#define __nimble_math_quaternion_h__

///////////////////////////////////////////////////////////////////////////////

#include <nimble/math/vector.h>
#include <nimble/math/mathops.h>
#include <nimble/core/logger.h>

///////////////////////////////////////////////////////////////////////////////

namespace nimble{
	namespace math{
        template <typename T, int R, int C> class Matrix;
                
        //! templated quaternion
		template <typename T, int N>
        class Quaternion{
        public:
            
            vector_t<T, N> m_data;
            
		public:
            
			//! Constructors
			Quaternion(){}
            //! copy constructor
			Quaternion(Quaternion<T, N> const& q){this->assignment(q);}
			//! construct a quaternion define by the unit vector and angle of rotation about the vector
			Quaternion(math::Vector<T, N - 1> v, float theta){
                
                // rotate around v by theta (radians)
                // q(x, y, z, w)
                // = (sin(theta/2) * v, cos(theta/2))
                // = (sin(theta/2) * v.x, sin(theta/2) * v.y, sin(theta/2) * v.z, cos(theta/2))
                
                // eg. rotating 0 degrees around x axis = (1.0, 0.0, 0.0, 0.0)
                // eg. rotating 90 degrees around x axis = (0.707107, 0.707107, 0.0, 0.0)
                // eg. rotating 180 degrees around x axis = (0.0, 1.0, 0.0, 0.0)
                // eg. rotating 90 degrees around y axis = (0.707107, 0.0, 0.707107, 0.0)
                // eg. rotating 180 degrees around y axis = (0.0, 0.0, 1.0, 0.0)
                
				float halfTheta = theta * 0.5f;
                float cosHalfTheta = math::cosf(halfTheta);
                float sinHalfTheta = math::sinf(halfTheta);
                m_data.m_array[0] = v[0] * sinHalfTheta;
                m_data.m_array[1] = v[1] * sinHalfTheta;
                m_data.m_array[2] = v[2] * sinHalfTheta;
                m_data.m_array[3] = v[3] * cosHalfTheta;
			}
            //! Destructor
            ~Quaternion(){}

        public:
            
			//! data access
			T& operator[](int i){return m_data.m_array[i];}
			//! data access
			T* getData(){return m_data.m_array;}
			//! data access
			const T* getConstData() const{return m_data.m_array;}            
			//! returns the dimensions of the vector
			int getDimension() const{return N;}
            
		public:
            
			bool operator==(Quaternion<T, N> const& v1) const{return this->equal(v1);}
			bool operator!=(Quaternion<T, N> const& v1) const{return this->notEqual(v1);}
            
			Quaternion<T, N> operator=(Quaternion<T, N> const& v1){this->assignment(v1); return Quaternion<T, N>(*this);}
			Quaternion<T, N> operator+(Quaternion<T, N> const& v1) const{Quaternion<T, N> ret(*this); ret.add(v1); return ret;}
			Quaternion<T, N> operator+=(Quaternion<T, N> const& v1){this->add(v1); return *this;}
			Quaternion<T, N> operator-(Quaternion<T, N> const& v1) const{Quaternion<T, N> ret(*this); ret.subtract(v1); return ret;}
			Quaternion<T, N> operator-=(Quaternion<T, N> const& v1){this->subtract(v1); return *this;}
			Quaternion<T, N> operator*(Quaternion<T, N> const& v1) const{return Quaternion<T, N>(multiply(v1));}
			Quaternion<T, N> operator*=(Quaternion<T, N> const& v1){this->add(v1); return *this;}
			Quaternion<T, N> operator*(T scaler) const{Quaternion<T, N> v1(*this); v1.multiply(scaler); return v1;}
			Quaternion<T, N> operator*=(T scaler){this->multiply(scaler); return *this;}
			Quaternion<T, N> operator/(T scaler) const{Quaternion<T, N> v1(*this); v1.divide(scaler); return v1;}
			Quaternion<T, N> operator/=(T scaler){this->divide(scaler); return *this;}
            
        public:
            
			// assignment
			void assignment(Quaternion<T, N-1> const& v1){vecZero<T, N>(getData()); vecCopy<T, N-1>(getData(), v1.getConstData());}
			void assignment(Quaternion<T, N> const& v1){vecCopy<T, N>(getData(), v1.getConstData());}
			void assignment(Quaternion<T, N+1> const& v1){vecCopy<T, N>(getData(), v1.getConstData());}
            
			// comparison
			bool equal(Quaternion<T, N> const& v1) const{return vecEq<T, N>(getConstData(), v1.getConstData());}
			bool notEqual(Quaternion<T, N> const& v1) const{return !equal(v1);}
            
            // arithmetic
			void add(Quaternion<T, N> const& v1){vecAdd<T, N>(getData(), getConstData(), v1.getConstData());}
			void subtract(Quaternion<T, N> const& v1){vecSub<T, N>(getData(), getConstData(), v1.getConstData());}
			void multiply(T scaler){vecMul<T, N>(getData(), scaler);}
			void divide(T scaler){vecDiv<T, N>(getData(), scaler);}

            // misc
			float dot(Quaternion<T, N> const& v1) const{float retValue; vecDot<T, N>(&retValue, getConstData(), v1.getConstData()); return retValue;}
            void normalize(){vecNor<T, N>(getData());}
            float length() const{float retValue; vecLen<float, N>(&retValue, getConstData()); return retValue;}
            
            // multiply
            Quaternion<T, N> multiply(Quaternion<T, N> const& q) const{
                // given r(v, w), s(v, w)
                // q = r * s
                // q = [wr + xri + yrj + zrk] * [ws + xsi + ysj + zsk]
                // q = [wr * ws - vr.vs, ws * vr + wr * vs + vr x vs]
                
				Quaternion<T, N> r;
                T const *pR = m_data.m_array;
                T const *pS = q.m_data.m_array;
                
                // ws * vr + wr * vs + vr x vs
                // ws * vr = (ws * vr.x, ws * vr.y, ws * vr.z)
                // wr * vs = (wr * vs.x, wr * vs.y, wr * vs.z)
                // vr x vs = (vr.y * vs.z - vr.z * vs.y,
                //            vr.z * vs.x - vr.x * vs.z,
                //            vr.x * vs.y - vr.y * vs.x)
                r[0] = pR[0] * pS[3] + pR[3] * pS[0] + pR[1] * pS[2] - pR[2] * pS[1];
                r[1] = pR[1] * pS[3] + pR[3] * pS[1] + pR[2] * pS[0] - pR[0] * pS[2];
                r[2] = pR[2] * pS[3] + pR[3] * pS[2] + pR[0] * pS[1] - pR[1] * pS[0];
                
                // wr * ws - vr.vs
                r[3] = pR[3] * pS[3] - (pR[0] * pS[0] + pR[1] * pS[1] + pR[2] * pS[2]);
                
				return r;
			}
            // inverse
			Quaternion<T, N> inverse() const{
                // q = (w, v)
                // q-1 = (w, -v)
				Quaternion<T, N> r;
                for(int i = 0; i < (N - 2); i++){
                    r[i] = -1.0f * m_data.m_array[i];
                }
                r[N - 1] = m_data.m_array[N - 1];
                return r;
			}
            
        public:
            
			static Quaternion<T, N> zero(){Quaternion<T, N> retValue; vecZero<T, N>(retValue.getData()); return retValue;}
            static Quaternion<T, N> identity(){Quaternion<T, N> retValue; vecZero<T, N>(retValue.getData()); retValue[N - 1] = T(1.0); return retValue;}
            static Quaternion<T, N> slerp(math::Quaternion<T, N> const& a, math::Quaternion<T, N> const& b, float u){
                const float theta = math::acosf(a.dot(b)); //angle between two unit quaternions
                assert(!math::isNaN(theta));
                const float sinTheta = math::sinf(theta);
                if(sinTheta == 0.0f){
                    return a;
                }
                const float t = 1.0f / sinTheta;
                return (a * math::sinf((1.0f - u) * theta) + b * math::sinf(u * theta)) * t;
            }
		};
        
        //! Quaternion2
		template <typename T = float> class Quaternion2: public Quaternion<T, 2>{
		public: //! Constructor / destructor
			Quaternion2(){(*this)[0] = (T)0; (*this)[1] = (T)0;}
			Quaternion2(Quaternion<T, 2> const& v1){this->assignment(v1);}
			Quaternion2(math::Vector<T, 1> v, float theta):Quaternion<T, 2>(v, theta){}
            Quaternion2(T x, T y){(*this)[0] = x; (*this)[1] = y;}
            
		public:
            
			bool operator==(Quaternion<T, 2> const& v1) const{return this->equal(v1);}
			bool operator!=(Quaternion<T, 2> const& v1) const{return this->notEqual(v1);}
            
			Quaternion<T, 2> operator=(Quaternion<T, 2> const& v1){this->assignment(v1); return Quaternion<T, 2>(*this);}
			Quaternion<T, 2> operator+(Quaternion<T, 2> const& v1){Quaternion<T, 2> retVect(*this); retVect.add(v1); return retVect;}
			Quaternion<T, 2> operator+=(Quaternion<T, 2> const& v1){this->add(v1); return *this;}
			Quaternion<T, 2> operator-(Quaternion<T, 2> const& v1){Quaternion<T, 2> retVect(*this); retVect.subtract(v1); return retVect;}
			Quaternion<T, 2> operator-=(Quaternion<T, 2> const& v1){this->subtract(v1); return *this;}
			Quaternion<T, 2> operator*(Quaternion<T, 2> const& v1) const{return Quaternion<T, 2>(this->multiply(v1));}
			Quaternion<T, 2> operator*=(Quaternion<T, 2> const& v1){this->add(v1); return *this;}
			Quaternion<T, 2> operator*(T scaler){Quaternion<T, 2> retVect(*this); retVect.multiply(scaler); return retVect;}
			Quaternion<T, 2> operator*=(T scaler){this->multiply(scaler); return *this;}
			Quaternion<T, 2> operator/(T scaler){Quaternion<T, 2> retVect(*this); retVect.divide(scaler); return retVect;}
			Quaternion<T, 2> operator/=(T scaler){this->divide(scaler); return *this;}
		};
        
        //! Quaternion3
		template <typename T = float> class Quaternion3: public Quaternion<T, 3>{
		public: //! Constructor / destructor
			Quaternion3(){(*this)[0] = (T)0; (*this)[1] = (T)0; (*this)[2] = (T)0;}
			Quaternion3(Quaternion<T, 3> const& v1){this->assignment(v1);}
			Quaternion3(math::Vector<T, 2> v, float theta):Quaternion<T, 3>(v, theta){}
            Quaternion3(T x, T y, T z, T w){(*this)[0] = x; (*this)[1] = y; (*this)[2] = z;}
            
		public:
            
			bool operator==(Quaternion<T, 3> const& v1) const{return this->equal(v1);}
			bool operator!=(Quaternion<T, 3> const& v1) const{return this->notEqual(v1);}
            
			Quaternion<T, 3> operator=(Quaternion<T, 3> const& v1){this->assignment(v1); return Quaternion<T, 3>(*this);}
			Quaternion<T, 3> operator+(Quaternion<T, 3> const& v1){Quaternion<T, 3> retVect(*this); retVect.add(v1); return retVect;}
			Quaternion<T, 3> operator+=(Quaternion<T, 3> const& v1){this->add(v1); return *this;}
			Quaternion<T, 3> operator-(Quaternion<T, 3> const& v1){Quaternion<T, 3> retVect(*this); retVect.subtract(v1); return retVect;}
			Quaternion<T, 3> operator-=(Quaternion<T, 3> const& v1){this->subtract(v1); return *this;}
            Quaternion<T, 3> operator*(Quaternion<T, 3> const& v1) const{return Quaternion<T, 3>(this->multiply(v1));}
			Quaternion<T, 3> operator*=(Quaternion<T, 3> const& v1){this->add(v1); return *this;}
            Quaternion<T, 3> operator*(T scaler){Quaternion<T, 3> retVect(*this); retVect.multiply(scaler); return retVect;}
			Quaternion<T, 3> operator*=(T scaler){this->multiply(scaler); return *this;}
			Quaternion<T, 3> operator/(T scaler){Quaternion<T, 3> retVect(*this); retVect.divide(scaler); return retVect;}
			Quaternion<T, 3> operator/=(T scaler){this->divide(scaler); return *this;}
		};
        
        //! Quaternion4
		template <typename T = float>
        class Quaternion4: public Quaternion<T, 4>{
		public: //! Constructor / destructor
			Quaternion4(){(*this)[0] = (T)0; (*this)[1] = (T)0; (*this)[2] = (T)0; (*this)[3] = (T)0;}
			Quaternion4(Quaternion<T, 4> const& v1){this->assignment(v1);}
			Quaternion4(math::Vector<T, 3> v, float theta):Quaternion<T, 4>(v, theta){}
            Quaternion4(T x, T y, T z, T w){(*this)[0] = x; (*this)[1] = y; (*this)[2] = z; (*this)[3] = w;}
            
		public:
            
			bool operator==(Quaternion<T, 4> const& v1) const{return this->equal(v1);}
			bool operator!=(Quaternion<T, 4> const& v1) const{return this->notEqual(v1);}
            
			Quaternion<T, 4> operator=(Quaternion<T, 4> const& v1){this->assignment(v1); return Quaternion<T, 4>(*this);}
			Quaternion<T, 4> operator+(Quaternion<T, 4> const& v1){Quaternion<T, 4> retVect(*this); retVect.add(v1); return retVect;}
			Quaternion<T, 4> operator+=(Quaternion<T, 4> const& v1){this->add(v1); return *this;}
			Quaternion<T, 4> operator-(Quaternion<T, 4> const& v1){Quaternion<T, 4> retVect(*this); retVect.subtract(v1); return retVect;}
			Quaternion<T, 4> operator-=(Quaternion<T, 4> const& v1){this->subtract(v1); return *this;}
            Quaternion<T, 4> operator*(Quaternion<T, 4> const& v1) const{return Quaternion<T, 4>(this->multiply(v1));}
			Quaternion<T, 4> operator*=(Quaternion<T, 4> const& v1){this->add(v1); return *this;}
            Quaternion<T, 4> operator*(T scaler){Quaternion<T, 4> retVect(*this); retVect.multiply(scaler); return retVect;}
			Quaternion<T, 4> operator*=(T scaler){this->multiply(scaler); return *this;}
			Quaternion<T, 4> operator/(T scaler){Quaternion<T, 4> retVect(*this); retVect.divide(scaler); return retVect;}
			Quaternion<T, 4> operator/=(T scaler){this->divide(scaler); return *this;}
            
        public:
            
            static Quaternion<T, 4> rotationXYZ(float radX, float radY, float radZ){
                Quaternion<T, 4> r;
                double c1 = math::cosf(radY / 2.0f);
                double s1 = math::sinf(radY / 2.0f);
                double c2 = math::cosf(radZ / 2.0f);
                double s2 = math::sinf(radZ / 2.0f);
                double c3 = math::cosf(radX / 2.0f);
                double s3 = math::sinf(radX / 2.0f);
                r.m_data.m_array[0] = c1 * c2 * s3 + s1 * s2 * c3;
                r.m_data.m_array[1] = s1 * c2 * c3 + c1 * s2 * s3;
                r.m_data.m_array[2] = c1 * s2 * c3 - s1 * c2 * s3;
                r.m_data.m_array[3] = c1 * c2 * c3 - s1 * s2 * s3;
                return r;
			}
            static Quaternion<T, 4> rotation(math::Matrix<T, 4, 4> const &transform);
            static Quaternion<T, 4> rotation(math::Vector<T, 3> const &forward);
		};
        
        //! vector types
        typedef Quaternion2<float> Quaternion2f;
        typedef Quaternion3<float> Quaternion3f;
        typedef Quaternion4<float> Quaternion4f;
	};
};

#include <nimble/math/matrix.h>
namespace nimble{
    namespace math{
        
        // calculates a quaternion from a rotation matrix
        template <typename T>
        math::Quaternion<T, 4> Quaternion4<T>::rotation(math::Matrix<T, 4, 4> const &transform){
#if defined(NIMBLE_DEBUG)
            const float kEpsilon = 0.0001f;
            float det = math::abs(transform.determinant());
            if(math::abs(1.0f - det) > kEpsilon){
                core::logger_warning("math", "Failed to construct quaternion from rotation matrix - matrix determinanet is not (+/-)1");
                return Quaternion<T, 4>();
            }
#endif
            Quaternion<T, 4> r;
            
            float tr = transform.get(0, 0) + transform.get(1, 1) + transform.get(2, 2);
            if (tr > 0) {
                float S = sqrt(tr + 1.0) * 2;
                r.m_data.m_array[3] = 0.25 * S;
                r.m_data.m_array[0] = (transform.get(2, 1) - transform.get(1, 2)) / S;
                r.m_data.m_array[1] = (transform.get(0, 2) - transform.get(2, 0)) / S;
                r.m_data.m_array[2] = (transform.get(1, 0) - transform.get(0, 1)) / S;
            } else if ((transform.get(0, 0) > transform.get(1, 1))&(transform.get(0, 0) > transform.get(2, 2))) {
                float S = sqrt(1.0 + transform.get(0, 0) - transform.get(1, 1) - transform.get(2, 2)) * 2;
                r.m_data.m_array[3] = (transform.get(2, 1) - transform.get(1, 2)) / S;
                r.m_data.m_array[0] = 0.25 * S;
                r.m_data.m_array[1] = (transform.get(0, 1) + transform.get(1, 0)) / S;
                r.m_data.m_array[2] = (transform.get(0, 2) + transform.get(2, 0)) / S;
            } else if (transform.get(1, 1) > transform.get(2, 2)) {
                float S = sqrt(1.0 + transform.get(1, 1) - transform.get(0, 0) - transform.get(2, 2)) * 2;
                r.m_data.m_array[3] = (transform.get(0, 2) - transform.get(2, 0)) / S;
                r.m_data.m_array[0] = (transform.get(0, 1) + transform.get(1, 0)) / S;
                r.m_data.m_array[1] = 0.25 * S;
                r.m_data.m_array[2] = (transform.get(1, 2) + transform.get(2, 1)) / S;
            } else { 
                float S = sqrt(1.0 + transform.get(2, 2) - transform.get(0, 0) - transform.get(1, 1)) * 2;
                r.m_data.m_array[3] = (transform.get(1, 0) - transform.get(0, 1)) / S;
                r.m_data.m_array[0] = (transform.get(0, 2) + transform.get(2, 0)) / S;
                r.m_data.m_array[1] = (transform.get(1, 2) + transform.get(2, 1)) / S;
                r.m_data.m_array[2] = 0.25 * S;
            }
            return r;
        }
        
        // calculates a quaternion from a forward vector
        template <typename T>
        math::Quaternion<T, 4> Quaternion4<T>::rotation(math::Vector<T, 3> const &forward){
            // create change of basis matrix with left, up, forward vectors
            math::Vector3f upVector(0.0f, 1.0f, 0.0f);
            math::Vector3f leftVector = upVector ^ forward;
            upVector = forward ^ leftVector;
            math::Matrix<T, 4, 4> matrix = math::Matrix<T, 4, 4>::identity();
            matrix.setColumn(0, leftVector);
            matrix.setColumn(1, upVector);
            matrix.setColumn(2, forward);
            return math::Quaternion4<T>::rotation(matrix);
        }
    };
};
/*
 //! extract the 3x3 portion of the matrix to generate the quaternion
 Quaternion(math::Matrix4x4<> m){
 float tr, s;
 
 tr = m[0][0] + m[1][1] + m[2][2];
 if(tr >= 0){
 s = math::fastsqrt(tr + 1);
 w = 0.5f * s;
 s = 0.5f / s;
 x = (m[2][1] - m[1][2]) * s;
 y = (m[0][2] - m[2][0]) * s;
 z = (m[1][0] - m[0][1]) * s;
 }else{
 if(m[1][1] > m[0][0]){
 s = sqrtf((m[1][1] - (m[2][2] + m[0][0])) + 1);
 y = 0.5f * s;
 s = 0.5f / s;
 z = (m[1][2] + m[2][1]) * s;
 x = (m[0][1] + m[1][0]) * s;
 w = (m[0][2] - m[2][0]) * s;
 }else if(m[2][2] > m[1][1]){
 s = sqrtf((m[2][2] - (m[0][0] + m[1][1])) + 1);
 z = 0.5f * s;
 s = 0.5f / s;
 x = (m[2][0] + m[0][2]) * s;
 y = (m[1][2] + m[2][1]) * s;
 w = (m[1][0] - m[0][1]) * s;
 }else{
 s = sqrtf((m[0][0] - (m[1][1] + m[2][2])) + 1);
 x = 0.5f * s;
 s = 0.5f / s;
 y = (m[0][1] + m[1][0]) * s;
 z = (m[2][0] + m[0][2]) * s;
 w = (m[2][1] - m[1][2]) * s;
 }
 }
 }
 */

///////////////////////////////////////////////////////////////////////////////

#endif

///////////////////////////////////////////////////////////////////////////////