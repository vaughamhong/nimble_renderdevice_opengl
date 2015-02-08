//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_core_buffer_h__
#define __nimble_core_buffer_h__

//////////////////////////////////////////////////////////////////////////

#include <stdint.h>
#include <cstdlib>
#include <nimble/core/memory.h>
#include <nimble/core/array.h>

//////////////////////////////////////////////////////////////////////////

// TODO: Add exceptions

//////////////////////////////////////////////////////////////////////////

namespace nimble{
namespace core{
    
    //! An array of bytes
    template <typename Allocator = core::Allocator>
    class Buffer{
    public:
        
        typedef size_t      SizeType;
        
    private:
        
        core::Array<char, Allocator> m_array;

    public:

        //! a constructor
        Buffer(core::IAllocator *pAllocator = 0);
        //! a constructor
        Buffer(uint32_t size, core::IAllocator *pAllocator = 0);
        //! a constructor
        Buffer(core::Buffer<Allocator> const &buffer, core::IAllocator *pAllocator = 0);
        //! a constructor
        template <typename OtherAllocator>
        Buffer(core::Buffer<OtherAllocator> const &buffer, core::IAllocator *pAllocator = 0);
        //! a destructor
        virtual ~Buffer();
        
    public:
        
        //! resize this buffer
        //! \param size the new buffer size
        virtual void resize(SizeType size);
        //! returns the buffer size
        //! \return the buffer size
        virtual SizeType getSize() const;

        //! copy operator
        Buffer<Allocator>& operator=(core::Buffer<Allocator> const &buffer);
        //! copy operator
        template <typename OtherAllocator>
        Buffer<Allocator>& operator=(core::Buffer<OtherAllocator> const &buffer);
        //! equality operator
        //! \param array the array to check for equality
        //! \return the true if equal
        template <typename OtherAllocator>
        bool operator==(core::Buffer<OtherAllocator> const &buffer);
        //! inequality operator
        //! \param array the array to check for inequality
        //! \return the true if not equal
        template <typename OtherAllocator>
        bool operator!=(core::Buffer<OtherAllocator> const &buffer);

        //! returns an alement
        char& operator[](int32_t index) const;
        
    public:
        
        //! returns a const pointer to the buffer
        //! \return a const pointer to the buffer
        virtual const char* getConstPointer(int32_t offset = 0) const;
        //! returns a pointer to the buffer
        //! \return a pointer to the buffer
        virtual char* getPointer(int32_t offset = 0) const;
    };
};};

//////////////////////////////////////////////////////////////////////////

#include "buffer.inline.h"

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////