//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_core_Stream_externalbuffer__
#define __nimble_core_Stream_externalbuffer__

//////////////////////////////////////////////////////////////////////////

#include <nimble/core/stream.h>

//////////////////////////////////////////////////////////////////////////

namespace nimble{
namespace core{
    
    //! external buffer based Stream
    class ExternalBufferStream
    : public Stream{
    private:
        
        char        *m_pBuffer;
        size_t      m_bufferSize;
        uint32_t    m_readPosition;
        uint32_t    m_writePosition;
        
    public:
        
        //! Constructor
        ExternalBufferStream();
        //! Constructor
        ExternalBufferStream(char *pBuffer, size_t size);
        //! Destructor
        virtual ~ExternalBufferStream();
        
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
        virtual const char* getConstPointer(){return m_pBuffer;}
    };
};};

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////