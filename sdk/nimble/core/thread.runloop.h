//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_core_runloopthread__
#define __nimble_core_runloopthread__

//////////////////////////////////////////////////////////////////////////

#include <nimble/core/irunloop.h>
#include <nimble/core/ithread.h>
#include <nimble/core/thread.h>
#include <nimble/core/thread.mutex.h>
#include <vector>

//////////////////////////////////////////////////////////////////////////

namespace nimble{
    namespace core{
        class RunLoop;
        class Semaphore;
                
        //! A RunLoopThread is a thread running in a loop, which can
        //! execute one-off operations (perform) and looping operations
        class RunLoopThread
        : public core::IRunLoop
        , public core::IThread{
        private:
            
            mutable core::Mutex m_lock;
            
            core::RunLoop       *m_pRunLoop;
            core::Thread        *m_pThread;
            bool                m_stopRunning;
            
        public:
            
            //! Constructor
            RunLoopThread(core::eThreadPriority priority);
            //! Destructor
            virtual ~RunLoopThread();
            
            //! Starts running thread
            virtual void start();
            //! Stops running loop
            virtual void stop();
            //! Wait until thread has stopped
            virtual void join();
            
            //! Returns true if thread is stopped
            virtual bool isStopped() const;
            //! Returns true if thread is running
            virtual bool isRunning() const;
            //! Returns true if thread is main thread
            virtual bool isMainThread() const;
            
            //! returns the threadId
            virtual int32_t getThreadId() const;
            //! returns the thread priority
            virtual core::eThreadPriority getThreadPriority() const;
            
        public:
            
            //! called when thread has started
            virtual void onThreadBegin();
            //! called when thread has exited
            virtual void onThreadEnd();
            
        public:
            
            //! runs a synchronous operation on this run loop
            //! \param operation the operation to run
            virtual void runSync(core::RunOperation operation);
            //! runs a asynchronous operation on this run loop
            //! \param operation the operation to run
            virtual void runAsync(core::RunOperation operation);
            
            //! Adds a runloop operation
            //! \param operation adds a runloop operation to execute
            void addLoopOperation(core::RunLoopOperation operation);
            //! Removes a runloop operation
            //! \param operation removes a runloop operation from execution
            void removeLoopOperation(core::RunLoopOperation operation);
            
        private:
            
            //! thread starting point
            virtual void main();
        };        
    };
};

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////