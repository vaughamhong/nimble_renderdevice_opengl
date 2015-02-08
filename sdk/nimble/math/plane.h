//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_math_plane_h__
#define __nimble_math_plane_h__

///////////////////////////////////////////////////////////////////////////////

#include <nimble/math/vector.h>

///////////////////////////////////////////////////////////////////////////////

namespace nimble{
	namespace math{

		//! template plane
		template <typename T, int N>
        class Plane{
		private:

			Vector<T, N+1> m_normal;
			float m_distance;

		public:

			//! Constructor
			Plane(){}
			//! copy constructor
			Plane(Plane const& p1){assignment(p1);}
			//! copy constructor
			Plane(Vector<T, N> const& n1, float distance){m_normal = n1; m_distance = distance;}

			//! data access
			Vector<T, N> getNormal()const{return m_normal;}
			//! data access
			float getDistance()const{return m_distance;}

			// operator overloads
			Plane<T, N> operator=(Plane<T, N> const& p1){assignment(p1); return Plane<T, N>(*this);}

			//! assignment
			void assignment(Plane<T, N> const& p1){m_normal = p1.getNormal(); m_distance = p1.getDistance();}
		};

		//! template plane3
		template <typename T = float>
        class Plane3: public Plane<T, 3>{
		public:
			Plane3(){}
			Plane3(Plane<T, 3> const& p1){assignment(p1);}
			Plane3(Vector<T, 3> const& v1, float distance):Plane<T, 3>(v1, distance){}

			// operator overloads
			Plane<T, 3> operator=(Plane<T, 3> const& p1){assignment(p1); return Plane<T, 3>(*this);}
		};
        
        //! plane types
        typedef Plane3<float> Plane3f;
	};
};

///////////////////////////////////////////////////////////////////////////////

#endif

///////////////////////////////////////////////////////////////////////////////
