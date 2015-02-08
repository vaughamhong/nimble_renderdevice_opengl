//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_renderdevice_renderdevice_h__
#define __nimble_renderdevice_renderdevice_h__

//////////////////////////////////////////////////////////////////////////

#include <nimble/renderdevice/irenderdevice.h>
#include <nimble/renderdevice/iframebuffer.h>
#include <nimble/renderdevice/ivertexbuffer.h>
#include <nimble/renderdevice/iindexbuffer.h>
#include <nimble/renderdevice/itexture.h>
#include <nimble/renderdevice/ishader.h>
#include <nimble/renderdevice/ishaderprogram.h>

//////////////////////////////////////////////////////////////////////////

namespace nimble{
    namespace resource{
        class ResourceManager;
    };
	namespace renderdevice{
        class IRenderDevice;
        
        //! returns the global render device
        renderdevice::IRenderDevice* get();
        
        //! creates a frame buffer
        //! \param descriptor the frame buffer's descriptor
        //! \return a frame buffer
        renderdevice::IFrameBuffer* createFrameBuffer(uint32_t width,
                                                      uint32_t height,
                                                      uint32_t flags = 0,
                                                      renderdevice::IRenderDevice *pRenderDevice = 0);
        
        //! Creates a vertex buffer resource
        //! \param format the vertex format
        //! \param numVertices the number of vertices in this buffer
        //! \param usage the usage hints for this buffer
        //! \param pRenderDevice the RenderDevice to create this resource with
        //! \return a VertexBuffer resource
        renderdevice::IVertexBuffer* createVertexBuffer(renderdevice::VertexFormat const &format,
                                                        uint32_t numVertices,
                                                        uint32_t usage,
                                                        renderdevice::IRenderDevice *pRenderDevice = 0);
        
        //! Creates a index buffer resource
        //! \param primitiveType the primitive type
        //! \param indexType the index type
        //! \param numIndices the number of indices in this buffer
        //! \param usage the usage hints for this buffer
        //! \param pRenderDevice the RenderDevice to create this resource from
        //! \return a IndexBuffer resource
        renderdevice::IIndexBuffer* createIndexBuffer(renderdevice::ePrimitiveType primitiveType,
                                                      renderdevice::eIndexType indexType,
                                                      uint32_t numIndices,
                                                      uint32_t usage,
                                                      renderdevice::IRenderDevice *pRenderDevice = 0);
        
        //! Creates a texture resource
        //! \param width the width of the texture
        //! \param height the height of the texture
        //! \param textureFormat the texture format
        //! \param usage the usage hint for this texture
        //! \param pRenderDevice the RenderDevice to create this resource with
        //! \return a Texture resource
        renderdevice::ITexture* createTexture(uint32_t width,
                                              uint32_t height,
                                              renderdevice::eTextureFormat textureFormat,
                                              uint32_t usage,
                                              renderdevice::IRenderDevice *pRenderDevice = 0);
        
        //! Creates a shader resource
        //! \param pRenderDevice the RenderDevice to create this resource with
        //! \return a VertexShader resource
        renderdevice::IShader* createShader(renderdevice::eShaderType type,
                                            renderdevice::IRenderDevice *pRenderDevice = 0);
        //! creates a program
        //! \param pRenderDevice the RenderDevice to create this resource with
        //! \return a program
        renderdevice::IShaderProgram* createShaderProgram(renderdevice::IRenderDevice *pRenderDevice = 0);
	};
};

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////
