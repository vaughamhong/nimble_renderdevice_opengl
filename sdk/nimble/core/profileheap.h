//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_core_profileheap_h__
#define __nimble_core_profileheap_h__

//////////////////////////////////////////////////////////////////////////

#include <stdint.h>
#include <cstdlib>
#include <nimble/core/thread.mutex.h>
#include <nimble/core/timer.h>

//////////////////////////////////////////////////////////////////////////

namespace nimble{
namespace core{
    
    template <typename T>
    class ProfileHeap
    : public T{
    private:
        
        uint32_t m_numAllocations;
        double m_totalAllocationTime;
        core::Timer m_allocationTimer;
        
        uint32_t m_numDeallocations;
        double m_totalDeallocationTime;
        core::Timer m_deallocationTimer;
        
    public:
        
        //! Constructor
        ProfileHeap(){
            m_numAllocations = 0;
            m_totalAllocationTime = 0.0f;
            m_numDeallocations = 0;
            m_totalDeallocationTime = 0.0f;
        }
        //! Destructor
        virtual ~ProfileHeap(){
        }
        
    public:
        
        //! allocates memory - alignment must be suitable for any data type
        //! \return a pointer to the allocated memory
        virtual void* allocate(size_t size){
            m_allocationTimer.reset();
            void* pAllocation = T::allocate(size);
            double elapsedTime = m_allocationTimer.getElapsedTimeInMilliSeconds();
            m_numAllocations += 1;
            m_totalAllocationTime += elapsedTime;
            return pAllocation;
        }
        //! deallocates memory
        virtual void deallocate(void* pAllocation){
            m_deallocationTimer.reset();
            T::deallocate(pAllocation);
            double elapsedTime = m_deallocationTimer.getElapsedTimeInMilliSeconds();
            m_numDeallocations += 1;
            m_totalDeallocationTime += elapsedTime;
        }
    };
};};

#endif

//////////////////////////////////////////////////////////////////////////