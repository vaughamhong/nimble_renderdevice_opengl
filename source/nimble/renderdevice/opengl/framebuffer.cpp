//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#include <nimble/renderdevice/opengl/framebuffer.h>
#include <nimble/renderdevice/opengl/texture.h>
#include <nimble/core/assert.h>
#include <nimble/core/locator.h>

//////////////////////////////////////////////////////////////////////////

using namespace nimble;
using namespace nimble::renderdevice::opengl;

//////////////////////////////////////////////////////////////////////////

//! a constructor
FrameBuffer::FrameBuffer(uint32_t width, uint32_t height, uint32_t flags)
:m_fboHandle(0)
,m_depthBufferHandle(0)
,m_stencilBufferHandle(0)
,m_width(width)
,m_height(height)
,m_flags(flags){
    memset(m_pBuffers, 0, sizeof(renderdevice::ITexture*) * kMaxFrameBufferTypes);
    
    // set up our frame buffer object
	GLDEBUG(glGenFramebuffers(1, &m_fboHandle));
	GLDEBUG(glBindFramebuffer(GL_FRAMEBUFFER, m_fboHandle));
    
    // set up depth (render buffer) if asked to do so
    if(m_flags & kFrameBufferFlagGenDepth24Stencil8){
        // generate shared depth24 stencil8 render buffer
        GLDEBUG(glGenRenderbuffers(1, &m_depthBufferHandle));
        GLDEBUG(glBindRenderbuffer(GL_RENDERBUFFER, m_depthBufferHandle));
        GLDEBUG(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8_EXT, width, height));
        GLDEBUG(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depthBufferHandle));
        GLDEBUG(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_depthBufferHandle));
    }else{
        // generate appropriate depth buffer
        if(m_flags & kFrameBufferFlagGenDepth16){
            GLDEBUG(glGenRenderbuffers(1, &m_depthBufferHandle));
            GLDEBUG(glBindRenderbuffer(GL_RENDERBUFFER, m_depthBufferHandle));
            GLDEBUG(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, width, height));
            GLDEBUG(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depthBufferHandle));
        }else if(m_flags & kFrameBufferFlagGenDepth24){
            GLDEBUG(glGenRenderbuffers(1, &m_depthBufferHandle));
            GLDEBUG(glBindRenderbuffer(GL_RENDERBUFFER, m_depthBufferHandle));
            GLDEBUG(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, width, height));
            GLDEBUG(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depthBufferHandle));
        }else if(m_flags & kFrameBufferFlagGenDepth32){
            GLDEBUG(glGenRenderbuffers(1, &m_depthBufferHandle));
            GLDEBUG(glBindRenderbuffer(GL_RENDERBUFFER, m_depthBufferHandle));
            GLDEBUG(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT32, width, height));
            GLDEBUG(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depthBufferHandle));
        }
        
        // generate appropriate stencil buffer
        if(m_flags & kFrameBufferFlagGenStencil1){
            GLDEBUG(glGenRenderbuffers(1, &m_stencilBufferHandle));
            GLDEBUG(glBindRenderbuffer(GL_RENDERBUFFER, m_stencilBufferHandle));
            GLDEBUG(glRenderbufferStorage(GL_RENDERBUFFER, GL_STENCIL_INDEX1, width, height));
            GLDEBUG(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_stencilBufferHandle));
        }else if(m_flags & kFrameBufferFlagGenStencil4){
            GLDEBUG(glGenRenderbuffers(1, &m_stencilBufferHandle));
            GLDEBUG(glBindRenderbuffer(GL_RENDERBUFFER, m_stencilBufferHandle));
            GLDEBUG(glRenderbufferStorage(GL_RENDERBUFFER, GL_STENCIL_INDEX4, width, height));
            GLDEBUG(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_stencilBufferHandle));
        }else if(m_flags & kFrameBufferFlagGenStencil8){
            GLDEBUG(glGenRenderbuffers(1, &m_stencilBufferHandle));
            GLDEBUG(glBindRenderbuffer(GL_RENDERBUFFER, m_stencilBufferHandle));
            GLDEBUG(glRenderbufferStorage(GL_RENDERBUFFER, GL_STENCIL_INDEX8, width, height));
            GLDEBUG(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_stencilBufferHandle));
        }else if(m_flags & kFrameBufferFlagGenStencil16){
            GLDEBUG(glGenRenderbuffers(1, &m_stencilBufferHandle));
            GLDEBUG(glBindRenderbuffer(GL_RENDERBUFFER, m_stencilBufferHandle));
            GLDEBUG(glRenderbufferStorage(GL_RENDERBUFFER, GL_STENCIL_INDEX16, width, height));
            GLDEBUG(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_stencilBufferHandle));
        }
    }
}
//! a destructor
FrameBuffer::~FrameBuffer(){
    // clean up render buffers if we need to
    if(m_depthBufferHandle != 0){
        GLDEBUG(glDeleteRenderbuffers(1, &m_depthBufferHandle));
        m_depthBufferHandle = 0;
    }
    if(m_stencilBufferHandle != 0){
        GLDEBUG(glDeleteRenderbuffers(1, &m_stencilBufferHandle));
        m_stencilBufferHandle = 0;
    }
    
    // clean up frame buffer object
	GLDEBUG(glDeleteFramebuffers(1, &m_fboHandle));
}

