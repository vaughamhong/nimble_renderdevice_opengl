//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_core_runloop__
#define __nimble_core_runloop__

//////////////////////////////////////////////////////////////////////////

#include <nimble/core/irunloop.h>
#include <nimble/core/ithread.h>
#include <nimble/core/thread.mutex.h>
#include <vector>

//////////////////////////////////////////////////////////////////////////

namespace nimble{
    namespace core{
        class Semaphore;
        
        //! A RunLoop executes a loop, which can process
        //! one-off operations (perform) and looping operations
        class RunLoop
        : public core::IRunLoop{
        private:
            
            // loop operations
            typedef std::vector<core::RunLoopOperation> LoopOperationList;
            LoopOperationList m_newLoopOperations;
            LoopOperationList m_activeLoopOperations;
            LoopOperationList m_inactiveLoopOperations;
            int32_t           m_activeStartOffset;
            
            // operations
            struct operation_t{
                core::RunOperation operation;
                core::Semaphore    *pWaitLock;
            };
            typedef std::vector<operation_t> OperationList;
            OperationList                   m_newOperations;
            OperationList                   m_operations;
            
            mutable core::Mutex             m_newLoopOperationsLock;
            mutable core::Mutex             m_inactiveLoopOperationsLock;
            mutable core::Mutex             m_newOperationsLock;
            
        public:
            
            //! Constructor
            RunLoop();
            //! Destructor
            virtual ~RunLoop();
            
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

            //! Runs a single loop update
            void update();
            
        private:
            
            //! Executes loop operations
            virtual void executeLoopOperations();
            //! Executes operations
            virtual void executeOperations();
        };
        
        //! Sets the current run loop
        //! \param pRunLoop the run loop to set for this thread
        void setCurrentRunLoop(core::IRunLoop *pRunLoop, bool isMainRunLoop = false);
        //! Returns the current run loop
        //! \return the current run loop
        core::IRunLoop* getCurrentRunLoop();
        //! Returns the main run loop
        //! \return the main run loop
        core::IRunLoop* getMainRunLoop();
    };
};

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////