//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_math_matrix_h__
#define __nimble_math_matrix_h__

///////////////////////////////////////////////////////////////////////////////

#include <nimble/math/matrixops.h>
#include <nimble/math/vector.h>
#include <nimble/math/quaternion.h>
#include <nimble/math/ray.h>

///////////////////////////////////////////////////////////////////////////////

namespace nimble{
	namespace math{
        
		//! templated matrix
		template <typename T, int R, int C>
        class Matrix{
		private:
            
            typedef Matrix<T, R, C> MatrixType;
			vector_t<T, R * C> m_data;

		public:

			//! Constructor
			Matrix(){}
			//! Constructor
			Matrix(MatrixType const& m1){assignment(m1);}
			//! Constructor
			Matrix(T const m1[R*C]){assignment(m1);}
			//! Constructor
			Matrix(T const m1[][C]){assignment(m1);}
			//! copy destructor
			~Matrix(){}

		public:

			//! data access
			T& operator[](int i){return m_data.m_array[i * R];}
            
			//! data access
			T* getBuffer(){return m_data.m_array;}
			//! data access
			const T* getConstBuffer() const{return m_data.m_array;}
            
			//! data access
			const T& get(int i, int j) const{return m_data.m_array[i * C + j];}
			//! data access
			void set(int i, int j, T const &val){m_data.m_array[i * C + j] = val;}

			//! column access
			void setColumn(unsigned int j, Vector<T, R> const& v1){matSetCol<T, R, C>(getBuffer(), j, v1.getConstData());}
			Vector<T, R> getColumn(unsigned int j) const{Vector<T, R> v1; matGetCol<T, R, C>(v1.getData(), j, getConstBuffer()); return v1;}
			//! row access
			void setRow(unsigned int i, Vector<T, C> const& v1){matSetRow<T, R, C>(getBuffer(), i, v1.getConstData());}
			Vector<T, C> getRow(unsigned int i) const{Vector<T, C> v1; matGetRow<T, R, C>(v1.getData(), i, getConstBuffer()); return v1;}

		public:
            
			bool operator==(MatrixType const& point) const{return equals(point);}
			bool operator!=(MatrixType const& point) const{return notEquals(point);}

			MatrixType operator=(MatrixType const& m1){assignment(m1); return MatrixType(*this);}
			MatrixType operator+(MatrixType const& m1) const{MatrixType retMat(*this); retMat.add(m1); return retMat;}
			MatrixType operator+=(MatrixType const& m1){add(m1); return MatrixType(*this);}
			MatrixType operator-(MatrixType const& m1) const{MatrixType retMat(*this); retMat.subtract(m1); return retMat;}
			MatrixType operator-=(MatrixType const& m1){subtract(m1); return MatrixType(*this);}
			MatrixType operator*(T scaler) const{MatrixType retMat(*this); retMat.multiply(scaler); return retMat;}
			MatrixType operator*=(T scaler){multiply(scaler); return MatrixType(*this);}
			MatrixType operator*(MatrixType const& m1) const{MatrixType retMat(*this); retMat.multiply(*this, m1); return retMat;}
			MatrixType operator*=(MatrixType const& m1){MatrixType m2(*this); multiply(m2, m1); return *this;}
			MatrixType operator/(T scaler) const{MatrixType retMat(*this); retMat.divide(scaler); return retMat;}
			MatrixType operator/=(T scaler){divide(scaler); return MatrixType(*this);}

			Vector<T, C> operator*(Vector<T, C> const& v1){return multiply(v1);}
			Ray<T, C> operator*(Ray<T, C> const& r1){return multiply(r1);}

		public:
            
			// assignment
			void assignment(MatrixType const& m1){
                vecCopy<T, R * C>(getBuffer(), m1.getConstBuffer());
            }
            void assignment(T const m1[R*C]){
				for(int i = 0; i < R; i++){
					for(int j = 0; j < C; j++){
						m_data.m_array[i * C + j] = m1[i * C + j];
					}
				}
			}
			void assignment(T const m1[][C]){
				for(int i = 0; i < R; i++){
					for(int j = 0; j < C; j++){
						m_data.m_array[i * C + j] = m1[i][j];
					}
				}
			}

