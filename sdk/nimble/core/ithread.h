//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_core_ithread__
#define __nimble_core_ithread__

//////////////////////////////////////////////////////////////////////////

#include <stdint.h>

//////////////////////////////////////////////////////////////////////////

namespace nimble{
    namespace core{

        //! Thread priorities
        enum eThreadPriority{
            kThreadPriorityNormal,
            kThreadPriorityBackground
        };

        //! Abstract thread interface
        class IThread{
        public:
            
            //! Constructor
            IThread(){}
            //! Destructor
            virtual ~IThread(){}
            
            //! Starts running thread
            virtual void start() = 0;
            //! Wait until thread has stopped
            virtual void join() = 0;
            
            //! Returns true if thread is stopped
            virtual bool isStopped() const = 0;
            //! Returns true if thread is running
            virtual bool isRunning() const = 0;
            //! Returns true if thread is main thread
            virtual bool isMainThread() const = 0;
            
            //! returns the threadId
            virtual int32_t getThreadId() const = 0;
            //! returns the thread priority
            virtual core::eThreadPriority getThreadPriority() const = 0;
        };
    };
};

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////