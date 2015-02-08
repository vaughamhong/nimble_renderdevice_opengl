//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_renderdevice_iframebuffer_h__
#define __nimble_renderdevice_iframebuffer_h__

//////////////////////////////////////////////////////////////////////////

#include <stdint.h>
#include <cstdlib>

//////////////////////////////////////////////////////////////////////////

#define FRAMEBUFFER_TUPLESET \
FRAMEBUFFER_TUPLE(kFrameBufferDepth,         0) \
FRAMEBUFFER_TUPLE(kFrameBufferStencil,       1) \
FRAMEBUFFER_TUPLE(kFrameBufferAccumulation,  2) \
FRAMEBUFFER_TUPLE(kFrameBufferColor0,        3) \
FRAMEBUFFER_TUPLE(kFrameBufferColor1,        4) \
FRAMEBUFFER_TUPLE(kFrameBufferColor2,        5) \
FRAMEBUFFER_TUPLE(kFrameBufferColor3,        6) \
FRAMEBUFFER_TUPLE(kFrameBufferColor4,        7) \
FRAMEBUFFER_TUPLE(kFrameBufferColor5,        8) \
FRAMEBUFFER_TUPLE(kFrameBufferColor6,        9) \
FRAMEBUFFER_TUPLE(kFrameBufferColor7,        10) \

//////////////////////////////////////////////////////////////////////////

#define FRAMEBUFFERFLAG_TUPLESET \
FRAMEBUFFERFLAG_TUPLE(kFrameBufferFlagGenDepth24Stencil8,   0) \
FRAMEBUFFERFLAG_TUPLE(kFrameBufferFlagGenDepth16,           1) \
FRAMEBUFFERFLAG_TUPLE(kFrameBufferFlagGenDepth24,           2) \
FRAMEBUFFERFLAG_TUPLE(kFrameBufferFlagGenDepth32,           3) \
FRAMEBUFFERFLAG_TUPLE(kFrameBufferFlagGenStencil1,          4) \
FRAMEBUFFERFLAG_TUPLE(kFrameBufferFlagGenStencil4,          5) \
FRAMEBUFFERFLAG_TUPLE(kFrameBufferFlagGenStencil8,          6) \
FRAMEBUFFERFLAG_TUPLE(kFrameBufferFlagGenStencil16,         7) \

//////////////////////////////////////////////////////////////////////////

namespace nimble{
	namespace renderdevice{
		class ITexture;

        //! buffer types
        enum eFrameBufferType{
        #define FRAMEBUFFER_TUPLE(ENUM, INDEX) ENUM,
            FRAMEBUFFER_TUPLESET
        #undef FRAMEBUFFER_TUPLE
            kMaxFrameBufferTypes
        };
        //! buffer bit
        enum eFrameBufferBit{
        #define FRAMEBUFFER_TUPLE(ENUM, INDEX) ENUM##Bit = (1 << INDEX),
            FRAMEBUFFER_TUPLESET
        #undef FRAMEBUFFER_TUPLE
        };
        //! buffer flags
        enum eFrameBufferFlag{
        #define FRAMEBUFFERFLAG_TUPLE(FLAG, INDEX) FLAG = (1 << INDEX),
            FRAMEBUFFERFLAG_TUPLESET
        #undef FRAMEBUFFERFLAG_TUPLE
        };

		//! frame buffer
		class IFrameBuffer{
        public:
            
			//! Destructor
			virtual ~IFrameBuffer(){}

		public:
            
            //! returns true if this frame buffer is complete
            virtual bool isComplete() const = 0;
            
            //! attach a texture target
            //! \param type the type to attach
            //! \param pTexture the texture to attach
            virtual void attachTextureTarget(renderdevice::eFrameBufferType type, renderdevice::ITexture *pTexture) = 0;
            //! detaches a texture target
            //! \param type the type to detach
            virtual void detachTextureTarget(renderdevice::eFrameBufferType type) = 0;
			//! attach a set of texture targets
			//! \param types the types to attach
			//! \param pTextures the textures to attach
            //! \param numTargets the number of textures to attach
			virtual void attachTextureTargets(renderdevice::eFrameBufferType *types, renderdevice::ITexture **pTextures, size_t numTargets) = 0;
            //! detaches a set of texture targets
            //! \param types the types to detach
            //! \param numTargets the number of textures to detach
            virtual void detachTextureTargets(renderdevice::eFrameBufferType *types, size_t numTargets) = 0;
            
            //! sets writable targets
            virtual void setWriteTargets(uint32_t bufferMask) = 0;
            
            //! returns the render target
            virtual renderdevice::ITexture* getTarget(renderdevice::eFrameBufferType buffer) = 0;
            
			//! returns the width
			//! \return the width
			virtual uint32_t getWidth() const = 0;
			//! returns the height
			//! \return the height
			virtual uint32_t getHeight() const = 0;
		};
	};
};

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////