//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_statestackmachine_h__
#define __nimble_statestackmachine_h__

//////////////////////////////////////////////////////////////////////////

#include <nimble/core/statemachine.h>
#include <stdint.h>
#include <nimble/core/smartptr.h>
#include <vector>

//////////////////////////////////////////////////////////////////////////

namespace nimble{
namespace core{
    class StackStateMachine;
    
    //! a stack based state
    class StackState{
    friend class StackStateMachine;
    private:
        
        core::StackStateMachine   *m_pStateMachine;
        
    public:
        
        //! Constructor
        StackState();
        //! Destructor
        virtual ~StackState();
        
    public:
        
        //! Called when the state has focus
        virtual void onStateHasFocus();
        //! Called when the state has lost focus
        virtual void onStateLostFocus();
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
        virtual core::StackStateMachine* getStateMachine();
        
    private:
        
        //! sets the state machine
        //! \param[in] pStateMachine the owner state machine
        virtual void setStateMachine(core::StackStateMachine *pStateMachine);
    };

    //! A stack based state machine
    class StackStateMachine{
    public:
        
        typedef core::StackState            StateType;
        typedef core::SmartPtr<StateType>   StatePtr;
        typedef std::vector<StatePtr>       StatePtrStack;

    private:
        
        StatePtrStack                   m_stateStack;
        StatePtrStack                   m_inactiveStates;
        bool                            m_invalidateUpdate;
        
    public:
        
        //! Constructor
        StackStateMachine();
        //! Destructor
        virtual ~StackStateMachine();
        
    public:
        
        //! returns the number of states in our stack
        //! \return the size of the stack
        virtual uint32_t getStackSize() const;
        //! returns the state at an index
        virtual StatePtr getStateAtIndex(uint32_t index);
        
        //! Switches the top state
        //! \param[in] state the state to switch to
        virtual void switchState(StatePtr state);
        //! pushes a state
        //! \param[in] state the state to push
        virtual void pushState(StatePtr state);
        //! pops a state
        virtual void popState(uint32_t numPops = 1);
        //! pops to root
        virtual void popToRoot();
        //! top state
        //! \return the top state
        virtual StatePtr topState();
        //! clears all states
        virtual void clearStates();
        //! state exists
        //! \param[in] state the state to check
        //! \return true if the state exists in our stack
        virtual bool exists(StatePtr state);

        //! Updates relative to an interval
        //! \param[in] interval the interval since last update
        virtual void update(uint64_t frameIndex, double interval);
        //! process an event
        //! \param[in] event the event to process
        virtual void processEvent(StateMachine::Event event) = 0;
    };
};};

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////