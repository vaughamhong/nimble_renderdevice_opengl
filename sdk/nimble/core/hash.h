//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_core_stringops_h__
#define __nimble_core_stringops_h__

//////////////////////////////////////////////////////////////////////////

#include <stdint.h>
#include <string>

//////////////////////////////////////////////////////////////////////////

namespace nimble{
namespace core{
    
    //! returns a hash from a c string
    int32_t hash(const char *data);
    //! returns a hash from a std string
    int32_t hash(const std::string &data);
    
    //! returns a md5 hash from a std string
    std::string hash_md5(const std::string &data);
    //! returns a djb2 hash from a c string
    int64_t hash_djb2(const char *str);
};};

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////