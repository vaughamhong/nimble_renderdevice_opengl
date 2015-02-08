//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_math_sphere_h__
#define __nimble_math_sphere_h__

///////////////////////////////////////////////////////////////////////////////

#include <nimble/math/vector.h>

///////////////////////////////////////////////////////////////////////////////

namespace nimble{
	namespace math{

		//! templated sphere
		template <typename T, int N>
        class Sphere{
		private:

			Vector<T, N> m_position;
			T m_radius;

		public:
            
			//! Constructor
			Sphere():m_position(Vector<T, N>::zero()), m_radius(1.0f){}
			//! Constructor
			Sphere(Vector<T, N> const& position, T radius):m_position(position), m_radius(radius){}
			//! Destructor
			virtual ~Sphere(){}

		public:
            
			//! returns position
			Vector<T, N> getPosition() const{return m_position;}
			//! sets position
			void setPosition(Vector<T, N> const& position){m_position = position;}

			//! returns radius
			float getRadius() const{return m_radius;}
			//! sets radius
			void setRadius(T radius){m_radius = radius;}
		};

		//! sphere3
		template <typename T = float> class Sphere3
        : public Sphere<T, 3>{
		public:

			//! a constructor
			Sphere3(Vector<T, 3> const& position, float radius)
            :Sphere<T, 3>(position, radius){
			}

			//! a constructor
			Sphere3(){
				setPosition(Vector<T, 3>::zero());
				setRadius((T)1.0f);
			}

			//! a copy constructor
			Sphere3(Sphere3<> const& sphere)
            :Sphere<T, 3>(sphere.getPosition(), sphere.getRadius()){
			}

			//! returns the identity sphere
			static Sphere3<T> identity(){
				Sphere3<T> sphere;
				sphere.setPosition(Vector3<T>(0.0f, 0.0f, 0.0f));
				sphere.setRadius(1.0f);
				return sphere;
			}
		};
        
        //! sphere types
        typedef Sphere<float, 2> Sphere2f;
        typedef Sphere3<float> Sphere3f;
	};
};

///////////////////////////////////////////////////////////////////////////////

#endif

///////////////////////////////////////////////////////////////////////////////