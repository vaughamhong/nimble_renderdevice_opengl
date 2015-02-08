//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_core_Stream_ringbuffer__
#define __nimble_core_Stream_ringbuffer__

//////////////////////////////////////////////////////////////////////////

#include <nimble/core/stream.h>
#include <nimble/core/buffer.ring.h>

//////////////////////////////////////////////////////////////////////////

namespace nimble{
namespace core{
    
    //! rint buffer based Stream
    class RingBufferStream
    : public Stream{
    public:
        
        static const int kDefaultBufferSize = 32;
        
    private:
        
        core::RingBuffer m_buffer;
        
    public:
        
        //! Constructor
        RingBufferStream(size_t size = kDefaultBufferSize);
        //! Destructor
        virtual ~RingBufferStream();
        
    public:
        
        //! returns the size of our Stream
        virtual size_t size() const;
        //! returns true if this buffer is empty
        virtual bool isEmpty() const;
        
    public:
        
        //! Writes to this stream
        virtual void write(char const *pBuffer, size_t size);
        //! Reads from this stream
        virtual void read(char *pBuffer, size_t size);
    };
};};

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////