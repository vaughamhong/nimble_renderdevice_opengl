//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#include <renderdevice.h>
#include <framebuffer.h>
#include <shaderprogram.h>
#include <vertexbuffer.h>
#include <indexbuffer.h>
#include <texture.h>
#include <mappings.h>
#include <nimble/core/assert.h>

//////////////////////////////////////////////////////////////////////////

using namespace nimble;
using namespace nimble::renderdevice::opengl;

//////////////////////////////////////////////////////////////////////////

//! sets frame buffer
//! \param pFrameBuffer the frame buffer
//! \return true if successful
void RenderDevice::bindFrameBuffer(renderdevice::IFrameBuffer* pFrameBuffer){
    // bind null frame (default) framebuffer
    if(!pFrameBuffer){
		GLDEBUG(glBindFramebuffer(GL_FRAMEBUFFER, 0));
        return;
    }
    
    // bind native frame buffer
    renderdevice::opengl::FrameBuffer* pNativeFrameBuffer = dynamic_cast<renderdevice::opengl::FrameBuffer*>(pFrameBuffer);
    if(pNativeFrameBuffer == 0){
        core::logger_error("graphics", "Failed to bind frame buffer - invalid native frame buffer");
        return;
    }
    
    // bind our frame buffer
    m_context.m_pFrameBuffer = pFrameBuffer;
    GLDEBUG(glBindFramebuffer(GL_FRAMEBUFFER, pNativeFrameBuffer->getFrameBufferHandle()));
}

//////////////////////////////////////////////////////////////////////////

//! sets index array
//! \param pIndexBuffer the index array to bind
void RenderDevice::bindIndexBuffer(renderdevice::IIndexBuffer* pIndexBuffer){
    // make sure index buffer is valid
    if(!pIndexBuffer){
        core::logger_warning("graphics", "Failed to bind index buffer - invalid input");
        return;
    }
    //! make sure we have a valid native index buffer
    renderdevice::opengl::IndexBuffer* pNativeIndexBuffer = dynamic_cast<renderdevice::opengl::IndexBuffer*>(pIndexBuffer);
    if(!pNativeIndexBuffer){
        core::logger_error("graphics", "Failed to bind index buffer - invalid native index buffer");
        return;
    }
    
    // early exit if already bound
    if(m_context.m_pIndexBuffer == pIndexBuffer){
        return;
    }

    // bind our array buffer
    m_context.m_pIndexBuffer = pIndexBuffer;
    GLDEBUG(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pNativeIndexBuffer->getArrayBufferHandle()));
}

//! sets vertex array
//! \param pVertexBuffer the vertex array to bind
void RenderDevice::bindVertexBuffer(renderdevice::IVertexBuffer* pVertexBuffer){
    // make sure vertex buffer is valid
    if(!pVertexBuffer){
        core::logger_warning("graphics", "Failed to bind vertex buffer - invalid input");
        return;
    }
    // make sure we have a valid native vertex buffer
    renderdevice::opengl::VertexBuffer* pNativeVertexBuffer = dynamic_cast<renderdevice::opengl::VertexBuffer*>(pVertexBuffer);
    if(!pNativeVertexBuffer){
        core::logger_warning("graphics", "Failed to bind vertex buffer - invalid native vertex buffer");
        return;
    }
    // make sure we have a shader program
    if(!m_context.m_pShaderProgram){
        core::logger_warning("graphics", "Failed to bind vertex buffer - no shader program to bind to");
        return;
    }
    // make sure we have a valid native shader program
    renderdevice::opengl::ShaderProgram *pNativeShaderProgram = dynamic_cast<renderdevice::opengl::ShaderProgram*>(m_context.m_pShaderProgram);
    if(!pNativeShaderProgram){
        core::logger_warning("graphics", "Failed to bind vertex buffer - invalid native shader program");
        return;
    }
    
    // early exit if already bound
    if(m_context.m_pVertexBuffer == pVertexBuffer){
        return;
    }
    
    // bind our array buffer
    m_context.m_pVertexBuffer = pVertexBuffer;
    GLDEBUG(glBindBuffer(GL_ARRAY_BUFFER, pNativeVertexBuffer->getArrayBufferHandle()));
    // grab our program handle
    GLuint programHandle = pNativeShaderProgram->m_programHandle;
    
    // grab our vertex format
    const renderdevice::VertexFormat &vertexFormat = pVertexBuffer->getVertexFormat();
    assert(vertexFormat.getVertexStride() > 0);
    
    // attach each vertex attribute
    unsigned int numAttributes = vertexFormat.getNumAttributes();
    unsigned int vertexStride = vertexFormat.getVertexStride();
    for(unsigned int i = 0; i < numAttributes; ++i){
        // attribute information
        const char *name = vertexFormat.getAttributeName(i);
        renderdevice::VertexFormat::eAttributeType vertexType = vertexFormat.getAttributeType(i);
        
        // gl attribute information
        GLenum type = gVertexAttributeTypeMap[vertexType];
        unsigned int dimension = gVertexAttributeTypeDimensionMap[vertexType];
        GLint attributeHandle = GLDEBUG(glGetAttribLocation(programHandle, name));
        GLboolean normalize = vertexFormat.getAttributeNormalize(i) ? GL_TRUE : GL_FALSE;
        size_t offset = vertexFormat.getAttributeByteOffset(i);
        
        // bind attribute
        if(attributeHandle >= 0){
            GLDEBUG(glEnableVertexAttribArray(attributeHandle));
            GLDEBUG(glVertexAttribPointer(attributeHandle, dimension, type, normalize, vertexStride, (const GLvoid*)offset));
        }
    }
}

