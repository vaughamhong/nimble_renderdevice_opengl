//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_renderdevice_irenderdevice_h__
#define __nimble_renderdevice_irenderdevice_h__

//////////////////////////////////////////////////////////////////////////

#include <nimble/math/matrix.h>

//////////////////////////////////////////////////////////////////////////

#include <nimble/renderdevice/iframebuffer.h>
#include <nimble/renderdevice/ivertexbuffer.h>
#include <nimble/renderdevice/iindexbuffer.h>
#include <nimble/renderdevice/itexture.h>
#include <nimble/renderdevice/ishader.h>
#include <nimble/renderdevice/ishaderprogram.h>

//////////////////////////////////////////////////////////////////////////

namespace nimble{
	namespace renderdevice{
        
        //! render states
        enum eRenderState{
            kRenderStateColorWrite,
            kRenderStateDepthWrite,
            kRenderStateStencilWrite,
            kRenderStateDepthTest,
            kRenderStateStencilTest,
            kRenderStateCullTest,
            kRenderStateBlending,
            kRenderStateLighting,
            kRenderStateTexturing,
            kMaxRenderStates
        };
        
        //! blend factor
        enum eRenderBlendFactor{
            kRenderBlendFactorZero,
            kRenderBlendFactorOne,
            kRenderBlendFactorSrcAlpha,
            kRenderBlendFactorOneMinusSrcAlpha
        };
        
        //! face
        enum eRenderFace{
            kRenderFaceFront,
            kRenderFaceBack,
            kRenderFaceFrontAndBack,
        };
        
        //! fill mode
        enum eRenderFillMode{
            kRenderFillModePoint,
            kRenderFillModeLine,
            kRenderFillModeFill,
        };
        
        //! depth func
        enum eRenderDepthFunc{
            kRenderDepthFuncNever,
            kRenderDepthFuncAlways,
            
            kRenderDepthFuncLessEqual,
            kRenderDepthFuncLess,
            
            kRenderDepthFuncGreaterEqual,
            kRenderDepthFuncGreater,
            
            kRenderDepthFuncEqual
        };
        
        //! stencil func
        enum eRenderStencilFunc{
            kRenderStencilFuncNever,
            kRenderStencilFuncAlways,
            
            kRenderStencilFuncLessEqual,
            kRenderStencilFuncLess,
            
            kRenderStencilFuncGreaterEqual,
            kRenderStencilFuncGreater,
            
            kRenderStencilFuncEqual,
            kRenderStencilFuncNotEqual,
        };
        
        //! stencil operation
        enum eRenderStencilOp{
            kRenderStencilOpKeep,
            kRenderStencilOpZero,
            kRenderStencilOpReplace,
            kRenderStencilOpIncr,
            kRenderStencilOpIncrWrap,
            kRenderStencilOpDecr,
            kRenderStencilOpDecrWrap,
            kRenderStencilOpInvert
        };
        
        //! cull face
        enum eRenderCullFace{
            kRenderCullFaceNone,
            kRenderCullFaceFront,
            kRenderCullFaceBack
        };

        //! front face orientation
        enum eRenderOrientation{
            kRenderOrientationClockwise,
            kRenderOrientationCounterClockwise
        };

        //! render buffers
        enum eRenderBuffer{
            kRenderBufferDepth			= (1 << 1),
            kRenderBufferStencil        = (1 << 2),
            kRenderBufferAccumulation   = (1 << 3),
            kRenderBufferColor0			= (1 << 4),
            kRenderBufferColor1			= (1 << 5),
            kRenderBufferColor2			= (1 << 6),
            kRenderBufferColor3			= (1 << 7),
            kRenderBufferColor4			= (1 << 8),
            kRenderBufferColor5			= (1 << 9),
            kRenderBufferColor6			= (1 << 10),
            kRenderBufferColor7			= (1 << 11)
        };
        
        //! matrixmode
        enum eRenderMatrixMode{
            kRenderMatrixModeModel          = (1 << 1),
            kRenderMatrixModeView			= (1 << 2),
            kRenderMatrixModeProjection     = (1 << 3),
            kRenderMatrixModeCurrent        = 0
        };
        
        //! shademode
        enum eRenderShadeMode{
            kRenderShadeModelSmooth,
            kRenderShadeModelFlat,
            kRenderShadeModelPoint,
            kRenderShadeModelWireframe,
        };
        
