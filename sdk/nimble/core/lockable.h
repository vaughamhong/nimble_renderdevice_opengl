//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_core_Lockable_h__
#define __nimble_core_Lockable_h__

//////////////////////////////////////////////////////////////////////////

#include <nimble/core/ilockable.h>

//////////////////////////////////////////////////////////////////////////

namespace nimble{
namespace core{
       
    //! Lockables allows external interfaces to access data through a lock/unlock interface
    class Lockable
    : public core::ILockable{
    private:
        
        bool        m_isLocked;
        eLockType   m_lockType;
        
    public:
        
        //! Constructor
        Lockable();
        //! Destructor
        virtual ~Lockable();
        
    public:
        
        //! locks data for access rights
        //! \param lockType the type of lock to the data
        //! \param ppPointer pointer to the data
        virtual bool lock(core::eLockType lockType, char **ppPointer);
        //! locks data for access rights
        //! \param lockType the type of lock to the data
        //! \param offset the offset of the data to lock
        //! \param size the size of the data to lock
        //! \param ppPointer pointer to the data
        virtual bool lockRange(core::eLockType lockType, char **ppPointer, int32_t offset, int32_t size);
        //! unlocks data
        virtual void unlock();
        
        //! \return true if locked
        virtual bool isLocked() const;
        //! \return the lock type
        virtual core::eLockType getLockType() const;
        
    protected:
        
        //! attempts to map a buffer
        virtual char* mapBuffer(core::eLockType lockType) = 0;
        //! attempts to map a buffer
        virtual char* mapBufferRange(core::eLockType lockType, uint32_t offset, uint32_t size) = 0;
        //! attempts to unmap a buffer
        virtual void unmapBuffer() = 0;
    };
};};

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////