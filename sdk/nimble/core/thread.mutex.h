//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_core_mutex__
#define __nimble_core_mutex__

//////////////////////////////////////////////////////////////////////////

#if defined(NIMBLE_TARGET_WIN32)
    #include <nimble/core/platform/win32/thread.mutex.h>
#elif defined(NIMBLE_TARGET_OSX)
    #include <nimble/core/platform/osx/thread.mutex.h>
#elif defined(NIMBLE_TARGET_ANDROID)
    #include <nimble/core/platform/android/thread.mutex.h>
#else
    #pragma message("Nimble mutex not implemented on this platform")
#endif

//////////////////////////////////////////////////////////////////////////

namespace nimble{
namespace core{
	
	//! scoped mutex
    class ScopedLock{
    private:
        
        core::Mutex *m_pLock;
        
    public:
        
        //! Constructor
        ScopedLock(core::Mutex *pLock);
        //! Destructor
        virtual ~ScopedLock();
    };
};};

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////