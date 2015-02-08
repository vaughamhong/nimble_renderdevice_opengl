//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_core_pool_h__
#define __nimble_core_pool_h__

//////////////////////////////////////////////////////////////////////////

#include <stdint.h>
#include <cstdlib>
#include <nimble/core/array.h>
#include <nimble/core/stack.h>
#include <nimble/core/iallocator.h>

//////////////////////////////////////////////////////////////////////////

namespace nimble{
namespace core{
    
    //! Manages a static pool of items
    template <typename T, size_t kSize>
    class StaticPool{
    public:
        
        typedef T           ValueType;
        typedef T*          PointerType;
        typedef T&          ReferenceType;
        typedef size_t      SizeType;

    private:
        
        ValueType   m_data[kSize];
        SizeType    m_dataSize;
        
        SizeType    m_freeStack[kSize];
        bool        m_freeFlags[kSize];
        SizeType    m_freeStackSize;
        
    public:
        
        //! Constructor
        StaticPool();
        //! Destructor
        ~StaticPool();
        
    public:
        
        //! allocates item
        PointerType allocate();
        //! Deallocates item
        void deallocate(PointerType pItem);
        
    public:
        
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
        //! clears this pool
        virtual void clear();
    };
    
    //! Fixed sized memory allocator
    template <typename T, size_t kSize>
    class StaticPoolAllocator
    : public core::IAllocator{
    private:
        
        core::StaticPool<T, kSize> m_pool;
        
    public:
        
        //! Constructor
        StaticPoolAllocator();
        //! Destructor
        virtual ~StaticPoolAllocator();
        
    public:
        
        //! allocates memory - alignment must be suitable for any data type
        //! \return allocated aligned memory
        virtual void* allocate(size_t size);
        //! deallocates memory
        virtual void deallocate(void* pAllocation);
    };
    
    
//    //! Manages a pool of items
//    template <typename T, typename Allocator = core::Allocator>
//    class Pool{
//    public:
//        
//        typedef T           ValueType;
//        typedef T*          PointerType;
//        typedef T&          ReferenceType;
//        typedef size_t      SizeType;
//
//    private:
//        
//        typedef core::Array<T, Allocator>       ArrayType;
//        typedef core::Stack<size_t, Allocator>  StackType;
//        
//        ArrayType m_data;
//        StackType m_freeStack;
//        
//    public:
//        
//        //! Constructor
//        Pool();
//        //! Constructor
//        Pool(SizeType size);
//        //! Destructor
//        ~Pool();
//        
//    public:
//        
//        //! allocates item
//        T* allocate();
//        //! Deallocates item
//        void deallocate(T* pItem);
//        
//    public:
//        
//        //! resize this buffer
//        //! \param size the new buffer size
//        virtual void resize(SizeType capacity);
//        //! returns the buffer capacity
//        //! \return the buffer capacity
//        virtual SizeType getCapacity() const;
//        //! returns the buffer size
//        //! \return the buffer size
//        virtual SizeType getSize() const;
//        //! returns true if stack is empty
//        //! \return true if stack is empty
//        virtual bool isEmpty() const;
//        //! returns true if stack is full
//        //! \return true if stack is full
//        virtual bool isFull() const;
//        
//        //! clears this stack
//        virtual void clear();
//        
//    public:
//        
//        //! copy operator
//        //! \param array the array to copy
//        //! \return the copied array
//        Stack<T, Allocator>& operator=(core::Stack<T, Allocator> const &stack);
//        //! copy operator
//        //! \param array the array to copy
//        //! \return the copied array
//        template <typename OtherAllocator>
//        Stack<T, Allocator>& operator=(core::Stack<T, OtherAllocator> const &stack);
//        //! equality operator
//        //! \param array the array to check for equality
//        //! \return the true if equal
//        template <typename OtherAllocator>
//        bool operator==(core::Stack<T, OtherAllocator> const &stack);
//        //! inequality operator
//        //! \param array the array to check for inequality
//        //! \return the true if not equal
//        template <typename OtherAllocator>
//        bool operator!=(core::Stack<T, OtherAllocator> const &stack);
//    };
};};

//////////////////////////////////////////////////////////////////////////

#include <nimble/core/pool.inline.h>

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////