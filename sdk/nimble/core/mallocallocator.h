//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_core_mallocallocator_h__
#define __nimble_core_mallocallocator_h__

//////////////////////////////////////////////////////////////////////////

#include <stdint.h>
#include <nimble/core/iallocator.h>

//////////////////////////////////////////////////////////////////////////

namespace nimble{
namespace core{
    
    //! Memory operations
    class MallocAllocator
    : public core::IAllocator{
    public:
        
        //! Constructor
        MallocAllocator();
        //! Destructor
        virtual ~MallocAllocator();
        
    public:
        
        //! allocates memory - alignment must be suitable for any data type
        //! \return allocated aligned memory
        virtual void* allocate(size_t size);
        //! deallocates memory
        virtual void deallocate(void* pAllocation);
    };
};};

#endif

//////////////////////////////////////////////////////////////////////////