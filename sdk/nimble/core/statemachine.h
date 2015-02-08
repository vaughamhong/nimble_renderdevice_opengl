//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_statemachine_h__
#define __nimble_statemachine_h__

//////////////////////////////////////////////////////////////////////////

#include <stdint.h>
#include <nimble/core/smartptr.h>
#include <vector>

//////////////////////////////////////////////////////////////////////////

namespace nimble{
namespace core{
    class StateMachine;
    
    // A stack based state
    class State{
    friend class StateMachine;
    private:
        
        core::StateMachine   *m_pStateMachine;
        
    public:
        
        //! Constructor
        State();
        //! Destructor
        virtual ~State();
        
    public:
        
        //! Called when we enter the state
        virtual void onStateEnter();
        //! Called when we leave the state
        virtual void onStateExit();
        
        //! Updates relative to an interval
        //! \param[in] interval the interval since last update
        virtual void update(double interval);
        
        //! Returns true if still active
        //! \return true if still active
        virtual bool isActive();
        //! Returns the state machine
        //! \return the owner state machine
        virtual core::StateMachine* getStateMachine();
        
    private:
        
        //! sets the state machine
        //! \param[in] pStateMachine the owner state machine
        virtual void setStateMachine(core::StateMachine *pStateMachine);
    };
    
    //! A state machine manages a single active state
    class StateMachine{
    public:
        
        typedef core::State             StateType;
        typedef core::SmartPtr<State>   StatePtr;
        typedef int32_t             Event;
        
    private:
        
        StatePtr m_activeState;
        
    public:
        
        //! default constructor
        StateMachine();
        //! a destrutor
        virtual ~StateMachine();
        
    public:
        
        //! Returns the active state
        //! \return the active state
        virtual StatePtr getActiveState();
        
        //! Switches the top state
        //! \param[in] state the state to switch to
        virtual void switchState(StatePtr state);
        
        //! Updates relative to an interval
        //! \param[in] interval the interval since last update
        virtual void update(double interval);
        
        //! process an event
        //! \param[in] event the event to process
        virtual void processEvent(StateMachine::Event event) = 0;
    };
};};

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////