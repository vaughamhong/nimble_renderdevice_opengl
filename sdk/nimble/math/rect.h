//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_math_rect_h__
#define __nimble_math_rect_h__

///////////////////////////////////////////////////////////////////////////////

#include <nimble/math/vector.h>
#include <stdint.h>

///////////////////////////////////////////////////////////////////////////////

namespace nimble{
	namespace math{
		
		//! templated rect
		template <typename T, int N> 
        class Rect{
		private:
			
            math::Vector<T, N>  m_origin;
            math::Vector<T, N>  m_size;
            
		public:
            
			//! Constructor
			Rect(){
                m_origin = math::Vector<T, N>::zero();
                m_size = math::Vector<T, N>::zero();
            }
			//! copy constructor
			Rect(Vector<T, N> const& p1, Vector<T, N> const& s1){
                m_origin = p1;
                m_size = s1;
            }
			//! copy constructor
			Rect(Rect<T, N> const& p1){assignment(p1);}
			//! Destructor
			~Rect(){}
            
		public:
            
			//! returns origin
            math::Vector<T, N> getOrigin() const{return m_origin;}
            //! returns size
            math::Vector<T, N> getSize() const{return m_size;}
            //! sets origin
            void setOrigin(math::Vector<T, N> const& p1){m_origin = p1;}
            //! sets size
            void setSize(math::Vector<T, N> const& s1){m_size = s1;}
            
		public:
            
			bool operator==(Rect<T, N> const& p1) const{return equal(p1);}
			bool operator!=(Rect<T, N> const& p1) const{return notEqual(p1);}
			
			Rect<T, N> operator=(Rect<T, N> const& p1){assignment(p1); return Rect<T, N>(*this);}
			
		public:
            
			// assignment
			void assignment(Rect<T, N> const& p1){
                m_origin = p1.m_origin;
                m_size = p1.m_size;
            }
			
			// comparison
			bool equal(Rect<T, N> const& p1) const{
                return (p1.m_size == m_size) && (p1.m_origin == m_origin);
            }
			bool notEqual(Rect<T, N> const& p1) const{return !equal(p1);}
            
		public:
            
			static Rect<T, N> zero(){return Rect<T, N>(Vector<T, N>::zero(), Vector<T, N>::zero());}
            static Rect<T, N> unit(){return Rect<T, N>(Vector<T, N>::zero(), Vector<T, N>::unit());}
		};
        
        //! explicit point types
        typedef Rect<float, 2> Rect2f;
        typedef Rect<float, 3> Rect3f;
        typedef Rect<int32_t, 2> Rect2i;
        typedef Rect<int32_t, 3> Rect3i;
	};
};

///////////////////////////////////////////////////////////////////////////////

#endif

///////////////////////////////////////////////////////////////////////////////
