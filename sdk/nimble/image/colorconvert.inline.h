//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

//////////////////////////////////////////////////////////////////////////

// TODO: wow color conversion, such optimization candidate

//////////////////////////////////////////////////////////////////////////

// converts R5G6B5 to R8G8B8A8
template <>
inline void convertFormat<colorR5G6B5_t, colorR8G8B8A8_t>(colorR5G6B5_t const *src, colorR8G8B8A8_t *dest, int32_t width, int32_t height){
    for(int32_t i = 0; i < width * height; i++){
        image::colorR5G6B5_t const &in = src[i];
        image::colorR8G8B8A8_t &out = dest[i];
        uint8_t r5 = (uint8_t)((in.value & 0xF800) >> 11);
        uint8_t g6 = (uint8_t)((in.value & 0x07E0) >> 5);
        uint8_t b5 = (uint8_t)((in.value & 0x001F) >> 0);
        out.rgba.r = (r5 << 3) | (r5 >> 2);    //!< map the top 3 bits to the bottom 3
        out.rgba.g = (g6 << 2) | (g6 >> 4);    //!< map the top 2 bits to the bottom 2
        out.rgba.b = (b5 << 3) | (b5 >> 2);    //!< map the top 3 bits to the bottom 3
        out.rgba.a = 255;
    }
}
// converts R8G8B8A8 to R5G6B5
template <>
inline void convertFormat<colorR8G8B8A8_t, colorR5G6B5_t>(colorR8G8B8A8_t const *src, colorR5G6B5_t *dest, int32_t width, int32_t height){
    for(int32_t i = 0; i < width * height; i++){
        image::colorR8G8B8A8_t const &in = src[i];
        image::colorR5G6B5_t &out = dest[i];
        uint8_t r = in.rgba.r;
        uint8_t g = in.rgba.g;
        uint8_t b = in.rgba.b;
        out.rgb.r = (r >> 3);       //!< chop off lower bits
        out.rgb.g = (g >> 2);       //!< chop off lower bits
        out.rgb.b = (b >> 3);       //!< chop off lower bits
    }
}

//////////////////////////////////////////////////////////////////////////

// converts R5G6B5 to B5G6R5
template <>
inline void convertFormat<colorR5G6B5_t, colorB5G6R5_t>(colorR5G6B5_t const *src, colorB5G6R5_t *dest, int32_t width, int32_t height){
    for(int32_t i = 0; i < width * height; i++){
        uint8_t r = src[i].rgb.r;
        uint8_t g = src[i].rgb.g;
        uint8_t b = src[i].rgb.b;
        dest[i].bgr.r = r;
        dest[i].bgr.g = g;
        dest[i].bgr.b = b;
    }
}
// converts B5G6R5 to R5G6B5
template <>
inline void convertFormat<colorB5G6R5_t, colorR5G6B5_t>(colorB5G6R5_t const *src, colorR5G6B5_t *dest, int32_t width, int32_t height){
    for(int32_t i = 0; i < width * height; i++){
        uint8_t r = src[i].bgr.r;
        uint8_t g = src[i].bgr.g;
        uint8_t b = src[i].bgr.b;
        dest[i].rgb.r = r;
        dest[i].rgb.g = g;
        dest[i].rgb.b = b;
    }
}

//////////////////////////////////////////////////////////////////////////

// converts R8G8B8 to B8G8R8
template <>
inline void convertFormat<colorR8G8B8_t, colorB8G8R8_t>(colorR8G8B8_t const *src, colorB8G8R8_t *dest, int32_t width, int32_t height){
    for(int32_t i = 0; i < width * height; i++){
        uint8_t r = src[i].rgb.r;
        uint8_t g = src[i].rgb.g;
        uint8_t b = src[i].rgb.b;
        dest[i].bgr.r = r;
        dest[i].bgr.g = g;
        dest[i].bgr.b = b;
    }
}
// converts B8G8R8 to R8G8B8
template <>
inline void convertFormat<colorB8G8R8_t, colorR8G8B8_t>(colorB8G8R8_t const *src, colorR8G8B8_t *dest, int32_t width, int32_t height){
    for(int32_t i = 0; i < width * height; i++){
        uint8_t r = src[i].bgr.r;
        uint8_t g = src[i].bgr.g;
        uint8_t b = src[i].bgr.b;
        dest[i].rgb.r = r;
        dest[i].rgb.g = g;
        dest[i].rgb.b = b;
    }
}

//////////////////////////////////////////////////////////////////////////

// converts R8G8B8A8 to B8G8R8A8
template <>
inline void convertFormat<colorR8G8B8A8_t, colorB8G8R8A8_t>(colorR8G8B8A8_t const *src, colorB8G8R8A8_t *dest, int32_t width, int32_t height){
    for(int32_t i = 0; i < width * height; i++){
        uint8_t r = src[i].rgba.r;
        uint8_t g = src[i].rgba.g;
        uint8_t b = src[i].rgba.b;
        uint8_t a = src[i].rgba.a;
        dest[i].bgra.r = r;
        dest[i].bgra.g = g;
        dest[i].bgra.b = b;
        dest[i].bgra.a = a;
    }
}
// converts B8G8R8A8 to R8G8B8A8
template <>
inline void convertFormat<colorB8G8R8A8_t, colorR8G8B8A8_t>(colorB8G8R8A8_t const *src, colorR8G8B8A8_t *dest, int32_t width, int32_t height){
    for(int32_t i = 0; i < width * height; i++){
        uint8_t r = src[i].bgra.r;
        uint8_t g = src[i].bgra.g;
        uint8_t b = src[i].bgra.b;
        uint8_t a = src[i].bgra.a;
        dest[i].rgba.r = r;
        dest[i].rgba.g = g;
        dest[i].rgba.b = b;
        dest[i].rgba.a = a;
    }
}

//////////////////////////////////////////////////////////////////////////