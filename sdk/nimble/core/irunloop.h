//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_core_irunLoop__
#define __nimble_core_irunLoop__

//////////////////////////////////////////////////////////////////////////

#include <nimble/core/functor.h>

//////////////////////////////////////////////////////////////////////////

namespace nimble{
    namespace core{
        typedef core::Functor<void> RunOperation;
        typedef core::Functor<void> RunLoopOperation;
        
        //! An abstract RunLoop defines an interface to run operations
        class IRunLoop{
        public:
            
            //! runs a synchronous operation on this run loop
            //! \param operation the operation to run
            virtual void runSync(core::RunOperation operation) = 0;
            //! runs a asynchronous operation on this run loop
            //! \param operation the operation to run
            virtual void runAsync(core::RunOperation operation) = 0;
            
            //! Adds a runloop operation
            //! \param operation adds a runloop operation to execute
            virtual void addLoopOperation(core::RunLoopOperation operation) = 0;
            //! Removes a runloop operation
            //! \param operation removes a runloop operation from execution
            virtual void removeLoopOperation(core::RunLoopOperation operation) = 0;
        };
    };
};

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////