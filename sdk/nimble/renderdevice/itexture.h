//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_renderdevice_itexture_h__
#define __nimble_renderdevice_itexture_h__

//////////////////////////////////////////////////////////////////////////

#include <nimble/resource/resource.h>
#include <nimble/resource/resourceloader.h>
#include <nimble/image/image.h>

//////////////////////////////////////////////////////////////////////////

#define TEXTURE_TUPLESET    \
TEXTURE_TUPLE(kTextureFormatR8G8B8,         sizeof(char) * 3,      24,     nimble::image::Image::kFormatR8G8B8) \
TEXTURE_TUPLE(kTextureFormatR16G16B16,      sizeof(short) * 3,     48,     nimble::image::Image::kFormatR16G16B16) \
TEXTURE_TUPLE(kTextureFormatRGBF,           sizeof(float) * 3,     96,     nimble::image::Image::kFormatRGBF) \
\
TEXTURE_TUPLE(kTextureFormatR8G8B8A8,       sizeof(char) * 4,      32,     nimble::image::Image::kFormatR8G8B8A8) \
TEXTURE_TUPLE(kTextureFormatR16G16B16A16,   sizeof(short) * 4,     64,     nimble::image::Image::kFormatR16G16B16A16) \
TEXTURE_TUPLE(kTextureFormatRGBAF,          sizeof(float) * 4,     128,    nimble::image::Image::kFormatRGBAF) \
\
TEXTURE_TUPLE(kTextureFormatB8G8R8,         sizeof(char) * 3,      24,     nimble::image::Image::kFormatB8G8R8) \
TEXTURE_TUPLE(kTextureFormatB8G8R8A8,       sizeof(char) * 4,      32,     nimble::image::Image::kFormatB8G8R8A8) \
\
TEXTURE_TUPLE(kTextureFormatDepth16,        sizeof(short) * 2,     16,     nimble::image::Image::kFormatDepth16) \
TEXTURE_TUPLE(kTextureFormatDepth24,        sizeof(short) * 3,     24,     nimble::image::Image::kFormatDepth24) \
TEXTURE_TUPLE(kTextureFormatDepth32,        sizeof(short) * 4,     32,     nimble::image::Image::kFormatDepth32)

//////////////////////////////////////////////////////////////////////////

namespace nimble{
	namespace renderdevice{

        //! texture format
        enum eTextureFormat{
        #define TEXTURE_TUPLE(ENUM, PIXEL_BYTESIZE, PIXEL_BPP, IMAGEFORMAT) ENUM,
            TEXTURE_TUPLESET
        #undef TEXTURE_TUPLE
            
            kMaxTextureFormats,
            kFirstFormat = kTextureFormatR8G8B8,
            kLastFormat	= kTextureFormatDepth16,
            kUnknownTextureFormat	= -1,
        };
        
        //! texture dimension
        enum eTextureDimension{
            kTextureDimention1D,
            kTextureDimention2D,
            kTextureDimention3D,
            
            kMaxTextureDimentions,
            kFirstTextureDimention = kTextureDimention1D,
            kLastTextureDimention = kTextureDimention3D,
            kUnknownTextureDimension = -1,
        };
        
        //! texture wrap parameter
        enum eTextureWrapParameter{
            kTextureWrapParamU,
            kTextureWrapParamV,
            
            kMaxTextureWrapParams
        };
        
        //! texture wrap mode
        enum eTextureWrapMode{
            kTextureWrapModeClampToEdge,
            kTextureWrapModeClampToBorder,
            kTextureWrapModeRepeat,
            
            kMaxTextureWrapModes,
            kDefaultTextureWrapMode = kTextureWrapModeRepeat,
            kUnknownTextureWrapMode = -1,
        };
        
        //! texture filter parameters
        enum eTextureFilterParameter{
            kTextureFilterParamMag,
            kTextureFilterParamMin,
            
            kMaxTextureFilterParams
        };
        
        //! texture filter mode
        enum eTextureFilterMode{
            kTextureFilterModeNearest,
            kTextureFilterModeLinear,
            
            kTextureFilterModeNearestMipMapNearest,
            kTextureFilterModeNearestMipMapLinear,
            kTextureFilterModeLinearMipMapNearest,
            kTextureFilterModeLinearMipMapLinear,
            
            kMaxTextureFilterModes,
            kDefaultTextureFilterMode = kTextureFilterModeLinear,
            kUnknownTextureFilterMode = -1,
        };
        
        //! Usage flags
        enum eTextureUsage{
            kTextureUsageStatic            = (1 << 1),
            kTextureUsageDynamic           = (1 << 2),
            kTextureUsageVolitile          = (1 << 3),
            
            kMaxTextureUsageTypes          = 3,
        };

		//! Abstract texture definition
		class ITexture{
		public:

            //! Destructor
			virtual ~ITexture(){}
            
		public:

            //! returns the usage
			//! \return the usage
			virtual uint32_t getUsage() const = 0;
			//! gets the format of this texture
            virtual renderdevice::eTextureFormat getFormat() const = 0;
			//! gets the number of dimensions of this texture
            virtual renderdevice::eTextureDimension getDimension() const = 0;
            //! gets the width of the texture
            virtual uint32_t getWidth() const = 0;
            //! gets the height of the texture
            virtual uint32_t getHeight() const = 0;
            //! gets the depth of the texture
            virtual uint32_t getDepth() const = 0;
            //! gets the bytes per pixel
            virtual uint32_t getBytesPerPixel() const = 0;
            //! gets the texture size in bytes
            virtual uint32_t getBufferSize() const = 0;
            
            //! gets the texture's sort index
            virtual uint32_t getSortIndex() const = 0;
            
		public:

			//! sets texture filter mode
			//! \param param the texture filter parameter we are interested in changing
			//! \param value the texture filter value
            virtual void setFilterMode(renderdevice::eTextureFilterParameter param, renderdevice::eTextureFilterMode value) = 0;
			//! sets texture wrap mode
			//! \param param the texture wrap parameter we are interested in changing
			//! \param value the texture wrap value
			virtual void setWrapMode(renderdevice::eTextureWrapParameter param, renderdevice::eTextureWrapMode value) = 0;

			//! gets the texture filter mode
			//! \param param the filter parameter
			virtual renderdevice::eTextureFilterMode getFilterMode(renderdevice::eTextureFilterParameter param) const = 0;
			//! gets the texture wrap mode
			//! \param param the wrap parameeter
			virtual renderdevice::eTextureWrapMode getWrapMode(renderdevice::eTextureWrapParameter param) const = 0;
            
            //! regenerates mipmaps
            virtual void regenerateMipMaps() = 0;
		};
	};
};

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////