			// comparison
			bool equals(MatrixType const& m1) const{return vecEq<T, R * C>(getConstBuffer(), m1.m_data.m_array);}
			bool notEquals(MatrixType const& m1) const{return !equals(m1);}

			// arithmetic
			void add(MatrixType const& m1){vecAdd<T, R * C>(getBuffer(), getConstBuffer(), m1.getConstData());}
			void subtract(MatrixType const& m1){vecSub<T, R * C>(getBuffer(), m1.getConstData());}
			void multiply(MatrixType const& m1, MatrixType const& m2){matMulMat<T, R, C>(getBuffer(), m1.getConstBuffer(), m2.getConstBuffer());}
			void multiply(T scaler){vecMul<T, R * C>(getBuffer(), scaler);}
			Vector<T, C> multiply(Vector<T, C> const& p1) const{Vector<T, C> retVec; matMulVec<T, R, C>(retVec.getData(), getConstBuffer(), p1.getConstData()); return retVec;}
			Ray<T, C> multiply(Ray<T, C> const& r1) const{Ray<T, C> retRay; Vector<T, C> p1 = r1.getPosition(); Vector<T, C> v1 = r1.getDirection(); retRay.setPosition(*this * p1); retRay.setDirection(*this * v1); return retRay;}
			void divide(T scaler){vecDiv<T, R * C>(getBuffer(), scaler);}

            // transpose
			MatrixType transpose(){matTpo<T, R, C>(getBuffer()); return *this;}
            // sub matrix
            Matrix<T, R-1, C-1> subMatrix(unsigned int i, unsigned int j) const{Matrix<T, R-1, C-1> retMat; matSubMat<T, R, C>(retMat.getBuffer(), getConstBuffer(), i, j); return retMat;}
            // cofactor matrix
            MatrixType cofactor() const{MatrixType retMat; matCof<T, R, C>(retMat.getBuffer(), getConstBuffer()); return retMat;}
            // adjugate matrix
            MatrixType adjugate() const{MatrixType retMat; matAdj<T, R, C>(retMat.getBuffer(), getConstBuffer()); return retMat;}
            // inverse matrix
            MatrixType inverse() const{MatrixType retMat; matInv<T, R, C>(retMat.getBuffer(), getConstBuffer()); return retMat;}
            // determinant
            float determinant() const{float retValue; matDet<T, R, C>(&retValue, getConstBuffer()); return retValue;}
			
		public:

            // zero matrix
			static MatrixType zero(){MatrixType retMat; vecZero<T, R * C>(retMat.getBuffer()); return retMat;}
            // identity matrix
			static MatrixType identity(){MatrixType retMat; matIde<T, R, C>(retMat.getBuffer()); return retMat;}
            // translation matrix
			static MatrixType translationMatrix(Vector<T, C> const& v1){
                MatrixType retMat = MatrixType::identity(); 
                matSetCol<T, R, C>(retMat.getBuffer(), C - 1, v1.getConstData()); 
                retMat.set(R - 1, C - 1, (T)1); 
                return retMat;
            }
            // translation matrix
            static MatrixType translationMatrix(Vector<T, C - 1> const& v1){
                return MatrixType::translationMatrix(Vector<T, C>(v1));
            }
            // scale matrix
			static MatrixType scaleMatrix(Vector<T, C - 1> const& v1){
                MatrixType retMat = MatrixType::identity(); 
                matSetDiag<T, R, C>(retMat.getBuffer(), v1.getConstData()); 
                retMat.set(R - 1, C - 1, (T)1); 
                return retMat;
            }
		};
        
