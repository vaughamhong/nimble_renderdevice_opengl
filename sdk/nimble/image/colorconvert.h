//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_image_colorconvert_h__
#define __nimble_image_colorconvert_h__

//////////////////////////////////////////////////////////////////////////

#include <nimble/image/color.h>

//////////////////////////////////////////////////////////////////////////

namespace nimble{
	namespace image{
        
        // converts color buffer formats
        template <typename SourceFormat, typename DestFormat>
        void convertFormat(SourceFormat const *src, DestFormat *dest, int32_t width, int32_t height);
        
        // inline methods
        #include "colorconvert.inline.h"
    };
};

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////