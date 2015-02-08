//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_math_intersects_h__
#define __nimble_math_intersects_h__

///////////////////////////////////////////////////////////////////////////////

#include <nimble/math/sphere.h>
#include <nimble/math/axisalignedbox.h>
#include <nimble/math/ray.h>

///////////////////////////////////////////////////////////////////////////////

namespace nimble{
	namespace math{

		//! returns true if the aab2 intersects the aab
		bool intersects(AxisAlignedBox3<> const& aab, AxisAlignedBox3<> const& aab2);
		//! returns true if the point intersects the aab
		bool intersects(AxisAlignedBox3<> const& aab, Vector3<> const& point);
		//! returns true if the ray intersects the aab
		bool intersects(AxisAlignedBox3<> const& aab, Ray3<> const& ray);
		//! returns true if the sphere intersects the aab
		bool intersects(AxisAlignedBox3<> const& aab, Sphere3<> const& sphere);
        //! returns true if the triangle intersects the aab
		bool intersects(AxisAlignedBox3<> const& aab, Vector3<> const& p1, Vector3<> const& p2, Vector3<> const& p3);

		//! returns true if the aab intersects the sphere
		bool intersects(Sphere3<> const& sphere, AxisAlignedBox3<> const& aab);
		//! returns true if the point intersects the sphere
		bool intersects(Sphere3<> const& sphere, Vector3<> const& point);
		//! returns true if the ray intersects the sphere
		bool intersects(Sphere3<> const& sphere, Ray3<> const& ray);
		//! returns true if the sphere2 intersects the sphere
		bool intersects(Sphere3<> const& sphere, Sphere3<> const& sphere2);

		//! returns true if the aab intersects the ray
		bool intersects(Ray3<> const& ray, AxisAlignedBox3<> const& aab);
		//! returns true if the point intersects the ray
		bool intersects(Ray3<> const& ray, Vector3<> const& point);
		//! returns true if the ray2 intersects the ray
		bool intersects(Ray3<> const& ray, Ray3<> const& ray2);
		//! returns true if the sphere intersects the ray
		bool intersects(Ray3<> const& ray, Sphere3<> const& sphere);

		//! returns true if the aab intersects the plane
		bool intersects(Plane3<> const& plane, AxisAlignedBox3<> const& aab);
		//! returns true if the point intersects the plane
		bool intersects(Plane3<> const& plane, Vector3<> const& point);
		//! returns true if the ray intersects the plane
		bool intersects(Plane3<> const& plane, Ray3<> const& ray);
		//! returns true if the ray intersects the plane
		bool intersects(Plane3<> const& plane, Ray3<> const& ray, Vector3<>& intersectPoint);
		//! returns true if the sphere intersects the plane
		bool intersects(Plane3<> const& plane, Sphere3<> const& sphere);
		
		//! returns true if the ray intersects the triangle
		bool intersects(Vector3<> const& p1, Vector3<> const& p2, Vector3<> const& p3, Ray3<> const& ray);
		//! returns true if the ray intersects the triangle
		bool intersects(Vector3<> const& p1, Vector3<> const& p2, Vector3<> const& p3, Ray3<> const& ray, Vector3<>& intersectPoint);

		//! returns true if the ray intersects the point
		bool intersects(Vector3<> const& p1, Ray3<> const& ray, float elipsonDistance);
	};
};

///////////////////////////////////////////////////////////////////////////////

#endif

///////////////////////////////////////////////////////////////////////////////