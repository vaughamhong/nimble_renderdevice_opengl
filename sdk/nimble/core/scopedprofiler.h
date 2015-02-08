//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_core_scopedprofiler_h__
#define __nimble_core_scopedprofiler_h__

//////////////////////////////////////////////////////////////////////////

#include <stdint.h>
#include <nimble/core/timer.h>
#include <nimble/core/defines.h>
#include <string>

//////////////////////////////////////////////////////////////////////////

namespace nimble{
namespace core{
    
    //! generic timer
    class ScopedProfiler{
    private:
        
        core::Timer m_timer;
        std::string m_name;
        
    public:
        
        //! Constructor
        ScopedProfiler(std::string name);
        //! Destructor
        ~ScopedProfiler();
    };
};};

//////////////////////////////////////////////////////////////////////////

#if defined(NIMBLE_DEBUG) || defined(NIMBLE_PROFILE)
#define SCOPEDPROFILE(name) nimble::core::ScopedProfiler profile(name);
#else
#define SCOPEDPROFILE(name)
#endif

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////