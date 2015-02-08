//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_core_array_h__
#define __nimble_core_array_h__

//////////////////////////////////////////////////////////////////////////

#include <stdint.h>
#include <cstdlib>
#include <memory.h>
#include <nimble/core/memory.h>

//////////////////////////////////////////////////////////////////////////

// TODO: Add exceptions

//////////////////////////////////////////////////////////////////////////

namespace nimble{
namespace core{
    
    //! Manages a list of items
    //! Support both POD and virtual classes
    template <typename T, typename Allocator = core::Allocator>
    class Array{
    public:
        
        typedef T           ValueType;
        typedef T*          PointerType;
        typedef T&          ReferenceType;
        typedef size_t      SizeType;
        typedef size_t      OffsetType;

    private:
        
        // STL containers makes a copy of the input allocator for later use. This is as a result
        // of STL container policy assuming allocators are state-less. This means
        // allocators of the same type are allowed to allocate / deallocate even across
        // different allocator instances. Allocators of the same type are are essentially singletons.
        
        // Our implementation allows stateful allocators. This means allocators (of the same type)
        // can be constructed / configured separately (eg. with different heaps). This adds
        // flexibility but requires more specific attention appiled to application level allocator design.
        
        // The default allocator is used if no external allocator
        // is specified on construction. Although this takes up a bit
        // more space, it is much easier to maintain (cleans up after itself
        // on destruction, no additional heap allocations, no additional management).
        Allocator           m_defaultAllocator;
        core::IAllocator    *m_pAllocator;
        
        // The allocated raw buffer
        char                *m_pBuffer;
        
        // The contiguous array of items
        ValueType           *m_pData;
        
        // The number of array items
        SizeType            m_size;
        
    public:

        //! a constructor
        Array(core::IAllocator *pAllocator = 0);
        //! a constructor
        //! \param size the number of elements to create
        Array(T const *pData, SizeType size, core::IAllocator *pAllocator = 0);
        //! a constructor
        //! \param size the number of elements to create
        Array(SizeType size, core::IAllocator *pAllocator = 0);
        //! a constructor
        //! \param array the array to copy
        Array(core::Array<T, Allocator> const &array, core::IAllocator *pAllocator = 0);
        //! a constructor
        //! \param array the array to copy
        template <typename OtherAllocator>
        Array(core::Array<T, OtherAllocator> const &array, core::IAllocator *pAllocator = 0);
        //! a destructor
        virtual ~Array();
        
    public:
        
        //! resize this buffer
        //! \param size the new buffer size
        virtual void resize(SizeType size);
        //! returns the buffer size
        //! \return the buffer size
        virtual SizeType getSize() const;

        //! copies raw array
        //! \param destOffset the offset to copy to
        //! \param pArray the array to copy
        //! \param size the array size
        virtual void rangedAssign(OffsetType destOffset, T const *pArray, SizeType size);
        //! copies a buffer
        //! \param destOffset the offset to copy to
        //! \param buffer the buffer to copy
        template <typename OtherAllocator>
        void rangedAssign(OffsetType destOffset, core::Array<T, OtherAllocator> const &buffer);

    public:
        
        //! copy operator
        //! \param array the array to copy
        //! \return the copied array
        Array<T, Allocator>& operator=(core::Array<T, Allocator> const &array);
        //! copy operator
        //! \param array the array to copy
        //! \return the copied array
        template <typename OtherAllocator>
        Array<T, Allocator>& operator=(core::Array<T, OtherAllocator> const &array);
        
        //! equality operator
        //! \param array the array to check for equality
        //! \return the true if equal
        template <typename OtherAllocator>
        bool operator==(core::Array<T, OtherAllocator> const &array);
        //! inequality operator
        //! \param array the array to check for inequality
        //! \return the true if not equal
        template <typename OtherAllocator>
        bool operator!=(core::Array<T, OtherAllocator> const &array);
        
        //! returns an alement
        //! \param index the item with index to return
        //! \return the item at index
        ReferenceType operator[](size_t index) const;
        
        //! returns the array pointer
        PointerType getArrayPointer() const;
    };
};};

//////////////////////////////////////////////////////////////////////////

#include "array.inline.h"

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////