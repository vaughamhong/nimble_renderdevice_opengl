//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#include <nimble/renderdevice/opengl/renderdevice.h>
#include <nimble/renderdevice/opengl/framebuffer.h>
#include <nimble/renderdevice/opengl/vertexbuffer.h>
#include <nimble/renderdevice/opengl/indexbuffer.h>
#include <nimble/renderdevice/opengl/texture.h>
#include <nimble/renderdevice/opengl/shader.h>
#include <nimble/renderdevice/opengl/shaderprogram.h>

//////////////////////////////////////////////////////////////////////////

using namespace nimble;
using namespace nimble::renderdevice::opengl;

//////////////////////////////////////////////////////////////////////////

//! creates a frame buffer
//! \param width the width of the frame buffer
//! \param height the height of the frame buffer
//! \return a frame buffer
renderdevice::IFrameBuffer* RenderDevice::createFrameBuffer(uint32_t width, uint32_t height, uint32_t flags){
    return new renderdevice::opengl::FrameBuffer(width, height, flags);
}
//! creates a vertex array
//! \param format the vertex format
//! \param numVertices the number of vertices in this buffer
//! \param usage the usage hints for this buffer
//! \return a vertex array
renderdevice::IVertexBuffer* RenderDevice::createVertexBuffer(renderdevice::VertexFormat const &vertexFormat, uint32_t numVertices, uint32_t usage){
    return new renderdevice::opengl::VertexBuffer(vertexFormat, numVertices, usage);
}
//! creates a index array
//! \param primitiveType the primitive type
//! \param indexType the index type
//! \param numindices the number of indices in this buffer
//! \param usage the usage hints for this buffer
//! \return a index array
renderdevice::IIndexBuffer* RenderDevice::createIndexBuffer(renderdevice::ePrimitiveType primitiveType, renderdevice::eIndexType indexType, uint32_t numIndices, uint32_t usage){
    return new renderdevice::opengl::IndexBuffer(primitiveType, indexType, numIndices, usage);
}
//! creates a texture
//! \param width the width of the texture
//! \param height the height of the texture
//! \param format the format of the texture
//! \param usage the usage hints for this texture
//! \return a texture
renderdevice::ITexture* RenderDevice::createTexture(uint32_t width, uint32_t height, renderdevice::eTextureFormat format, uint32_t usage){
    return new renderdevice::opengl::Texture(width, height, format, usage);
}
//! creates a texture from an image
//! \param image the image to create from
//! \param format the format of the texture
//! \param usage the usage hints for this texture
//! \return a texture
renderdevice::ITexture* RenderDevice::createTextureFromImage(image::Image &image, uint32_t usage){
    return new renderdevice::opengl::Texture(image, usage);
}
//! creates a shader
//! \param type the shader type
//! \return a shader
renderdevice::IShader* RenderDevice::createShader(renderdevice::eShaderType type){
    return new renderdevice::opengl::Shader(type);
}
//! creates a program
//! \return a program
renderdevice::IShaderProgram* RenderDevice::createShaderProgram(){
    return new renderdevice::opengl::ShaderProgram();
}

//////////////////////////////////////////////////////////////////////////