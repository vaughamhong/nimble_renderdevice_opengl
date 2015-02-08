//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_core_endian_h__
#define __nimble_core_endian_h__

//////////////////////////////////////////////////////////////////////////

#include <stdint.h>

//////////////////////////////////////////////////////////////////////////

namespace nimble{
namespace core{
    
    //! returns true if we are big endian
    //! \return true if big endian
    inline bool isBigEndian(){
        union{
            int32_t i;
            char c[4];
        }bint={0x01020304};
        return bint.c[0] == 1;
    }
    //! returns true if we are little endian
    //! \return true if little endian
    inline bool isLittleEndian(){
        return !isBigEndian();
    }
};};

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////