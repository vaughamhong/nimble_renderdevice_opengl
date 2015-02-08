//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_core_debugheap_h__
#define __nimble_core_debugheap_h__

//////////////////////////////////////////////////////////////////////////

#include <stdint.h>
#include <cstdlib>
#include <nimble/core/assert.h>

//////////////////////////////////////////////////////////////////////////

namespace nimble{
namespace core{
    class IAllocator;
    
    template <typename T>
    class DebugHeap
    : public T{
    private:
        
        //! holds allocation information
        struct header_t{
            int32_t             magic;
            size_t              size;
            core::IAllocator  *pAllocator;
        };
        static const int32_t kMagicValue = 0xdeadbeef;
        
    public:
        
        //! Constructor
        DebugHeap(){
        }
        //! Destructor
        virtual ~DebugHeap(){
        }
        
    public:
        
        //! allocates memory - alignment must be suitable for any data type
        //! \return a pointer to the allocated memory
        virtual void* allocate(size_t size){
            // allocate enough space including our header
            size_t actualSize = size + sizeof(header_t);
            void *pAllocation = T::allocate(actualSize);
            
            // fill our header
            header_t *pHeader = (header_t*)pAllocation;
            pHeader->magic = kMagicValue;
            pHeader->size = actualSize;
            pHeader->pAllocator = dynamic_cast<core::IAllocator*>(this);
            
            // return offset to our user memory
            return (void*)((char*)pAllocation + sizeof(header_t));
        }
        //! deallocates memory
        virtual void deallocate(void* pAllocation){
            void *pActualAllocation = ((char*)pAllocation - sizeof(header_t));
            header_t *pHeader = (header_t*)pActualAllocation;
            core::assert_error(pHeader->magic == kMagicValue);
            core::assert_error(pHeader->pAllocator == dynamic_cast<core::IAllocator*>(this));
            T::deallocate(pActualAllocation);
        }
    };
};};

#endif

//////////////////////////////////////////////////////////////////////////