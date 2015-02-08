//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_core_locator_h__
#define __nimble_core_locator_h__

//////////////////////////////////////////////////////////////////////////

namespace nimble{
namespace core{
    
    //! Gets an object relative to a scope
    template <typename T>
    T* locator_acquire(const char *scope = "");

    //! Sets an object for a scope
    template <typename T>
    void locator_provide(T *pObject, const char *scope = "");

    //! Erases an object for a scope
    template <typename T>
    void locator_release(const char *scope = "");

    //! clears all objects
    template <typename T>
    void locator_clear();

    //! checks if a locator exists
    template <typename T>
    bool locator_exists(const char *scope = "");
};};

//////////////////////////////////////////////////////////////////////////

#include "locator.inline.h"

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////