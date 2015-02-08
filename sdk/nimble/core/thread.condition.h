//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_core_condition__
#define __nimble_core_condition__

//////////////////////////////////////////////////////////////////////////

#if defined(NIMBLE_TARGET_WIN32)
    #include <nimble/core/platform/win32/thread.condition.h>
#elif defined(NIMBLE_TARGET_OSX)
    #include <nimble/core/platform/osx/thread.condition.h>
#elif defined(NIMBLE_TARGET_ANDROID)
    #include <nimble/core/platform/android/thread.condition.h>
#else
    #pragma message("Nimble condition not implemented on this platform")
#endif

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////