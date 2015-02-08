//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_core_threadsafeheap_h__
#define __nimble_core_threadsafeheap_h__

//////////////////////////////////////////////////////////////////////////

#include <stdint.h>
#include <cstdlib>
#include <nimble/core/thread.mutex.h>

//////////////////////////////////////////////////////////////////////////

namespace nimble{
namespace core{
    
    template <typename T>
    class ThreadSafeHeap
    : public T{
    private:
        
        mutable core::Mutex m_lock;
        
    public:
        
        //! Constructor
        ThreadSafeHeap(){
        }
        //! Destructor
        virtual ~ThreadSafeHeap(){
        }
        
    public:
        
        //! allocates memory - alignment must be suitable for any data type
        //! \return a pointer to the allocated memory
        virtual void* allocate(size_t size){
            core::ScopedLock lock(&m_lock);
            return T::allocate(size);
        }
        //! deallocates memory
        virtual void deallocate(void* pAllocation){
            core::ScopedLock lock(&m_lock);
            T::deallocate(pAllocation);
        }
    };
};};

#endif

//////////////////////////////////////////////////////////////////////////