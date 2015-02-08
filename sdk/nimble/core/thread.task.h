//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_core_threadtask__
#define __nimble_core_threadtask__

//////////////////////////////////////////////////////////////////////////

#include <stdint.h>
#include <nimble/core/smartptr.h>

//////////////////////////////////////////////////////////////////////////

namespace nimble{
namespace core{
    class ThreadPool;
    class WorkerThread;
    
    //! base class job to be executed
    class Task{
    friend class ThreadPool;
    friend class WorkerThread;
    private:
        core::ThreadPool *m_pThreadPool;
        core::WorkerThread *m_pWorkerThread;
        uint32_t m_index;
        int32_t m_priority;
    public:
        //! Constructor
        Task();
        //! Destructor
        virtual ~Task();
        //! returns the job index
        virtual uint32_t getIndex() const;
        //! returns the job priority
        virtual uint32_t getPriority() const;
        //! returns the parent job manager
        virtual core::ThreadPool* getThreadPool() const;
        //! returns the bound worker thread
        virtual core::WorkerThread* getWorkerThread() const;
    public:
        //! execute
        virtual void execute() = 0;
        //! cancel
        virtual void cancel();
    private:
        //! sets a job index
        virtual void setIndex(uint32_t index);
        //! sets a job priority
        virtual void setPriority(int32_t priority);
        //! sets job manager
        virtual void setThreadPool(core::ThreadPool *pThreadPool);
        //! sets worker thread
        virtual void setWorkerThread(core::WorkerThread *pWorkerThread);
    };
    typedef core::SmartPtr<Task> TaskPtr;
};};

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////