//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_renderdevice_ishader_h__
#define __nimble_renderdevice_ishader_h__

//////////////////////////////////////////////////////////////////////////

namespace nimble{
	namespace renderdevice{
        
        //! Shader type
        enum eShaderType{
            kShaderTypeVertex,
            kShaderTypePixel,
        };

        //! An abstract interface representing a hardware shader
		class IShader{
        public:
            
			//! Destructor
			virtual ~IShader(){}
            
        public:
            
            //! Get shader type
            virtual eShaderType getShaderType() const = 0;
			//! Compiles the shader with source data
			//! \param pData the data to compile with
			virtual bool compileWithSource(const char *pData) = 0;
		};
	};
};

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////