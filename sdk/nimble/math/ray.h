//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_math_ray_h__
#define __nimble_math_ray_h__

///////////////////////////////////////////////////////////////////////////////

#include <nimble/math/vector.h>

///////////////////////////////////////////////////////////////////////////////

namespace nimble{
	namespace math{

		//! templated ray
		template <typename T, int N> class Ray{
		private:

			Vector<T, N> m_position;
			Vector<T, N> m_direction;

		public:
		
			//! Constructor
			Ray(){m_position = Vector<T, N>::zero(); m_direction = Vector<T, N>::zero();}
			//! copy constructor
			Ray(Ray<T, N-1> const& r1){m_position = r1.getPosition(); m_direction = r1.getDirection();}
			//! copy constructor
			Ray(Ray<T, N> const& r1){m_position = r1.getPosition(); m_direction = r1.getDirection();}
			//! copy constructor
			Ray(Ray<T, N+1> const& r1){m_position = r1.getPosition(); m_direction = r1.getDirection();}
			//! copy constructor
			Ray(Vector<T, N-1> const& p1, Vector<T, N-1> const& v1){m_position = p1; m_direction = v1;}
			//! copy constructor
			Ray(Vector<T, N> const& p1, Vector<T, N> const& v1){m_position = p1; m_direction = v1;}
			//! copy constructor
			Ray(Vector<T, N+1> const& p1, Vector<T, N+1> const& v1){m_position = p1; m_direction = v1;}
			//! Destructor
			~Ray(){}

			//! returns the position
			virtual Vector<T, N> getPosition() const{return m_position;}
			//! returns the direction
			virtual Vector<T, N> getDirection() const{return m_direction;}

			//! sets the position
			virtual void setPosition(Vector<T, N> const& position){m_position = position;}
			//! sets the direction
			virtual void setDirection(Vector<T, N> const& direction){m_direction = direction;}
		};

		//! ray3
		template <typename T = float> class Ray3
        : public Ray<T, 3>{
		public:
		
			//! Constructor
			Ray3(){}
            //! copy constructor
			Ray3(Ray<T, 3-1> const& r1):Ray<T, 3>(r1){}
			//! copy constructor
			Ray3(Ray<T, 3> const& r1):Ray<T, 3>(r1){}
			//! copy constructor
			Ray3(Ray<T, 3+1> const& r1):Ray<T, 3>(r1){}
			//! copy constructor
			Ray3(Vector<T, 3-1> const& p1, Vector<T, 3-1> const& v1):Ray<T, 3-1>(p1, v1){}
			//! copy constructor
			Ray3(Vector<T, 3> const& p1, Vector<T, 3> const& v1):Ray<T, 3>(p1, v1){}
			//! copy constructor
			Ray3(Vector<T, 3+1> const& p1, Vector<T, 3+1> const& v1):Ray<T, 3+1>(p1, v1){}
			//! Destructor
			~Ray3(){}
		};

		//! ray4
		template <typename T = float> class Ray4
        : public Ray<T, 4>{
		public:
		
			//! Constructor
			Ray4(){}
			//! copy constructor
			Ray4(Ray<T, 4-1> const& r1):Ray<T, 4>(r1){}
			//! copy constructor
			Ray4(Ray<T, 4> const& r1):Ray<T, 4>(r1){}
			//! copy constructor
			Ray4(Ray<T, 4+1> const& r1):Ray<T, 4>(r1){}
			//! copy constructor
			Ray4(Vector<T, 4-1> const& p1, Vector<T, 4-1> const& v1):Ray<T, 4-1>(p1, v1){}
			//! copy constructor
			Ray4(Vector<T, 4> const& p1, Vector<T, 4> const& v1):Ray<T, 4>(p1, v1){}
			//! copy constructor
			Ray4(Vector<T, 4+1> const& p1, Vector<T, 4+1> const& v1):Ray<T, 4+1>(p1, v1){}
			//! Destructor
			~Ray4(){}
		};
        
        //! rays
        typedef Ray3<float> Ray3f;
	};
};

#endif // __nimble_math_ray_h__