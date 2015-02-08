//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_core_osx_condition__
#define __nimble_core_osx_condition__

//////////////////////////////////////////////////////////////////////////

#include <stdint.h>
#include <nimble/core/thread.mutex.h>
#include <pthread.h>

//////////////////////////////////////////////////////////////////////////

namespace nimble{
namespace core{
    
    //! pthread semaphore interface
    class Condition{
    private:
        
        pthread_cond_t m_condition;
        
    public:
        
        //! Constructor
        Condition();
        //! Destructor
        virtual ~Condition();
        
    public:
        
        //! waits for unlock
        virtual void wait(core::Mutex *pMutex);
        //! signals unlock
        virtual void signal();
        //! broadcast unlock
        virtual void broadcast();
    };
};};

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////