        //! texture unit
        enum eTextureUnit{
            kTextureUnit0,
            kTextureUnit1,
            kTextureUnit2,
            kTextureUnit3,
            kMaxTextureUnits,
        };
        
		//! Abstract definition of our render device
		class IRenderDevice{
        public:
            
            //! delegates certain platform specific functions
            class Delegate{
            public:                
                //! the frame has begun
                virtual void frameHasBegun(){}
                //! the frame has ended
                virtual void frameHasEnded(){}
            };
            
        public:
            
			//! Destructor
			virtual ~IRenderDevice(){}
            
        public:
            
            //! set delegate
            virtual void setDelegate(renderdevice::IRenderDevice::Delegate* pRenderDeviceDelegate) = 0;
            
		public:
            
            //! draws with current state
			virtual void draw() = 0;
            //! draws with current state
			virtual void drawElements(uint32_t startIndex, uint32_t numIndices) = 0;
            
			//! starts rendering a frame
            virtual void beginFrame() = 0;
            //! ends rendering a frame
            virtual void endFrame() = 0;
            
			//! returns the width of the frame
			//! \return the width of the frame
			virtual uint32_t getFrameWidth() = 0;
			//! returns the height of the frame
			//! \return the height of the frame
			virtual uint32_t getFrameHeight() = 0;
            
		public:
            
			//! clear frame buffer
			//! \param bufferMask the set of buffers to clear
			virtual void clearBuffer(uint32_t bufferMask) = 0;
            //! sets our clear color
            //! \param r the red component
            //! \param g the green component
            //! \param b the blue component
            //! \param a the alpha component
			virtual void setClearColor(float r, float g, float b, float a) = 0;
            
		public:

            //! Fill mode functions
            //! \param face the face to set fill mode
            //! \param mode the fill mode
            virtual void setFillMode(renderdevice::eRenderFace face, renderdevice::eRenderFillMode mode) = 0;
            
            //! Depth functions
            //! \param func the depth compare mode
            virtual void setDepthFunc(renderdevice::eRenderDepthFunc func) = 0;
            //! Stencil functions
            //! \param func the stencil compare mode
			//! \param ref the value to compare with
			//! \param mask the mask to apply before comparison
            virtual void setStencilFunc(renderdevice::eRenderStencilFunc func, int32_t ref, uint32_t mask) = 0;
			//! Stencil operation
            //! \param sfail action taken when stencil pass fails
			//! \param dfail action taken when depth pass fails
			//! \param pass action taken when stencil and depth pass succeed
            virtual void setStencilOp(renderdevice::eRenderStencilOp sfail, renderdevice::eRenderStencilOp dfail, renderdevice::eRenderStencilOp pass) = 0;
			//! Stencil operation
            //! \param mask stencil write mask
            virtual void setStencilMask(uint32_t mask) = 0;
            //! Cull functions
            //! \param face the face to cull
            virtual void setCullFace(renderdevice::eRenderCullFace face) = 0;
            //! Front face orientation function
            //! \param orientation the face orientation
            virtual void setFrontFaceOrientation(renderdevice::eRenderOrientation orientation) = 0;
            //! Blend function
            //! \param srcScaler the src scaler component
            //! \param destScaler the dest scaler component
            virtual void setBlendFunc(renderdevice::eRenderBlendFactor srcScaler, renderdevice::eRenderBlendFactor destScaler) = 0;
            
            //! Enable function
            //! \param enables a state
            virtual void enableState(renderdevice::eRenderState state) = 0;
            //! Disable function
            //! \param disables a state
            virtual void disableState(renderdevice::eRenderState state) = 0;
            
            //! sets viewport
			//! \param x the viewport x coordinate
			//! \param y the viewport y coordinate
			//! \param width the viewport width
			//! \param height the viewport height
			virtual void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
            
		public:
            
			//! sets our projection matrix
			virtual void setProjectionMatrix(nimble::math::Matrix4x4f const &matrix) = 0;
			//! sets our view matrix
			virtual void setViewMatrix(nimble::math::Matrix4x4f const &matrix) = 0;

