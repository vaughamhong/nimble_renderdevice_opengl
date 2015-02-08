//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_renderdevice_ishaderparamblock_h__
#define __nimble_renderdevice_ishaderparamblock_h__

//////////////////////////////////////////////////////////////////////////

#include <cstdlib>

//////////////////////////////////////////////////////////////////////////

namespace nimble{
	namespace renderdevice{
        class IShaderParam;
        
        //! Abstract param block
        class IShaderParamBlock{
        public:
            
            //! Constructor
            IShaderParamBlock(){}
            //! Destructor
            virtual ~IShaderParamBlock(){}
            
        public:
            
            //! Returns the number of parameters
            virtual size_t getNumShaderParams() const = 0;
            
            //! Returns true if param with name exists
            //! \return true if param with name exists
            virtual bool existsParamWithName(const char *name) const = 0;
            
            //! Returns the shader param by index
            virtual renderdevice::IShaderParam const* getShaderParamByIndex(size_t index) const = 0;
            //! Returns the shader param by name
            virtual renderdevice::IShaderParam const* getShaderParamByName(const char *name) const = 0;
            
            //! Sets shader param by index
            virtual void setShaderParamByIndex(size_t index, void *pData) = 0;
            //! Sets shader param by name
            virtual void setShaderParamByName(const char *name, void *pData) = 0;
            
            //! Adds a shader param
            virtual void addShaderParam(renderdevice::IShaderParam const &param) = 0;
            
            //! Clears all parameters
            virtual void clear() = 0;
        };
	};
};

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////