//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_renderdevice_iarraybuffer_h__
#define __nimble_renderdevice_iarraybuffer_h__

//////////////////////////////////////////////////////////////////////////

#include <stdint.h>

//////////////////////////////////////////////////////////////////////////

namespace nimble{
	namespace renderdevice{

        //! Usage flags
        enum eArrayUsage{
            kArrayUsageStatic       = (1 << 1),
            kArrayUsageDynamic      = (1 << 2),
            kArrayUsageVolitile     = (1 << 3),
            kMaxArrayUsageTypes     = 3,
        };

        //! An abstract interface representing a hardware buffer
        class IArrayBuffer{
        public:
            
            //! Destructor
			virtual ~IArrayBuffer(){}
            
        public:
            
            //! returns the usage of this array
			//! \return the usage of this array
			virtual uint32_t getUsage() const = 0;
            //! returns the number of elements in this array
			//! \return the number of elements in this array
			virtual size_t getNumElements() const = 0;
            //! returns the size of the elements in this array
			//! \return the size of the elements in this array
			virtual size_t getElementSize() const = 0;
            //! returns the number of bytes in this array
			//! \return the number of bytes in this array
			virtual size_t getBufferSize() const = 0;
        };
    };
};

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////