//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_core_defines_h__
#define __nimble_core_defines_h__

//////////////////////////////////////////////////////////////////////////

// defines import / export visibility
// DLL (dynamic linked library) should be built with NIMBLE_BUILDING_DLL (which will define exports)
// libraries that use the DLL should exclude NIMBLE_BUILDING_DLL (which will define imports)
#if defined(NIMBLE_TARGET_WIN32)
    #if defined(NIMBLE_BUILDING_DLL)
        #define NIMBLE_DLL_PUBLIC __declspec(dllexport)
    #else
        #define NIMBLE_DLL_PUBLIC __declspec(dllimport)
    #endif
#else
    #define NIMBLE_DLL_PUBLIC
#endif

// defines alignment
#if defined(NIMBLE_TARGET_WIN32)
    #define NIMBLE_ALIGN16 __declspec(align(16))
#else
    #define NIMBLE_ALIGN16 __declspec(align(16))
#endif

// defines inline
#if defined(NIMBLE_TARGET_WIN32)
    #define NIMBLE_INLINE       inline
    #define NIMBLE_FORCE_INLINE __forceinline
#else
    #define NIMBLE_INLINE       inline
    #define NIMBLE_FORCE_INLINE __forceinline
#endif

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////