			//! sets matrix
			//! \param matrix the matrix data
			virtual void setMatrix(nimble::math::Matrix4x4f const &matrix) = 0;
			//! gets matrix
			//! \param matrixMode the matrix mode we are interested in
			//! \return the matrix associated with the matrix mode
			virtual nimble::math::Matrix4x4f getMatrix(eRenderMatrixMode matrixMode) const = 0;
            
			//! push matrix onto the matrix stack
			virtual void pushMatrix() = 0;
			//! pop matrix onto the matrix stack
			virtual void popMatrix() = 0;
			//! clears all matrices including stack
			virtual void clearMatrix() = 0;
            
            //! sets matrix mode
			//! \param mode the matrix mode to set
			virtual void setMatrixMode(eRenderMatrixMode mode) = 0;
			//! gets matrix mode
			//! \return the matrix mode
			virtual eRenderMatrixMode getMatrixMode() const = 0;
			//! pushes matrix mode
			virtual void pushMatrixMode() = 0;
			//! pops matrix mode
			virtual void popMatrixMode() = 0;
            
        public:
            
			//! sets vertex array
			//! \param pVertexBuffer the vertex array to bind
            //! \param force force sets the vertex buffer
			virtual void bindVertexBuffer(renderdevice::IVertexBuffer *pVertexBuffer) = 0;
			//! sets index array
			//! \param pIndexBuffer the index array to bind
            //! \param force force sets the index buffer
			virtual void bindIndexBuffer(renderdevice::IIndexBuffer *pIndexBuffer) = 0;
            //! sets texture
			//! \param textureUnit the index of the texture
			//! \param pTexture the texture data
            //! \param force force sets the texture
			//! \return true if successful
			virtual void bindTexture(uint32_t textureUnit, renderdevice::ITexture *pTexture) = 0;
			//! sets frame buffer
			//! \param pFrameBuffer the frame buffer
            //! \param force force sets the frame buffer
			//! \return true if successful
			virtual void bindFrameBuffer(renderdevice::IFrameBuffer *pFrameBuffer) = 0;
            //! sets a program
            //! \param pShaderProgram the program
            //! \return true if successful
            virtual void bindShaderProgram(renderdevice::IShaderProgram *pShaderProgram) = 0;
            
        public:
            
            //! creates a frame buffer
            //! \param descriptor the frame buffer's descriptor
            //! \return a frame buffer
            virtual renderdevice::IFrameBuffer* createFrameBuffer(uint32_t width, uint32_t height, uint32_t flags = 0) = 0;
            
            //! creates a vertex array
            //! \param format the vertex format
            //! \param numVertices the number of vertices in this buffer
            //! \param usage the usage hints for this buffer
            //! \return a vertex array
            virtual renderdevice::IVertexBuffer* createVertexBuffer(renderdevice::VertexFormat const &format,
                                                                    uint32_t numVertices,
                                                                    uint32_t usage) = 0;
            //! creates a index array
            //! \param primitiveType the primitive type
            //! \param indexType the index type
            //! \param numindices the number of indices in this buffer
            //! \param usage the usage hints for this buffer
            //! \return a index array
            virtual renderdevice::IIndexBuffer* createIndexBuffer(renderdevice::ePrimitiveType primitiveType,
                                                                  renderdevice::eIndexType indexType,
                                                                  uint32_t numIndices,
                                                                  uint32_t usage) = 0;
            //! creates a texture
            //! \param width the width of the texture
            //! \param height the height of the texture
            //! \param format the format of the texture
            //! \param usage the usage hints for this texture
            //! \return a texture
            virtual renderdevice::ITexture* createTexture(uint32_t width,
                                                          uint32_t height,
                                                          renderdevice::eTextureFormat format,
                                                          uint32_t usage) = 0;
            //! creates a texture from an image
            //! \param image the image to create from
            //! \param format the format of the texture
            //! \param usage the usage hints for this texture
            //! \return a texture
            virtual renderdevice::ITexture* createTextureFromImage(image::Image &image,
                                                                   uint32_t usage) = 0;
            //! creates a shader
            //! \param type the shader type
            //! \return a shader
            virtual renderdevice::IShader* createShader(renderdevice::eShaderType type) = 0;
            //! creates a shader program
            //! \return a shader program
            virtual renderdevice::IShaderProgram* createShaderProgram() = 0;
		};
	};
};

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////