//////////////////////////////////////////////////////////////////////////

//! sets texture
//! \param textureUnit the index of the texture unit to replace
//! \param pTexture the texture data
void RenderDevice::bindTexture(uint32_t textureUnit, renderdevice::ITexture* pTexture){
    //  make sure we have a valid shader program to bind to
	if(!m_context.m_pShaderProgram){
        core::logger_warning("graphics", "No shader program to bind to");
        return;
    }
    // unbind if null texture
    renderdevice::opengl::Texture *pNativeTexture = dynamic_cast<renderdevice::opengl::Texture*>(pTexture);
    if(pNativeTexture == 0){
        unsigned int internalTextureUnit = gTextureUnitMap[textureUnit];
        GLDEBUG(glActiveTexture(internalTextureUnit));
        GLDEBUG(glDisable(GL_TEXTURE_2D));
        return;
    }

    // bind texture
    unsigned int dimension  = gTextureDimensionMap[pNativeTexture->getDimension()];
    unsigned int internalTextureUnit = gTextureUnitMap[textureUnit];
    GLuint handle = pNativeTexture->getTextureHandle();
    m_context.m_textures[textureUnit] = pTexture;
    m_context.m_currentTextureUnitIndex = textureUnit;
    GLDEBUG(glActiveTexture(internalTextureUnit));
    GLDEBUG(glEnable(dimension));
    GLDEBUG(glBindTexture(dimension, handle));
}

//////////////////////////////////////////////////////////////////////////

//! sets a program
//! \param pShaderProgram the program
//! \return true if successful
void RenderDevice::bindShaderProgram(renderdevice::IShaderProgram* pShaderProgram){
    // invalidate bound vertex / index buffers
    m_context.m_pVertexBuffer = 0;
    m_context.m_pIndexBuffer = 0;

    // early exit if already bound
    if(m_context.m_pShaderProgram == pShaderProgram){
        return;
    }
    // unbinding shader program
    if(pShaderProgram == 0){
        GLDEBUG(glUseProgram(0));
    }
    
    // update our internal context state
    m_context.m_pShaderProgram = pShaderProgram;

    // make sure we have a valid native shader program
    renderdevice::opengl::ShaderProgram *pNativeShaderProgram = dynamic_cast<renderdevice::opengl::ShaderProgram*>(pShaderProgram);
    if(!pNativeShaderProgram){
        return;
    }

    // bind shader program
    GLint shaderProgramHandle = pNativeShaderProgram->getShaderProgramHandle();
    GLDEBUG(glUseProgram(shaderProgramHandle));
    
    // track which matrix params this program will need filling
    #define SHADERPARAM_TUPLE(NAME, SHADERNAME) \
        m_context.m_shaderHas##NAME##ShaderParam = pNativeShaderProgram->existsParamWithName(SHADERNAME); \
        m_context.m_final##NAME##MatrixChanged = true;
        SHADERPARAM_TUPLESET
    #undef SHADERPARAM_TUPLE
}

//////////////////////////////////////////////////////////////////////////