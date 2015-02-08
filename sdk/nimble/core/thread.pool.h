//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_core_threadpool__
#define __nimble_core_threadpool__

//////////////////////////////////////////////////////////////////////////

#include <stdint.h>
#include <nimble/core/thread.runloop.h>
#include <nimble/core/thread.task.h>
#include <nimble/core/thread.taskqueue.h>
#include <nimble/core/future.h>

//////////////////////////////////////////////////////////////////////////

namespace nimble{
namespace core{
    class ITaskQueue;
    class Semaphore;

    //////////////////////////////////////////////////////////////////////////
    
    //! handles the execution of a job
    class WorkerThread
    : public core::RunLoopThread{
    private:
        uint32_t m_index;
        ITaskQueue *m_pTaskQueue;
        core::Semaphore *m_pFullSem;
        core::Semaphore *m_pEmptySem;
        bool m_isDoneRunning;
    public:
        //! Constructor
        WorkerThread(uint32_t index, ITaskQueue *pTaskQueue, core::Semaphore *pFullSem, core::Semaphore *pEmptySem, core::eThreadPriority priority);
        //! Destructor
        virtual ~WorkerThread();

        //! returns the worker index
        virtual uint32_t getIndex() const;
        
        //! called on each run loop iteration
        virtual void runSingleFrame();
        //! returns true if we are done running
        virtual bool isDoneRunning();
    };
    
    //////////////////////////////////////////////////////////////////////////

    //! async task with a return value
    template <typename R = void>
    class AsyncTask
    : public core::Task{
    public:
        
        typedef core::Functor<R> FunctorType;
        typedef core::Promise<R> PromiseType;
        typedef core::Future<R> FutureType;
        
    private:
        
        PromiseType m_promise;
        FunctorType m_func;
        
    public:
        
        //! Constructor
        AsyncTask(FunctorType func)
        :m_func(func){
        }
        //! Destructor
        virtual ~AsyncTask(){
        }
        //! Returns execution future
        virtual FutureType getFuture(){
            return m_promise.getFuture();
        }
        //! Execute
        virtual void execute(){
            try{
                m_promise.set(m_func());
            }catch(...){
                // TODO: consider passing through std::exception
                m_promise.setException(1);
            }
        }
    };
    
    //////////////////////////////////////////////////////////////////////////

    //! manages a pool of executor threads
    class ThreadPool{
    private:
        
        typedef std::vector<core::WorkerThread*>  WorkerList;
        
        uint32_t m_numTotalTasks;
        
        WorkerList m_workerThreads;
        nimble::core::TaskQueue m_taskQueue;
        
        core::Mutex m_lock;
        core::Semaphore *m_pFullSem;
        core::Semaphore *m_pEmptySem;
        
    public:
        
        //! Constructor
        ThreadPool(int32_t numWorkers, uint32_t queueSize);
        //! Destructor
        virtual ~ThreadPool();
        
    public:
        
        //! adds a task with a return value to be executed
        template <typename R>
        core::Future<R> executeAsyncTask(core::Functor<R> const &callback, int32_t priority = 0){
            core::Task *pTask = new /*()*/ AsyncTask<R>(callback);
            AsyncTask<R> *pAsyncTask = dynamic_cast<AsyncTask<R>*>(pTask);
            core::Future<R> future = pAsyncTask->getFuture();
            this->executeAsyncTask(pTask, priority);
            return future;
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
};};

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////