//////////////////////////////////////////////////////////////////////////

//! returns true if this frame buffer is complete
bool FrameBuffer::isComplete() const{
    // A complete frame buffer must satisfy the following rules
    // + The width and height of framebuffer-attachable image must be not zero.
    // + All images attached a FBO must have the same width and height.
    // + All images attached the color attachment points must have the same internal format.
    // + FBO must have at least one image attached.
    // + Color attachments must have a color-renderable internal format. (eg. GL_RGBA)
    // + Depth attachments must have a depth-renderable internal format. (eg. GL_DEPTH_COMPONENT)
    // + Stencil attachments must have a stencil-renderable internal format. (eg. GL_STENCIL_INDEX)
    // Even though all of the above conditions are satisfied, your OpenGL driver
    // may not support some combinations of internal formats and parameters
    GLenum status = GLDEBUG(glCheckFramebufferStatus(GL_FRAMEBUFFER));
    return status == GL_FRAMEBUFFER_COMPLETE;
}

//////////////////////////////////////////////////////////////////////////

//! attach a texture target
//! \param type the type to attach
//! \param pTexture the texture to attach
void FrameBuffer::attachTextureTarget(renderdevice::eFrameBufferType type, renderdevice::ITexture *pTexture){
    attachTextureTargets(&type, &pTexture, 1);
}
//! detaches a texture target
//! \param type the type to detach
void FrameBuffer::detachTextureTarget(renderdevice::eFrameBufferType type){
    detachTextureTargets(&type, 1);
}
//! attach a set of texture targets
//! \param types the types to attach
//! \param pTextures the textures to attach
//! \param numTargets the number of textures to attach
void FrameBuffer::attachTextureTargets(renderdevice::eFrameBufferType *types, renderdevice::ITexture **pTextures, size_t numTargets){
    // early exit if there are no targets
    if(numTargets == 0){
        return;
    }
    
    // bind buffer if not already done so
    GLint boundHandle;
    GLDEBUG(glGetIntegerv(GL_FRAMEBUFFER_BINDING, &boundHandle));
    if(boundHandle != (GLint)m_fboHandle){
        GLDEBUG(glBindFramebuffer(GL_FRAMEBUFFER, m_fboHandle));
    }
    
    // loop through each texture and attach
    for(size_t i = 0; i < numTargets; i++){
        renderdevice::eFrameBufferType &bufferType = types[i];
        renderdevice::ITexture *pTexture = pTextures[i];
        uint32_t width = pTexture->getWidth();
        uint32_t height = pTexture->getHeight();
        
        // skip binding if texture dimensions are not correct
        if(pTexture->getDimension() != renderdevice::kTextureDimention2D){
            core::logger_warning("renderer", "Failed to attach texture to frame buffer - mismatching dimensions");
            continue;
        }
        if(width != this->getWidth() || height != this->getHeight()){
            core::logger_warning("renderer", "Failed to attach texture to frame buffer - mismatching dimensions");
            continue;
        }
        
        // get our native texture to work with
        renderdevice::opengl::Texture* pNativeTexture = dynamic_cast<renderdevice::opengl::Texture*>(pTexture);
        if(pNativeTexture == 0){
            core::logger_error("graphics", "Failed to attach invalid texture");
            continue;
        }
        
        // bind texture to buffer target
        switch(bufferType){
            case renderdevice::kFrameBufferDepth:{
                GLuint handle = pNativeTexture->getTextureHandle();
                GLDEBUG(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, handle, 0));
                m_pBuffers[bufferType] = pTexture;
                break;
            }
            case renderdevice::kFrameBufferStencil:{
                GLuint handle = pNativeTexture->getTextureHandle();
                GLDEBUG(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_TEXTURE_2D, handle, 0));
                m_pBuffers[bufferType] = pTexture;
                break;
            }
            case renderdevice::kFrameBufferColor0:{
                GLuint handle = pNativeTexture->getTextureHandle();
                GLDEBUG(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, handle, 0));
                m_pBuffers[bufferType] = pTexture;
                break;
            }
            case renderdevice::kFrameBufferColor1:{
                GLuint handle = pNativeTexture->getTextureHandle();
                GLDEBUG(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, handle, 0));
                m_pBuffers[bufferType] = pTexture;
                break;
            }
            case renderdevice::kFrameBufferColor2:{
                GLuint handle = pNativeTexture->getTextureHandle();
                GLDEBUG(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, handle, 0));
                m_pBuffers[bufferType] = pTexture;
                break;
            }
            case renderdevice::kFrameBufferColor3:{
                GLuint handle = pNativeTexture->getTextureHandle();
                GLDEBUG(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT3, GL_TEXTURE_2D, handle, 0));
                m_pBuffers[bufferType] = pTexture;
                break;
            }
            default:{
                core::logger_error("graphics", "Failed to attach texture to invalid target");
            }
        };
    }
    
    // restore previous frame buffer
    if(boundHandle != (GLint)m_fboHandle){
        GLDEBUG(glBindFramebuffer(GL_FRAMEBUFFER, boundHandle));
    }
}
//! detaches a set of texture targets
//! \param types the types to detach
//! \param numTargets the number of textures to detach
void FrameBuffer::detachTextureTargets(renderdevice::eFrameBufferType *types, size_t numTargets){
    // early exit if there are no targets
    if(numTargets == 0){
        return;
    }
    
    // bind buffer if not already done so
    GLint boundHandle;
    GLDEBUG(glGetIntegerv(GL_FRAMEBUFFER_BINDING, &boundHandle));
    if(boundHandle != (GLint)m_fboHandle){
        GLDEBUG(glBindFramebuffer(GL_FRAMEBUFFER, m_fboHandle));
    }
    
    // loop through each type and detach
    for(size_t i = 0; i < numTargets; i++){
        renderdevice::eFrameBufferType &bufferType = types[i];
        
        // unbind
        switch(bufferType){
            case renderdevice::kFrameBufferDepth:{
                GLDEBUG(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, 0, 0));
                break;
            }
            case renderdevice::kFrameBufferColor0:{
                GLDEBUG(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, 0, 0));
                break;
            }
            default:{
                core::logger_error("graphics", "Failed to detach invalid target");
                break;
            }
        }
        
        // remove texture from our context
        m_pBuffers[bufferType] = 0;
    }
    
    // restore previous frame buffer
    if(boundHandle != (GLint)m_fboHandle){
        GLDEBUG(glBindFramebuffer(GL_FRAMEBUFFER, boundHandle));
    }
}
//! sets writable targets
void FrameBuffer::setWriteTargets(uint32_t bufferMask){
    static GLenum targets[renderdevice::kMaxFrameBufferTypes];
    int32_t numTargets = 0;
    if(bufferMask & renderdevice::kFrameBufferDepthBit){targets[numTargets] = GL_DEPTH_ATTACHMENT; numTargets++;}
    if(bufferMask & renderdevice::kFrameBufferStencilBit){targets[numTargets] = GL_STENCIL_ATTACHMENT; numTargets++;}
    if(bufferMask & renderdevice::kFrameBufferAccumulationBit){core::logger_warning("renderer", "Failed to set write target - accumulation buffer");}
    if(bufferMask & renderdevice::kFrameBufferColor0Bit){targets[numTargets] = GL_COLOR_ATTACHMENT0; numTargets++;}
    if(bufferMask & renderdevice::kFrameBufferColor1Bit){targets[numTargets] = GL_COLOR_ATTACHMENT1; numTargets++;}
    if(bufferMask & renderdevice::kFrameBufferColor2Bit){targets[numTargets] = GL_COLOR_ATTACHMENT2; numTargets++;}
    if(bufferMask & renderdevice::kFrameBufferColor3Bit){targets[numTargets] = GL_COLOR_ATTACHMENT3; numTargets++;}
    if(bufferMask & renderdevice::kFrameBufferColor4Bit){targets[numTargets] = GL_COLOR_ATTACHMENT4; numTargets++;}
    if(bufferMask & renderdevice::kFrameBufferColor5Bit){targets[numTargets] = GL_COLOR_ATTACHMENT5; numTargets++;}
    if(bufferMask & renderdevice::kFrameBufferColor6Bit){targets[numTargets] = GL_COLOR_ATTACHMENT6; numTargets++;}
    if(bufferMask & renderdevice::kFrameBufferColor7Bit){targets[numTargets] = GL_COLOR_ATTACHMENT7; numTargets++;}
    
    // bind buffer if not already done so
    GLint boundHandle;
    GLDEBUG(glGetIntegerv(GL_FRAMEBUFFER_BINDING, &boundHandle));
    if(boundHandle != (GLint)m_fboHandle){
        GLDEBUG(glBindFramebuffer(GL_FRAMEBUFFER, m_fboHandle));
    }
    GLDEBUG(glDrawBuffers(numTargets, targets));
    // restore previous frame buffer
    if(boundHandle != (GLint)m_fboHandle){
        GLDEBUG(glBindFramebuffer(GL_FRAMEBUFFER, boundHandle));
    }
}

