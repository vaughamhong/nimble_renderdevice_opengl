//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_math_contains_h__
#define __nimble_math_contains_h__

///////////////////////////////////////////////////////////////////////////////

#include <nimble/math/sphere.h>
#include <nimble/math/axisalignedbox.h>
#include <nimble/math/ray.h>

///////////////////////////////////////////////////////////////////////////////

namespace nimble{
	namespace math{

		//! returns true if aab2 is contained inside the aab
		bool contains(AxisAlignedBox3<> const& aab, AxisAlignedBox3<> const& aab2);
		//! returns true point is contained inside the aab
		bool contains(AxisAlignedBox3<> const& aab, Vector3<> const& point);
		//! returns true if ray is contained inside aabb
		bool contains(AxisAlignedBox3<> const& aab, Ray3<> const& ray);
		//! returns true if sphere is contained inside the aab
		bool contains(AxisAlignedBox3<> const& aab, Sphere3<> const& sphere);

		//! returns true if aab2 is contained inside the sphere
		bool contains(Sphere3<> const& sphere, AxisAlignedBox3<> const& aab2);
		//! returns true point is contained inside the sphere
		bool contains(Sphere3<> const& sphere, Vector3<> const& point);
		//! returns true if ray is contained inside sphere
		bool contains(Sphere3<> const& sphere, Ray3<> const& ray);
		//! returns true if sphere is contained inside the sphere
		bool contains(Sphere3<> const& sphere, Sphere3<> const& sphere2);
	};
};

///////////////////////////////////////////////////////////////////////////////

#endif

///////////////////////////////////////////////////////////////////////////////