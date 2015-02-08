//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_core_Stream_buffer__
#define __nimble_core_Stream_buffer__

//////////////////////////////////////////////////////////////////////////

#include <nimble/core/stream.h>
#include <nimble/core/buffer.h>

//////////////////////////////////////////////////////////////////////////

namespace nimble{
namespace core{
    
    //! buffer based Stream
    class BufferStream
    : public Stream{
    public:
        
        static const int kDefaultBufferSize = 32;
        
    private:
        
        core::Buffer<> m_buffer;
        int32_t m_readPosition;
        int32_t m_writePosition;
        
    public:
        
        //! Constructor
        BufferStream(size_t size = kDefaultBufferSize);
        //! Destructor
        virtual ~BufferStream();
        
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
        
    public:
        
        //! returns the buffer
        virtual const char* getConstPointer();
    };
};};

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////