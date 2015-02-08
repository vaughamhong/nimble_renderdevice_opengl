//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_core_iallocator_h__
#define __nimble_core_iallocator_h__

//////////////////////////////////////////////////////////////////////////

#include <stdint.h>
#include <stdio.h>

//////////////////////////////////////////////////////////////////////////

namespace nimble{
namespace core{
    
    //! Abstract allocator
    class IAllocator{
    public:
        
        //! Constructor
        IAllocator(){}
        //! Destructor
        virtual ~IAllocator(){}
        
    public:
        
        //! allocates memory - alignment must be suitable for any data type
        //! \return allocated aligned memory
        virtual void* allocate(size_t size) = 0;
        //! deallocates memory
        virtual void deallocate(void* pAllocation) = 0;
    };
};};

#endif

//////////////////////////////////////////////////////////////////////////