//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_renderdevice_opengl_shaderparam_h__
#define __nimble_renderdevice_opengl_shaderparam_h__

//////////////////////////////////////////////////////////////////////////

#include <nimble/renderdevice/opengl/common.h>
#include <nimble/renderdevice/shaderparam.h>
#include <string>

//////////////////////////////////////////////////////////////////////////

namespace nimble{
	namespace renderdevice{
        namespace opengl{

            //! shader parameter
            class ShaderParam
            : public renderdevice::ShaderParam{
            private:
                
                GLint m_handle;
                GLint m_textureUnit;
                
            public:
                
                //! Constructor
                ShaderParam();
                //! Constructor
                ShaderParam(const char *name, renderdevice::eShaderParamType type, void *pData, GLint handle, GLint textureUnit = -1);
                //! Constructor
                ShaderParam(renderdevice::opengl::ShaderParam const &param);
                //! Destructor
                virtual ~ShaderParam();
                
            public:
                
                //! Returns the shader handle
                GLint getHandle() const;
                //! Returns the texture unit
                GLint getTextureUnit() const;
            };
            
            //! maps opengl uniform types to internal types
            renderdevice::eShaderParamType mapGLUniformTypeToInternalType(GLenum uniformType);
        };
	};
};

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////