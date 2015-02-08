//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_renderdevice_ishaderparam_h__
#define __nimble_renderdevice_ishaderparam_h__

//////////////////////////////////////////////////////////////////////////

namespace nimble{
	namespace renderdevice{
        
        //! shader parameter types
        enum eShaderParamType{
            kTypeFloat1,
            kTypeFloat2,
            kTypeFloat3,
            kTypeFloat4,
            kTypeFloat2x2,
            kTypeFloat2x3,
            kTypeFloat2x4,
            kTypeFloat3x2,
            kTypeFloat3x3,
            kTypeFloat3x4,
            kTypeFloat4x2,
            kTypeFloat4x3,
            kTypeFloat4x4,
            
            kTypeHalf1,
            kTypeHalf2,
            kTypeHalf3,
            kTypeHalf4,
            kTypeHalf2x2,
            kTypeHalf2x3,
            kTypeHalf2x4,
            kTypeHalf3x2,
            kTypeHalf3x3,
            kTypeHalf3x4,
            kTypeHalf4x2,
            kTypeHalf4x3,
            kTypeHalf4x4,
            
            kTypeInt1,
            kTypeInt2,
            kTypeInt3,
            kTypeInt4,
            kTypeInt2x2,
            kTypeInt2x3,
            kTypeInt2x4,
            kTypeInt3x2,
            kTypeInt3x3,
            kTypeInt3x4,
            kTypeInt4x2,
            kTypeInt4x3,
            kTypeInt4x4,
            
            kTypeFixed1,
            kTypeFixed2,
            kTypeFixed3,
            kTypeFixed4,
            kTypeFixed2x2,
            kTypeFixed2x3,
            kTypeFixed2x4,
            kTypeFixed3x2,
            kTypeFixed3x3,
            kTypeFixed3x4,
            kTypeFixed4x2,
            kTypeFixed4x3,
            kTypeFixed4x4,
            
            kTypeBool1,
            kTypeBool2,
            kTypeBool3,
            kTypeBool4,
            kTypeBool2x2,
            kTypeBool2x3,
            kTypeBool2x4,
            kTypeBool3x2,
            kTypeBool3x3,
            kTypeBool3x4,
            kTypeBool4x2,
            kTypeBool4x3,
            kTypeBool4x4,
            
            kTypeTexture2D,
            kTypeTexture3D,
            
            kMaxAttributeTypes,
            kTypeNull,
        };
        
        //! Abstract shader parameter
        class IShaderParam{
        public:

            //! Constructor
            IShaderParam(){}
            //! Destructor
            virtual ~IShaderParam(){}
            
        public:
            
            //! Returns the name
            virtual const char* getName() const = 0;
            //! Returns the data type
            virtual renderdevice::eShaderParamType getType() const = 0;
            
            //! Returns the value
            virtual void* getData() const = 0;
            //! Sets the value
            virtual void setData(void *pData) = 0;
        };
	};
};

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////