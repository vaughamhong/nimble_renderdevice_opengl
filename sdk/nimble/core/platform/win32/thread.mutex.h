//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_core_win32_mutex__
#define __nimble_core_win32_mutex__

//////////////////////////////////////////////////////////////////////////

#include <stdint.h>
#include <Windows.h>

//////////////////////////////////////////////////////////////////////////

namespace nimble{
namespace core{
    class Condition;
    
    //! pthread mutex interface
    class Mutex{
    friend class Condition;
    private:
        
		CRITICAL_SECTION m_lock;
        
    public:
        
        //! Constructor
        Mutex();
        //! Destructor
        virtual ~Mutex();
        
    public:
        
        //! locks with this mutex
        virtual void lock();
		//! tries to lock with this mutex
		virtual bool tryLock();
        //! unlocks with this mutex
        virtual void unlock();
    };
};};

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////