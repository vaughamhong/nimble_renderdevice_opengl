//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#include <nimble/renderdevice/opengl/mappings.h>
#include <nimble/renderdevice/opengl/texture.h>
#include <nimble/core/ilockable.h>

//////////////////////////////////////////////////////////////////////////

using namespace nimble;

//////////////////////////////////////////////////////////////////////////

//! maps RenderDevice enums to GL
int nimble::renderdevice::opengl::gTextureDimensionMap[renderdevice::kMaxTextureDimentions] ={
	-1,
	GL_TEXTURE_2D,
	-1};

//! maps RenderDevice enums to GL
int nimble::renderdevice::opengl::gTextureUnitMap[renderdevice::kMaxTextureUnits] ={
	GL_TEXTURE0,
	GL_TEXTURE1,
	-1,
    -1};

//! maps RenderDevice enums to GL
#define GLTEXTURE_TUPLE(SRCFORMAT, INTERNALFORMAT, TYPE, PIXELSIZE) SRCFORMAT,
int nimble::renderdevice::opengl::gTextureFormatMap[renderdevice::kMaxTextureFormats] ={
    GLTEXTURE_TUPLESET
};
#undef GLTEXTURE_TUPLE

//! maps RenderDevice enums to GL
#define GLTEXTURE_TUPLE(SRCFORMAT, INTERNALFORMAT, TYPE, PIXELSIZE) INTERNALFORMAT,
int nimble::renderdevice::opengl::gTextureInternalFormatMap[renderdevice::kMaxTextureFormats] ={
    GLTEXTURE_TUPLESET
};
#undef GLTEXTURE_TUPLE

//! maps RenderDevice enums to GL
#define GLTEXTURE_TUPLE(SRCFORMAT, INTERNALFORMAT, TYPE, PIXELSIZE) TYPE,
int nimble::renderdevice::opengl::gTextureTypeMap[renderdevice::kMaxTextureFormats] ={
    GLTEXTURE_TUPLESET
};
#undef GLTEXTURE_TUPLE

//! maps RenderDevice enums to GL
#define GLTEXTURE_TUPLE(SRCFORMAT, INTERNALFORMAT, TYPE, PIXELSIZE) PIXELSIZE,
int nimble::renderdevice::opengl::gTexturePixelSizeMap[renderdevice::kMaxTextureFormats] ={
    GLTEXTURE_TUPLESET
};
#undef GLTEXTURE_TUPLE

//! maps RenderDevice enums to GL
int nimble::renderdevice::opengl::gTextureWrapParamValueMap[renderdevice::kMaxTextureWrapParams] ={
	GL_TEXTURE_WRAP_S,
	GL_TEXTURE_WRAP_T};

//! maps RenderDevice enums to GL
int nimble::renderdevice::opengl::gTextureWrapModeValueMap[renderdevice::kMaxTextureWrapModes] ={
	GL_CLAMP_TO_EDGE,
    GL_CLAMP_TO_BORDER,
	GL_REPEAT};

//! maps RenderDevice enums to GL
int nimble::renderdevice::opengl::gTextureFilterParamValueMap[renderdevice::kMaxTextureFilterParams] ={
    GL_TEXTURE_MAG_FILTER,
    GL_TEXTURE_MIN_FILTER};

//! maps RenderDevice enums to GL
int nimble::renderdevice::opengl::gTextureFilterModeValueMap[renderdevice::kMaxTextureFilterModes] ={
	GL_NEAREST,
	GL_LINEAR,
    GL_NEAREST_MIPMAP_NEAREST,
    GL_NEAREST_MIPMAP_LINEAR,
    GL_LINEAR_MIPMAP_NEAREST,
    GL_LINEAR_MIPMAP_LINEAR};

//! maps RenderDevice enums to GL
int nimble::renderdevice::opengl::gVertexAttributeTypeMap[renderdevice::VertexFormat::kMaxAttributeTypes] ={
	GL_FLOAT,
	GL_FLOAT,
	GL_FLOAT,
	GL_FLOAT,
	GL_UNSIGNED_BYTE,
	GL_UNSIGNED_BYTE,
	GL_UNSIGNED_BYTE,
	GL_UNSIGNED_BYTE,
    GL_SHORT,
    GL_SHORT,
    GL_SHORT,
    GL_SHORT};

//! maps RenderDevice enums to GL
int nimble::renderdevice::opengl::gVertexAttributeTypeDimensionMap[renderdevice::VertexFormat::kMaxAttributeTypes] ={
	1,
	2,
	3,
	4,
	1,
	2,
	3,
	4,
    1,
	2,
	3,
	4};

//! maps RenderDevice enums to GL
//! OpenGL ES 2.0 doesn't support QUAD LISTS
//! TODO proper caps detection
int nimble::renderdevice::opengl::gIndexFormatMap[renderdevice::kMaxPrimitiveTypes] ={
	GL_TRIANGLES,
	GL_TRIANGLE_FAN,
	GL_TRIANGLE_STRIP,
	0,
	GL_POINTS,
	GL_LINES};

//! maps RenderDevice enums to GL
int nimble::renderdevice::opengl::gIndexIndexTypeSizeMap[renderdevice::kMaxIndexTypes] ={
    1,
	2,
    4};

//////////////////////////////////////////////////////////////////////////