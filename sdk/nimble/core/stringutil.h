//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_core_cast_h__
#define __nimble_core_cast_h__

//////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <sstream>

//////////////////////////////////////////////////////////////////////////

namespace nimble{
    namespace core{
        
        // cast to string
        template <typename T>
        std::string lexical_cast(T &t){
            std::ostringstream ss;
            ss << t;
            return ss.str();
        }

        // converts wchar_t strings to utf8 encoded std::string
        std::string utf8_encode(const std::wstring &wstr);
        // replaces all strings that match 'from' to 'to'
        void replaceAll(std::string& str, const std::string& from, const std::string& to);
    };
};

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////