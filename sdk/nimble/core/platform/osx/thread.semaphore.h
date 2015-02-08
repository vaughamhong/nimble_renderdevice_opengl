//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_core_osx_semaphore__
#define __nimble_core_osx_semaphore__

//////////////////////////////////////////////////////////////////////////

#include <stdint.h>
#include <semaphore.h>

//////////////////////////////////////////////////////////////////////////

namespace nimble{
namespace core{
    
    //! pthread semaphore interface
    class Semaphore{
    private:
        
        sem_t *m_pSem;
        
    public:
        
        //! Constructor
        Semaphore(const char *name, int32_t value = 1);
        //! Destructor
        virtual ~Semaphore();
        
    public:
        
        //! waits for unlock
        virtual void wait();
        //! signals semaphore unlock
        virtual void post();
    };
};};

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////