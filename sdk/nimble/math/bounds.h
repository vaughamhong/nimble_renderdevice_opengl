//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_math_bounds_h__
#define __nimble_math_bounds_h__

///////////////////////////////////////////////////////////////////////////////

#include <nimble/math/vector.h>
#include <nimble/math/vector.h>

///////////////////////////////////////////////////////////////////////////////

namespace nimble{
	namespace math{
        
		//! templated bounds class
		template <typename T, int N> 
        class Bounds{
		private:
			
            math::Vector<T, N>  m_size;
            math::Vector<T, N>  m_position;
            
		public:
            
			//! Constructor
			Bounds():m_size(math::Vector<T, N>::zero()), m_position(math::Vector<T, N>::zero()){}
			//! copy constructor
			Bounds(Bounds<T, N> const& p1){this->assignment(p1);}
            //! copy constructor
            Bounds(math::Vector<T, N> const& size):m_size(size), m_position(math::Vector<T, N>::zero()){}
			//! copy constructor
            Bounds(math::Vector<T, N> const& position, math::Vector<T, N> const& size):m_size(size), m_position(position){}
			//! Destructor
			~Bounds(){}
            
		public:
            
            //! data access
            math::Vector<T, N> getSize() const{return m_size;}
            //! data access
            math::Vector<T, N> getPosition() const{return m_position;}
            
            //! returns the dimensions of the vector
			int getDimension() const{return N;}
            
		public:
            
			bool operator==(Bounds<T, N> const& p1) const{return equal(p1);}
			bool operator!=(Bounds<T, N> const& p1) const{return notEqual(p1);}
			
			Bounds<T, N> operator=(Bounds<T, N> const& p1){assignment(p1); return Bounds<T, N>(*this);}
			
		public:
            
			// assignment
			void assignment(Bounds<T, N> const& p1){
                m_size = p1.m_size;
                m_position = p1.m_position;
            }
			
			// comparison
			bool equal(Bounds<T, N> const& p1) const{
                return m_size == p1.m_size && m_position == p1.m_position;
            }
			bool notEqual(Bounds<T, N> const& p1) const{return !equal(p1);}
            
		public:
            
			static Bounds<T, N> zero(){return Bounds(math::Vector<T, N>::zero(), math::Vector<T, N>::zero());}
            static Bounds<T, N> unit(){return Bounds(math::Vector<T, N>::unit(), math::Vector<T, N>::zero());}
		};
        
        //! bound types
        typedef Bounds<int, 2> Bounds2;
        typedef Bounds<float, 2> Bounds2f;
        typedef Bounds<float, 3> Bounds3f;
	};
};

///////////////////////////////////////////////////////////////////////////////

#endif

///////////////////////////////////////////////////////////////////////////////