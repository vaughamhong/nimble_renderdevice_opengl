//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_core_osx_mutex__
#define __nimble_core_osx_mutex__

//////////////////////////////////////////////////////////////////////////

#include <stdint.h>
#include <pthread.h>

//////////////////////////////////////////////////////////////////////////

namespace nimble{
namespace core{
    class Condition;
    
    //! pthread mutex interface
    class Mutex{
    friend class Condition;
    private:
        
        pthread_mutex_t m_lock;
        
    public:
        
        //! Constructor
        Mutex(bool isRecursive = true);
        //! Destructor
        virtual ~Mutex();
        
    public:
        
        //! locks with this mutex
        virtual void lock();
        //! tries to lock
        virtual bool tryLock();
        //! unlocks with this mutex
        virtual void unlock();
    };
};};

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////