        //! matrix4x4
		template <typename T = float>
        class Matrix3x3
        : public Matrix<T, 3, 3>{
        public:
            
			Matrix3x3(){}
			Matrix3x3(T const m1[][3])
			:Matrix<T, 3, 3>(m1){
			}
			Matrix3x3(Matrix<T, 3, 3> const& m1){this->assignment(m1);}
            Matrix3x3(Matrix<T, 4, 4> const& m1){
                this->set(0, 0, m1.get(0, 0)); this->set(0, 1, m1.get(0, 1)); this->set(0, 2, m1.get(0, 2));
                this->set(1, 0, m1.get(1, 0)); this->set(1, 1, m1.get(1, 1)); this->set(1, 2, m1.get(1, 2));
                this->set(2, 0, m1.get(2, 0)); this->set(2, 1, m1.get(2, 1)); this->set(2, 2, m1.get(2, 2));
            }
            
		public:
            
			bool operator==(Matrix<T, 3, 3> const& point) const{return this->equals(point);}
			bool operator!=(Matrix<T, 3, 3> const& point) const{return this->notEquals(point);}
            
			Matrix<T, 3, 3> operator=(Matrix<T, 3, 3> const& m1){this->assignment(m1); return Matrix<T, 3, 3>(*this);}
			Matrix<T, 3, 3> operator+(Matrix<T, 3, 3> const& m1) const{Matrix<T, 3, 3> retMat(*this); retMat.add(m1); return retMat;}
			Matrix<T, 3, 3> operator+=(Matrix<T, 3, 3> const& m1){add(m1); return Matrix<T, 3, 3>(*this);}
			Matrix<T, 3, 3> operator-(Matrix<T, 3, 3> const& m1) const{Matrix<T, 3, 3> retMat(*this); retMat.subtract(m1); return retMat;}
			Matrix<T, 3, 3> operator-=(Matrix<T, 3, 3> const& m1){subtract(m1); return Matrix<T, 3, 3>(*this);}
			Matrix<T, 3, 3> operator*(T scaler) const{Matrix<T, 3, 3> retMat(*this); retMat.multiply(scaler); return retMat;}
			Matrix<T, 3, 3> operator*=(T scaler){multiply(scaler); return Matrix<T, 3, 3>(*this);}
			Matrix<T, 3, 3> operator*(Matrix<T, 3, 3> const& m1) const{Matrix<T, 3, 3> retMat(*this); retMat.multiply(*this, m1); return retMat;}
			Matrix<T, 3, 3> operator*=(Matrix<T, 3, 3> const& m1){Matrix<T, 3, 3> m2(*this); this->multiply(m2, m1); return *this;}
			Matrix<T, 3, 3> operator/(T scaler) const{Matrix<T, 3, 3> retMat(*this); retMat.divide(scaler); return retMat;}
			Matrix<T, 3, 3> operator/=(T scaler){divide(scaler); return Matrix<T, 3, 3>(*this);}
            
			Vector<T, 3> operator*(Vector<T, 3> const& v1) const {return Matrix<T, 3, 3>::multiply(v1);}
			Ray<T, 3> operator*(Ray<T, 3> const& r1) const {return Matrix<T, 3, 3>::multiply(r1);}
            
		public:
            
			// make this a rotation matrix
			static Matrix<T, 3, 3> rotationMatrix(float rad){
				Matrix<T, 3, 3> retMat;
				retMat.setRow(0, Vector3<float>(cosf(rad),      sinf(rad),				0.0f));
				retMat.setRow(1, Vector3<float>(-sinf(rad),		cosf(rad),				0.0f));
				retMat.setRow(2, Vector3<float>(0.0f,			0.0f,                   1.0f));
				return retMat;
			}
			// make this a translation matrix
			static Matrix<T, 3, 3> translationMatrix(float x, float y){
				Matrix<T, 3, 3> retMat = Matrix<T, 3, 3>::identity();
				retMat = Matrix<T, 3, 3>::translationMatrix(Vector3<T>(x, y, 1.0f));
				return retMat;
			}
            
			// make this a scaling matrix
			static Matrix<T, 3, 3> scaleMatrix(float f){
				Matrix<T, 3, 3> retMat = Matrix<T, 3, 3>::identity();
				retMat = Matrix<T, 3, 3>::scaleMatrix(Vector3<T>(f, f, f));
				return retMat;
			}
			static Matrix<T, 3, 3> scaleMatrix(float x, float y, float w){
				Matrix<T, 3, 3> retMat = Matrix<T, 3, 3>::identity();
				retMat = Matrix<T, 3, 3>::scaleMatrix(Vector3<T>(x, y, w));
				return retMat;
			}
        };

