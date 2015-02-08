//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_core_threadtaskqueue__
#define __nimble_core_threadtaskqueue__

//////////////////////////////////////////////////////////////////////////

#include <stdint.h>
#include <vector>
#include <queue>
#include <nimble/core/thread.task.h>

//////////////////////////////////////////////////////////////////////////

namespace nimble{
    namespace core{
        class Semaphore;
        
        //! abstract job queue
        class ITaskQueue{
        public:
            //! pushes a job into the queue
            virtual TaskPtr push(TaskPtr pTask) = 0;
            //! pops a job from the queue
            virtual TaskPtr pop() = 0;
            
            //! removes a job
            virtual void cancelTask(TaskPtr pTask) = 0;
            //! removes all jobs
            virtual std::vector<TaskPtr> cancelAllTasks() = 0;
            
            //! returns the queue size
            virtual uint32_t size() = 0;
        };
        
        //! a (thread-safe) job queue
        class TaskQueue
        : public core::ITaskQueue{
        private:
            
            class compareTaskPriority{
            public:
                bool operator() (const core::TaskPtr& lhs, const core::TaskPtr&rhs) const{
                    return lhs->getPriority() < rhs->getPriority();
                }
            };
            std::priority_queue<core::TaskPtr, std::vector<core::TaskPtr>, compareTaskPriority> m_taskQueue;
            core::Mutex                         m_taskQueueLock;
        public:
            //! Constructor
            TaskQueue();
            //! Destructor
            virtual ~TaskQueue();
        public:
            //! pushes a job into the queue
            virtual TaskPtr push(TaskPtr pTask);
            //! pops a job from the queue
            virtual TaskPtr pop();
            
            //! removes a job
            virtual void cancelTask(TaskPtr pTask);
            //! removes all jobs
            virtual std::vector<TaskPtr> cancelAllTasks();
            
            //! returns the queue size
            virtual uint32_t size();
        };
    };
};

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////