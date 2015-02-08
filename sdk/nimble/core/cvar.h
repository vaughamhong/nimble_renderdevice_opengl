//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_core_cvar_h__
#define __nimble_core_cvar_h__

//////////////////////////////////////////////////////////////////////////

#include <nimble/core/functor.h>

//////////////////////////////////////////////////////////////////////////

namespace nimble{
namespace core{

    struct cvar_t;
        
    //! sets a cvar value
    void cvar_set(const char *name, bool value);
    //! sets a cvar value
    void cvar_set(const char *name, int value);
    //! sets a cvar value
    void cvar_set(const char *name, float value);
    //! sets a cvar value
    void cvar_set(const char *name, const char *value);
    //! gets a cvar value
    bool cvar_getBoolValue(const char *name);
    //! gets a cvar value
    int cvar_getIntValue(const char *name);
    //! gets a cvar value
    float cvar_getFloatValue(const char *name);
    //! gets a cvar value
    const char* cvar_getStringValue(const char *name);
    //! returns true if cvar exists
    bool cvar_exists(const char *name);

    //! returns the number of cvars
    size_t cvar_count();
    //! gets a cvar value by index
    const char* cvar_getName(size_t index);
    //! gets a cvar value by index
    bool cvar_getBoolValue(size_t index);
    //! gets a cvar value by index
    int cvar_getIntValue(size_t index);
    //! gets a cvar value by index
    float cvar_getFloatValue(size_t index);
    //! gets a cvar value by index
    const char* cvar_getStringValue(size_t index);

    //! a cvar state change handler
    typedef core::Functor<void, TLIST_2(cvar_t const&, cvar_t const&)> CVarChangeHandler;
    
    //! registers a handler on a cvar state change
    void cvar_registerHandler(const char *name, CVarChangeHandler func);
    //! unregisters a handler on a cvar state change
    void cvar_unregisterHandler(const char *name, CVarChangeHandler func);
};};

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////