//////////////////////////////////////////////////////////////////////////

//! returns the render target
renderdevice::ITexture* FrameBuffer::getTarget(renderdevice::eFrameBufferType buffer){
    if(buffer == renderdevice::kFrameBufferDepth){return m_pBuffers[0];}
	if(buffer == renderdevice::kFrameBufferStencil){return m_pBuffers[1];}
	if(buffer == renderdevice::kFrameBufferAccumulation){return m_pBuffers[2];}
    if(buffer == renderdevice::kFrameBufferColor0){return m_pBuffers[3];}
	if(buffer == renderdevice::kFrameBufferColor1){return m_pBuffers[4];}
	if(buffer == renderdevice::kFrameBufferColor2){return m_pBuffers[5];}
	if(buffer == renderdevice::kFrameBufferColor3){return m_pBuffers[6];}
	if(buffer == renderdevice::kFrameBufferColor4){return m_pBuffers[7];}
	if(buffer == renderdevice::kFrameBufferColor5){return m_pBuffers[8];}
	if(buffer == renderdevice::kFrameBufferColor6){return m_pBuffers[9];}
	if(buffer == renderdevice::kFrameBufferColor7){return m_pBuffers[10];}
    return 0;
}
//! returns the width
//! \return the width
unsigned int FrameBuffer::getWidth() const{
    return m_width;
}
//! returns the height
//! \return the height
unsigned int FrameBuffer::getHeight() const{
    return m_height;
}
//! returns the handle
GLuint FrameBuffer::getFrameBufferHandle(){
    return m_fboHandle;
}

//////////////////////////////////////////////////////////////////////////

//! discards depth buffer
void FrameBuffer::discardDepthBuffer(){
}

//////////////////////////////////////////////////////////////////////////