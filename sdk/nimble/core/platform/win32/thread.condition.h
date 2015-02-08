//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_core_win32_condition__
#define __nimble_core_win32_condition__

//////////////////////////////////////////////////////////////////////////

#include <stdint.h>
#include <nimble/core/thread.mutex.h>
#include <Windows.h>

//////////////////////////////////////////////////////////////////////////

namespace nimble{
namespace core{
    
    //! pthread semaphore interface
    class Condition{
    private:
        
		CONDITION_VARIABLE m_condition;
        
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