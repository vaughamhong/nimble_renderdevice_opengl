//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_core_backgroundthread__
#define __nimble_core_backgroundthread__

//////////////////////////////////////////////////////////////////////////

#include <nimble/core/functor.h>
#include <nimble/core/thread.pool.h>
#include <nimble/core/thread.taskqueue.h>

//////////////////////////////////////////////////////////////////////////

namespace nimble{
    namespace core{
        
        //! A background thread runs tasks in the background
        //! and return results via future.
        class BackgroundThread
        : public core::ThreadPool{
        public:
            
            //! Constructor
            BackgroundThread(uint32_t queueSize);
            //! Destructor
            virtual ~BackgroundThread();
            
        public:
            
            //! adds a task with a return value to be executed
            template <typename R>
            core::Future<R> executeAsyncTask(core::Functor<R> const &callback, int32_t priority = 0){
                return core::ThreadPool::executeAsyncTask<R>(callback, priority);
            }
            //! adds a task to be executed
            virtual void executeAsyncTask(core::Functor<void> const &callback, int32_t priority = 0);
            //! adds a task to be executed
            virtual void executeAsyncTask(core::Task *pTask, int32_t priority = 0);
            //! removes a task from execution
            virtual void cancelTask(TaskPtr pTask);
            //! clears all tasks
            virtual std::vector<TaskPtr> cancelAllTasks();
        };
    };
};

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////