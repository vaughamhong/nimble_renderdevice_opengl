//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_image_color_h__
#define __nimble_image_color_h__

//////////////////////////////////////////////////////////////////////////

#include <stdint.h>

//////////////////////////////////////////////////////////////////////////

namespace nimble{
	namespace image{
        
        // 16bit RGB
        union colorR5G6B5_t{
            struct{
                uint8_t r:5;
                uint8_t g:6;
                uint8_t b:5;
            }rgb;
            uint8_t data[2];
            uint16_t value;
        };
        // 16bit BGR
        union colorB5G6R5_t{
            struct{
                uint8_t b:5;
                uint8_t g:6;
                uint8_t r:5;
            }bgr;
            uint8_t data[2];
            uint16_t value;
        };
        
        // 24bit RGB
        union colorR8G8B8_t{
            struct{
                uint8_t r, g, b;
            }rgb;
            uint8_t data[3];
        };
        // 24bit BGR
        union colorB8G8R8_t{
            struct{
                uint8_t b, g, r;
            }bgr;
            uint8_t data[3];
        };
        
        // 32bit RGBA
        union colorR8G8B8A8_t{
            struct{
                uint8_t r, g, b, a;
            }rgba;
            uint8_t data[4];
            uint32_t value;
        };
        // 32bit BGRA
        union colorB8G8R8A8_t{
            struct{
                uint8_t b, g, r, a;
            }bgra;
            uint8_t data[4];
            uint32_t value;
        };
    };
};

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////