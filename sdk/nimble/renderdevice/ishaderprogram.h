//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_renderdevice_ishaderprogram_h__
#define __nimble_renderdevice_ishaderprogram_h__

//////////////////////////////////////////////////////////////////////////

#include <stdint.h>
#include <cstdlib>
#include <nimble/renderdevice/shaderparam.h>

//////////////////////////////////////////////////////////////////////////

namespace nimble{
	namespace renderdevice{
        class IShader;
        class IShaderParam;
        class IShaderParamBlock;
        
		//! Abstract shader program
		class IShaderProgram{
		public:
            
            //! Constructor
            IShaderProgram(){}
			//! Destructor
			virtual ~IShaderProgram(){}
            
        public:
            
            //! gets the shader program's sort index
            virtual uint32_t getSortIndex() const = 0;
            
        public:
            
            //! compiles this program
            //! \param[in] pVertexShader the vertex shader to compile
            //! \param[in] pPixelShader the pixel shader to compile
            virtual void compile(renderdevice::IShader *pVertexShader, renderdevice::IShader *pPixelShader) = 0;
            
        public:
            
            //! Returns true if param with name exists
            //! \return true if param with name exists
            virtual bool existsParamWithName(const char *name) const = 0;
            //! Returns the shader parameter by name
            //! \param[in] name the name of the parameter to retreive
            //! \return returns the shader parameter
            virtual renderdevice::IShaderParam const* getShaderParamByName(const char *name) const = 0;
            //! Returns the shader param block for this program
            //! \return the shader param block for this program
            virtual renderdevice::IShaderParamBlock* createShaderParamBlock(const char *names[] = 0, size_t numNames = 0) = 0;

        public:
            
            //! Sets a shader parameter by name
            //! \param[in] name the name of the shader parameter to set
            //! \param[in] pData the data to set the shader parameter
            virtual void setShaderParamByName(const char *name, void* pData) = 0;
            //! Sets a shader parameter block
            //! \param[in] pBlock the shader parameter block to set
            virtual void setShaderParamBlock(renderdevice::IShaderParamBlock const &block) = 0;
		};
	};
};

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////