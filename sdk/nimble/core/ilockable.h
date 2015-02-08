//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_resource_ilockable_h__
#define __nimble_resource_ilockable_h__

//////////////////////////////////////////////////////////////////////////

#include <stdint.h>

//////////////////////////////////////////////////////////////////////////

namespace nimble{
namespace core{
    
    //! Lock Type
    enum eLockType{
        kLockTypeNone = -1,
        kLockTypeRead,
        kLockTypeWrite,
        kLockTypeReadWrite,
        kMaxLockTypes,
    };

    //! A Lockable interface allows external access through a lock/unlock interface
    class ILockable{
    public:
        
        //! Destructor
        virtual ~ILockable(){}
        
    public:
        
        //! locks data for access rights
        //! \param lockType the type of lock to the data
        //! \param ppPointer pointer to the data
        virtual bool lock(eLockType lockType, char** ppPointer) = 0;
        //! unlocks data
        virtual void unlock() = 0;
        
        //! \return true if locked
        virtual bool isLocked() const = 0;
        //! \return the lock type
        virtual eLockType getLockType() const = 0;
    };
};};

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////