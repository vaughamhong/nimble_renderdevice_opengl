//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_renderdevice_shaderparam_h__
#define __nimble_renderdevice_shaderparam_h__

//////////////////////////////////////////////////////////////////////////

#include <nimble/renderdevice/ishaderparam.h>

//////////////////////////////////////////////////////////////////////////

namespace nimble{
	namespace renderdevice{
        
        //! The maximum shader param name size
        static const int kMaxShaderParamNameSize = 64;
        
        //! Shader parameter
        class ShaderParam
        : public renderdevice::IShaderParam{
        private:
            
            char                            m_name[kMaxShaderParamNameSize];
            renderdevice::eShaderParamType  m_type;
            void                            *m_pData;
            
        public:
            
            //! Constructor
            ShaderParam();
            //! Constructor
            ShaderParam(const char *name, renderdevice::eShaderParamType type, void *pData);
            //! Constructor
            ShaderParam(ShaderParam const &param);
            //! Destructor
            virtual ~ShaderParam();
            
        public:
            
            //! Assignment operator
            ShaderParam& operator=(ShaderParam const &param);
            //! Equivalence operator
            bool operator==(ShaderParam const &param);
            //! Equivalence operator
            bool operator!=(ShaderParam const &param);
            
        public:
            
            //! Returns the name
            virtual const char* getName() const;
            //! Returns the data type
            virtual renderdevice::eShaderParamType getType() const;
            
            //! Returns the value
            virtual void* getData() const;
            //! Sets the value
            virtual void setData(void *pData);
        };
	};
};

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////