		//! matrix4x4
		template <typename T = float>
        class Matrix4x4
        : public Matrix<T, 4, 4>{
        public:
            
			Matrix4x4(){}
			Matrix4x4(T const m1[16])
            :Matrix<T, 4, 4>(m1){
            }
			Matrix4x4(T const m1[][4])
			:Matrix<T, 4, 4>(m1){
			}
			Matrix4x4(Matrix<T, 4, 4> const& m1){this->assignment(m1);}

		public:
            
			bool operator==(Matrix<T, 4, 4> const& point) const{return this->equals(point);}
			bool operator!=(Matrix<T, 4, 4> const& point) const{return this->notEquals(point);}

			Matrix<T, 4, 4> operator=(Matrix<T, 4, 4> const& m1){this->assignment(m1); return Matrix<T, 4, 4>(*this);}
			Matrix<T, 4, 4> operator+(Matrix<T, 4, 4> const& m1) const{Matrix<T, 4, 4> retMat(*this); retMat.add(m1); return retMat;}
			Matrix<T, 4, 4> operator+=(Matrix<T, 4, 4> const& m1){add(m1); return Matrix<T, 4, 4>(*this);}
			Matrix<T, 4, 4> operator-(Matrix<T, 4, 4> const& m1) const{Matrix<T, 4, 4> retMat(*this); retMat.subtract(m1); return retMat;}
			Matrix<T, 4, 4> operator-=(Matrix<T, 4, 4> const& m1){subtract(m1); return Matrix<T, 4, 4>(*this);}
			Matrix<T, 4, 4> operator*(T scaler) const{Matrix<T, 4, 4> retMat(*this); retMat.multiply(scaler); return retMat;}
			Matrix<T, 4, 4> operator*=(T scaler){multiply(scaler); return Matrix<T, 4, 4>(*this);}
			Matrix<T, 4, 4> operator*(Matrix<T, 4, 4> const& m1) const{Matrix<T, 4, 4> retMat(*this); retMat.multiply(*this, m1); return retMat;}
			Matrix<T, 4, 4> operator*=(Matrix<T, 4, 4> const& m1){Matrix<T, 4, 4> m2(*this); this->multiply(m2, m1); return *this;}
			Matrix<T, 4, 4> operator/(T scaler) const{Matrix<T, 4, 4> retMat(*this); retMat.divide(scaler); return retMat;}
			Matrix<T, 4, 4> operator/=(T scaler){divide(scaler); return Matrix<T, 4, 4>(*this);}

			Vector<T, 4> operator*(Vector<T, 4> const& v1) const {return Matrix<T, 4, 4>::multiply(v1);}
			Ray<T, 4> operator*(Ray<T, 4> const& r1) const {return Matrix<T, 4, 4>::multiply(r1);}

		public:
            
			// make this a rotation matrix
			static Matrix<T, 4, 4> rotationXMatrix(float rad){
				Matrix<T, 4, 4> retMat;
				retMat.setRow(0, Vector4<float>(1.0f,			0.0f,               0.0f,				0.0f));
				retMat.setRow(1, Vector4<float>(0.0f,			cosf(rad),			-sinf(rad),			0.0f));
				retMat.setRow(2, Vector4<float>(0.0f,			sinf(rad),			cosf(rad),			0.0f));
				retMat.setRow(3, Vector4<float>(0.0f,			0.0f,				0.0f,				1.0f));
				return retMat;
			}
			static Matrix<T, 4, 4> rotationYMatrix(float rad){
				Matrix<T, 4, 4> retMat;
				retMat.setRow(0, Vector4<float>(cosf(rad),		0.0f,               sinf(rad),			0.0f));
				retMat.setRow(1, Vector4<float>(0.0f,			1.0f,               0.0f,				0.0f));
				retMat.setRow(2, Vector4<float>(-sinf(rad),     0.0f,               cosf(rad),			0.0f));
				retMat.setRow(3, Vector4<float>(0.0f,			0.0f,               0.0f,				1.0f));
				return retMat;
			}
			static Matrix<T, 4, 4> rotationZMatrix(float rad){
				Matrix<T, 4, 4> retMat;
				retMat.setRow(0, Vector4<float>(cosf(rad),		-sinf(rad),			0.0f,               0.0f));
				retMat.setRow(1, Vector4<float>(sinf(rad),		cosf(rad),			0.0f,               0.0f));
				retMat.setRow(2, Vector4<float>(0.0f,			0.0f,				1.0f,               0.0f));
				retMat.setRow(3, Vector4<float>(0.0f,			0.0f,				0.0f,               1.0f));
				return retMat;
			}
			static Matrix<T, 4, 4> rotationXYZMatrix(float radX, float radY, float radZ){
				Matrix4x4<T> rotateMatX, rotateMatY, rotateMatZ;
				rotateMatX = Matrix4x4<T>::rotationXMatrix(radX); 
				rotateMatY = Matrix4x4<T>::rotationYMatrix(radY); 
				rotateMatZ = Matrix4x4<T>::rotationZMatrix(radZ);
				return rotateMatZ * rotateMatY * rotateMatX;
			}
			static Matrix<T, 4, 4> rotationZYXMatrix(float radX, float radY, float radZ){
				Matrix4x4<T> rotateMatX, rotateMatY, rotateMatZ;
				rotateMatX = Matrix4x4<T>::rotationXMatrix(radX); 
				rotateMatY = Matrix4x4<T>::rotationYMatrix(radY); 
				rotateMatZ = Matrix4x4<T>::rotationZMatrix(radZ);
				return rotateMatX * rotateMatY * rotateMatZ;
			}
            static Matrix<T, 4, 4> rotationMatrix(Quaternion<T, 4> const& q){
                math::Matrix<T, 4, 4> r;
                T x = q.getConstData()[0];
                T y = q.getConstData()[1];
                T z = q.getConstData()[2];
                T w = q.getConstData()[3];
				r.setColumn(0, Vector4<T>(1.0f - 2.0f * y * y - 2.0f * z * z, 
                                         2.0f * x * y + 2.0f * w * z, 
                                         2.0f * x * z - 2.0f * w * y,
                                         0.0f));
				r.setColumn(1, Vector4<T>(2.0f * x * y - 2.0f * w * z,
                                         1.0f - 2.0f * x * x - 2.0f * z * z,
                                         2.0f * y * z + 2.0f * w * x,
                                         0.0f));
				r.setColumn(2, Vector4<T>(2.0f * x * z + 2.0f * w * y,
                                         2.0f * y * z - 2.0f * w * x,
                                         1.0f - 2.0f * x * x - 2.0f * y * y,
                                         0.0f));
				r.setColumn(3, Vector4<T>(0.0f,0.0f,0.0f,1.0f));
				return r;
			}
			// make this a translation matrix
			static Matrix<T, 4, 4> translationMatrix(float x, float y, float z){
				Matrix<T, 4, 4> retMat = Matrix<T, 4, 4>::identity();
				retMat = Matrix<T, 4, 4>::translationMatrix(Vector4<T>(x, y, z, 1.0f)); 
				return retMat;
			}
            // translation matrix
			static Matrix<T, 4, 4> translationMatrix(Vector<T, 3> const& v1){
                return Matrix<T, 4, 4>::translationMatrix(v1);
            }

			// make this a scaling matrix
			static Matrix<T, 4, 4> scaleMatrix(float f){
				Matrix<T, 4, 4> retMat = Matrix<T, 4, 4>::identity();
				retMat = Matrix<T, 4, 4>::scaleMatrix(Vector4<T>(f, f, f, f)); 
				return retMat;
			}
			static Matrix<T, 4, 4> scaleMatrix(float x, float y, float z, float w){
				Matrix<T, 4, 4> retMat = Matrix<T, 4, 4>::identity();
				retMat = Matrix<T, 4, 4>::scaleMatrix(Vector4<T>(x, y, z, w)); 
				return retMat;
			}
            // scale matrix
			static Matrix<T, 4, 4> scaleMatrix(Vector<T, 3> const& v1){
                return Matrix<T, 4, 4>::scaleMatrix(v1);
            }
		};
        
        //! explicit matrix types
        typedef Matrix3x3<float> Matrix3x3f;
        typedef Matrix4x4<float> Matrix4x4f;
	};
};

///////////////////////////////////////////////////////////////////////////////

#endif

///////////////////////////////////////////////////////////////////////////////