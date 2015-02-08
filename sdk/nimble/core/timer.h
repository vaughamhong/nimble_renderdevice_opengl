//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_core_timer_h__
#define __nimble_core_timer_h__

//////////////////////////////////////////////////////////////////////////

#include <stdint.h>

#if defined(NIMBLE_TARGET_WIN32)
    #include <windows.h>
#elif defined(NIMBLE_TARGET_OSX)
    #include <mach/mach_time.h>
    #include <sys/time.h>
#elif defined(NIMBLE_TARGET_ANDROID)
    #include <time.h>
#endif

//////////////////////////////////////////////////////////////////////////

namespace nimble{
namespace core{
    
    //! generic timer
    class Timer{
    private:
        
        double m_startTime;
        double m_endTime;
        bool m_stopped;
        
    #if defined(NIMBLE_TARGET_WIN32)
        LARGE_INTEGER frequency;
        LARGE_INTEGER startTick;
        LARGE_INTEGER endTick;
    #elif defined(NIMBLE_TARGET_OSX)
        mach_timebase_info_data_t m_info;
        uint64_t startTick;
        uint64_t endTick;
    #elif defined(NIMBLE_TARGET_ANDROID)
        struct timespec m_start;
        struct timespec m_end;
    #endif
        
    public:
        
        //! Constructor
        Timer();
        //! Destructor
        ~Timer();

    public:
        
        //! starts the timer
        void start();
        //! stops the timer
        void stop();
        //! resets the timer
        void reset();
        //! sets the timer
        void set(double time);
        
    public:
        
        //! returns the elapsed ms
        double getElapsedTimeInMilliSeconds();
        //! returns the elapsed sec
        double getElapsedTimeInSeconds();
        //! returns the elapsed us
        double getElapsedTimeInMicroSeconds();
        //! returns the elapsed ns
        double getElapsedTimeInNanoSeconds();
        //! returns the elapsed ticks
        double getElapsedTicks();
    };
    
    //! timer that starts and stops relative to scope
    class ScopedTimer{
    private:
        
        Timer &m_timer;
        
    public:

        //! Constructor
        ScopedTimer(Timer &timer);
        //! Destructor
        ~ScopedTimer();

	public:

		//! Assignment operator
		ScopedTimer& operator=(ScopedTimer const &timer);
    };
};};

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////
