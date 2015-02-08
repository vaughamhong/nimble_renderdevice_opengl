//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_math_random_h__
#define __nimble_math_random_h__

///////////////////////////////////////////////////////////////////////////////

#include <stdint.h>

///////////////////////////////////////////////////////////////////////////////

namespace nimble{
namespace math{
    
    //! random number generator
    class Random{
    private:
        
        uint64_t m_seed;
        uint64_t m_a;
        uint64_t m_m;
        uint64_t m_q;
        uint64_t m_r;
        double m_oneOverM;
        
    public:
        
        //! Constructor
        Random(uint64_t seed = 0);
        //! Destructor
        ~Random();
        
    public:
        
        //! returns a random number
        uint64_t rand();
    };
};};

///////////////////////////////////////////////////////////////////////////////

#endif

///////////////////////////////////////////////////////////////////////////////