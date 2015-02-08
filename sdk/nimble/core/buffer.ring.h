//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_core_ringbuffer_h__
#define __nimble_core_ringbuffer_h__

//////////////////////////////////////////////////////////////////////////

#include <stdint.h>
#include <list>
#include <queue>
#include <nimble/core/buffer.h>

//////////////////////////////////////////////////////////////////////////

namespace nimble{
namespace core{
    
    //! ring buffer
    class RingBuffer
    : public Buffer<>{
    private:
        
        typedef std::list<uint32_t>                           ItemSizeQueueContainer;
        typedef std::queue<uint32_t, ItemSizeQueueContainer>  ItemSizeQueue;
                
        char        *m_pBufferFront;
        size_t      m_allocatedSize;
        uint32_t    m_endOfBufferWaste;
        
        ItemSizeQueue   m_itemSizes;
        
    public:

        //! a constructor
        RingBuffer();
        //! Constructor
        RingBuffer(size_t size);
        //! a constructor
        RingBuffer(core::RingBuffer const &buffer);
        //! Destructor
        virtual ~RingBuffer();

    public:

        //! returns the allocated size of the buffer
        //! \return the allocated size of the buffer
        virtual size_t allocatedSize() const;
        //! returns the free size of the buffer
        //! \return the free size of the buffer
        virtual size_t freeSize() const;
        //! returns true if buffer is empty
        virtual bool isEmpty() const;

    protected:
        
        //! called when resizing, allowing child classes to resolve data as necessary
        virtual void resolveResize(char *pOldBuffer, size_t oldSize, char *pNewBuffer, size_t newSize);
        //! automatic resize policy
        virtual size_t calculateAutoResizeAmount(size_t additionalSize);
        
    public:
        
        //! clears the buffer contents
        virtual void clear();
        //! Inserts a new item at the back of the queue.
        //! \param buffer the buffer to push
        //! \param bufferSize the size of the buffer to push
        //! \return pointer to the data in the buffer
        virtual void push(const char* pBuffer, size_t bufferSize);
        //! Removes the item at the front of a non-empty queue.
        //! \param ppBuffer the buffer to fill
        //! \param size the buffer size
        //! \return 0 if no errors occured
        virtual void pop(char** ppBuffer, size_t bufferSize);

    private:

        //! calculates the back of our buffer
        virtual char* calculateBackOfBuffer();
    };
};};

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////