//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_core_strptime__
#define __nimble_core_strptime__

//////////////////////////////////////////////////////////////////////////

#include <cstdlib>
#include <time.h>

//////////////////////////////////////////////////////////////////////////

namespace nimble{
namespace core{
    
    //! Converts string to time
    const char *strptime(const char *buf, const char *fmt, struct tm *tm);
    
    //! Compares two strings without case
    int strncasecmp(const char *s1, const char *s2, size_t n);
};};

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////