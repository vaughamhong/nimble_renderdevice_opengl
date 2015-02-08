//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_core_smallblockallocator_h__
#define __nimble_core_smallblockallocator_h__

//////////////////////////////////////////////////////////////////////////

#include <stdint.h>
#include <nimble/core/iallocator.h>

//////////////////////////////////////////////////////////////////////////

// TODO: implement small block allocator

//////////////////////////////////////////////////////////////////////////

namespace nimble{
namespace core{
    
    //! Memory operations
    class SmallBlockAllocator
    : public core::IAllocator{
    public:
        
        //! Constructor
        SmallBlockAllocator();
        //! Destructor
        virtual ~SmallBlockAllocator();
        
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