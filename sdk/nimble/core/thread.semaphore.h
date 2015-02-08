//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_core_semaphore__
#define __nimble_core_semaphore__

//////////////////////////////////////////////////////////////////////////

#if defined(NIMBLE_TARGET_WIN32)
    #include <nimble/core/platform/win32/thread.semaphore.h>
#elif defined(NIMBLE_TARGET_OSX)
    #include <nimble/core/platform/osx/thread.semaphore.h>
#elif defined(NIMBLE_TARGET_ANDROID)
    #include <nimble/core/platform/android/thread.semaphore.h>
#else
    #pragma message("Nimble semaphore not implemented on this platform")
#endif

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////