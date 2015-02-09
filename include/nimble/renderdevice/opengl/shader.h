//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_renderdevice_opengl_shader__
#define __nimble_renderdevice_opengl_shader__

//////////////////////////////////////////////////////////////////////////

#include <nimble/renderdevice/opengl/common.h>
#include <nimble/renderdevice/ishader.h>
#include <nimble/resource/resource.h>

//////////////////////////////////////////////////////////////////////////

namespace nimble{
	namespace renderdevice{
        namespace opengl{
            class RenderDevice;
            class ShaderProgram;
            
            //! Shader resource
            class Shader
            : public renderdevice::IShader
            , public resource::Resource{
            friend class nimble::renderdevice::opengl::RenderDevice;
            private:
                
                GLuint                      m_shaderHandle;
                renderdevice::eShaderType   m_type;
                
            public:
                
                //! Constructor
                Shader(renderdevice::eShaderType type);
                //! Destructor
                virtual ~Shader();
                
            public:
                
                //! Get shader type
                virtual eShaderType getShaderType() const;
                //! compiles the shader with source data
                //! \param data the data to copy
                virtual bool compileWithSource(const char *pData);
                
            public:
                
                //! Returns the shader handle
                GLuint getShaderHandle() const;
            };
        };
	};
};

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////