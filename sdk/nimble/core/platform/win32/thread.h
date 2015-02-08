//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_core_win32_thread__
#define __nimble_core_win32_thread__

//////////////////////////////////////////////////////////////////////////

#include <stdint.h>
#include <nimble/core/functor.h>
#include <nimble/core/ithread.h>
#include <nimble/core/thread.mutex.h>

#if defined(NIMBLE_TARGET_WIN32)
	#include <Windows.h>
#else
	#include <pthread.h>
#endif

//////////////////////////////////////////////////////////////////////////

namespace nimble{
namespace core{
    class Thread;
    struct threadResults;
	struct threadData;
    
    typedef core::Functor<void> ThreadMainFunc;
    
    //! A Thread the basic building block of a parallel execution environment
    class Thread
    : public core::IThread{
    public:
        
        enum eState{
            kStateStopped,
            kStateStarting,
            kStateRunning
        };
        
    private:
        
        int32_t					m_threadId;
		HANDLE					m_threadHandle;
		SECURITY_ATTRIBUTES		m_securityAttributes;
        threadData				*m_pThreadData;
        
        core::eThreadPriority   m_priority;
        
        eState					m_state;
        mutable core::Mutex		m_stateLock;
                
        static int32_t			threadIdCount;
        static core::Mutex		threadIdCountLock;

    public:
        
        //! Constructor
        Thread(ThreadMainFunc main, core::eThreadPriority priority);
        //! Destructor
        virtual ~Thread();

        //! Starts running thread
        virtual void start();
        //! Wait until thread has stopped
        virtual void join();
        
        //! Returns true if thread is stopped
        bool isStopped() const;
        //! Returns true if thread is running
        bool isRunning() const;
        //! Returns true if thread is main thread
        virtual bool isMainThread() const;
        
        //! returns the threadId
        int32_t getThreadId() const;
		//! returns the thread priority
		virtual core::eThreadPriority getThreadPriority() const;
                
    protected:
        
        //! called when thread has started
        virtual void onThreadBegin();
        //! called when thread has exited
        virtual void onThreadEnd();
    };
};};

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////