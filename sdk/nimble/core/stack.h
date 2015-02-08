//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_core_stack_h__
#define __nimble_core_stack_h__

//////////////////////////////////////////////////////////////////////////

#include <stdint.h>
#include <cstdlib>
#include <nimble/core/memory.h>
#include <nimble/core/array.h>

//////////////////////////////////////////////////////////////////////////

namespace nimble{
namespace core{

    //! A list of items that is pushed and popped
    template <typename T, typename Allocator = core::Allocator>
    class Stack{
    public:
        
        typedef T           ValueType;
        typedef T*          PointerType;
        typedef T&          ReferenceType;
        typedef size_t      SizeType;
        typedef Allocator   AllocatorType;

    private:

        core::Array<T, Allocator> m_array;
        SizeType m_capacity;
        SizeType m_size;
        
    public:

        //! a constructor
        Stack(AllocatorType *pAllocator = 0);
        //! a constructor
        //! \param size the number of elements to create
        Stack(SizeType size, AllocatorType *pAllocator = 0);
        //! a constructor
        //! \param array the array to copy
        Stack(core::Stack<T, Allocator> const &stack, AllocatorType *pAllocator = 0);
        //! a constructor
        //! \param array the array to copy
        template <typename OtherAllocator>
        Stack(core::Stack<T, OtherAllocator> const &stack, AllocatorType *pAllocator = 0);
        //! a destructor
        virtual ~Stack();
        
    public:
        
        //! pushes an item onto the stack
        virtual void push(const ValueType &item);
        //! pops an item from our stack
        virtual void pop();
        //! return the top item
        virtual ValueType& top();
        
    public:
        
        //! resize this buffer
        //! \param size the new buffer size
        virtual void resize(SizeType capacity);
        //! returns the buffer capacity
        //! \return the buffer capacity
        virtual SizeType getCapacity() const;
        //! returns the buffer size
        //! \return the buffer size
        virtual SizeType getSize() const;
        //! returns true if stack is empty
        //! \return true if stack is empty
        virtual bool isEmpty() const;
        //! returns true if stack is full
        //! \return true if stack is full
        virtual bool isFull() const;
        
        //! clears this stack
        virtual void clear();
        
    public:
        
        //! copy operator
        //! \param array the array to copy
        //! \return the copied array
        Stack<T, Allocator>& operator=(core::Stack<T, Allocator> const &stack);
        //! copy operator
        //! \param array the array to copy
        //! \return the copied array
        template <typename OtherAllocator>
        Stack<T, Allocator>& operator=(core::Stack<T, OtherAllocator> const &stack);
        //! equality operator
        //! \param array the array to check for equality
        //! \return the true if equal
        template <typename OtherAllocator>
        bool operator==(core::Stack<T, OtherAllocator> const &stack);
        //! inequality operator
        //! \param array the array to check for inequality
        //! \return the true if not equal
        template <typename OtherAllocator>
        bool operator!=(core::Stack<T, OtherAllocator> const &stack);
        
        //! returns an alement
        //! \param index the item with index to return
        //! \return the item at index
        ReferenceType operator[](size_t index) const;
    };
};};

//////////////////////////////////////////////////////////////////////////

#include "stack.inline.h"

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////