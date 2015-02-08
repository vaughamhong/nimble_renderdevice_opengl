//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_math_axisalignedbox_h__
#define __nimble_math_axisalignedbox_h__

//////////////////////////////////////////////////////////////////////////

#include <nimble/math/vector.h>
#include <nimble/math/plane.h>
#include <nimble/math/mathops.h>
#include <stdint.h>
#include <assert.h>

//////////////////////////////////////////////////////////////////////////

namespace nimble{
	namespace math{

		//! templated axis aligned box
		template <typename T, int N> 
        class AxisAlignedBox{
        private:
            
			Vector<T, N> m_minimum;
			Vector<T, N> m_maximum;
            
		public:

			Vector<T, N> getCenter() const;
			Vector<T, N> getMinimum() const;
            Vector<T, N> getMaximum() const;
			float getDimension(int i) const;
            math::Vector<T, N> getSize() const;

        public:
            
            void setMinimum(Vector<T, N> const& p1);
			void setMaximum(Vector<T, N> const& p1);
        
        public:
            
			bool operator==(AxisAlignedBox<T, N> const& p1) const{return equal(p1);}
			bool operator!=(AxisAlignedBox<T, N> const& p1) const{return notEqual(p1);}
            
        public:
            
			// comparison
			bool equal(AxisAlignedBox<T, N> const& p1) const{return m_minimum == p1.m_minimum && m_maximum == p1.m_maximum;}
			bool notEqual(AxisAlignedBox<T, N> const& p1) const{return !equal(p1);}
		};
        
        //! aab2
		template <typename T = float>
        class AxisAlignedBox2
        : public AxisAlignedBox<T, 2>{
		public:
            
			//! a constructor
			AxisAlignedBox2();
			//! a copy constructor
			AxisAlignedBox2(AxisAlignedBox2<> const & aab);
			//! a constructor
			AxisAlignedBox2(Vector<T, 2> const& min, Vector<T, 2> const& max);
			//! a constructor
			AxisAlignedBox2(Vector<T, 2> const& center, T width, T height);
            
        public:
            
            bool operator==(AxisAlignedBox<T, 2> const& p1) const{return this->equal(p1);}
			bool operator!=(AxisAlignedBox<T, 2> const& p1) const{return this->notEqual(p1);}
            
        public:
            
			//! returns the width of the aab
			T getWidth() const;
			//! returns the height of the aab
			T getHeight() const;
            
			//! returns the corner point given an index
			Vector<T, 2> getCornerPoint(int index) const;
            
			//! returns the identity aabox
			static AxisAlignedBox2<T> identity();
		};

		//! aab3
		template <typename T = float> 
        class AxisAlignedBox3
        : public AxisAlignedBox<T, 3>{
		public:
            
			//! a constructor
			AxisAlignedBox3();
			//! a copy constructor
			AxisAlignedBox3(AxisAlignedBox3<> const & aab);
			//! a constructor
			AxisAlignedBox3(Vector<T, 3> const& min, Vector<T, 3> const& max);
			//! a constructor
			AxisAlignedBox3(Vector<T, 3> const& center, T width, T height, T depth);

        public:
            
            bool operator==(AxisAlignedBox<T, 3> const& p1) const{return this->equal(p1);}
			bool operator!=(AxisAlignedBox<T, 3> const& p1) const{return this->notEqual(p1);}
            
        public:
            
			//! returns the width of the aab
			T getWidth() const;
			//! returns the height of the aab
			T getHeight() const;
			//! returns the depth of the aab
			T getDepth() const;
            
			//! returns the corner point given an index
			Vector<T, 3> getCornerPoint(int index) const;
			//! returns the corner point given an index
			Plane3<> getFacePlane(int index) const;

			//! returns the identity aabox
			static AxisAlignedBox3<T> identity();
		};
        
        //! aab types
        typedef AxisAlignedBox2<float> AxisAlignedBox2f;
        typedef AxisAlignedBox2<int16_t> AxisAlignedBox2s;
        typedef AxisAlignedBox2<int32_t> AxisAlignedBox2i;
        typedef AxisAlignedBox3<float> AxisAlignedBox3f;
        typedef AxisAlignedBox3<int16_t> AxisAlignedBox3s;
        typedef AxisAlignedBox3<int32_t> AxisAlignedBox3i;
        
        //! AxisAlignedBox inline functions
        #include "axisalignedbox.inline.h"
	};
};

//////////////////////////////////////////////////////////////////////////

#endif

///////////////////////////////////////////////////////////////////////////////