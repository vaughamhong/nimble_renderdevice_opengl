//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_stream_threadsafe_h__
#define __nimble_stream_threadsafe_h__

//////////////////////////////////////////////////////////////////////////

#include <stdint.h>
#include <nimble/core/thread.mutex.h>

//////////////////////////////////////////////////////////////////////////

namespace nimble{
namespace core{
    
    //! thread safe Stream
    template <typename K>
    class ThreadSafeStream
    : public K{
    private:
        
        mutable core::Mutex m_lock;
        
    public:
        
        //! Constructor
        ThreadSafeStream(){
        }
        //! Constructor
        ThreadSafeStream(uint32_t size):K(size){
        }
        //! Destructor
        virtual ~ThreadSafeStream(){
        }
        
    public:
        
        //! returns the size of our Stream
        virtual uint32_t size(){
            core::ScopedLock lock(&m_lock);
            return K::size();
        }
        //! returns true if this buffer is empty
        virtual bool isEmpty() const{
            core::ScopedLock lock(&m_lock);
            return K::isEmpty();
        }
        
    public:
                    
        //! Writes to this stream
        virtual void write(char const *pBuffer, uint32_t size){
            core::ScopedLock lock(&m_lock);
            K::write(pBuffer, size);
        }
        //! Reads from this stream
        virtual void read(char *pBuffer, uint32_t size){
            core::ScopedLock lock(&m_lock);
            K::read(pBuffer, size);
        }
    };
};};

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////