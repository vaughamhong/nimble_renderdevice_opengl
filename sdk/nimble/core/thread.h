//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_core_thread__
#define __nimble_core_thread__

//////////////////////////////////////////////////////////////////////////

#include <nimble/core/functor.h>

//////////////////////////////////////////////////////////////////////////

namespace nimble{
    namespace core{
        class IThread;
        const int32_t kMainThreadId = 0;
        
        //! Returns the current threadId
        //! \return the current threadId
        int32_t getCurrentThreadId();
        
        //! Returns the current thread
        //! \return the current thread
        core::IThread* getCurrentThread();
    };
};

//////////////////////////////////////////////////////////////////////////

#if defined(NIMBLE_TARGET_WIN32)
    #include <nimble/core/platform/win32/thread.h>
#elif defined(NIMBLE_TARGET_OSX)
    #include <nimble/core/platform/osx/thread.h>
#elif defined(NIMBLE_TARGET_ANDROID)
    #include <nimble/core/platform/android/thread.h>
#else
    #pragma message("Nimble threads not implemented on this platform")
#endif

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////