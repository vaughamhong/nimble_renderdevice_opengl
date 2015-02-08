//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_core_stackallocator_h__
#define __nimble_core_stackallocator_h__

//////////////////////////////////////////////////////////////////////////

#include <stdint.h>
#include <cstdlib>
#include <nimble/core/iallocator.h>

//////////////////////////////////////////////////////////////////////////

namespace nimble{
namespace core{
    
    //! Fixed sized memory allocator
    template <typename T>
    class StackAllocator
    : public core::IAllocator{
    public:
        
        typedef size_t SizeType;
        
    public:
        
        //! Constructor
        StackAllocator();
        //! Constructor
        StackAllocator(SizeType size);
        //! Destructor
        virtual ~StackAllocator();
        
    public:
        
        //! allocates memory - alignment must be suitable for any data type
        //! \return allocated aligned memory
        virtual void* allocate(size_t size);
        //! deallocates memory
        virtual void deallocate(void* pAllocation);
    };
};};

//////////////////////////////////////////////////////////////////////////

#include <nimble/core/stackallocator.inline.h>

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////