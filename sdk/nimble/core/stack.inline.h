//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

//////////////////////////////////////////////////////////////////////////

namespace nimble{
    namespace core{

        //////////////////////////////////////////////////////////////////////////

        //! a constructor
        template <typename T, typename Allocator>
        Stack<T, Allocator>::Stack(AllocatorType *pAllocator)
        :m_array(pAllocator)
        ,m_capacity(0)
        ,m_size(0){
        }
        //! a constructor
        template <typename T, typename Allocator>
        Stack<T, Allocator>::Stack(SizeType size, AllocatorType *pAllocator)
        :m_array(pAllocator)
        ,m_capacity(0)
        ,m_size(0){
            resize(size);
        }
        //! a constructor
        template <typename T, typename Allocator>
        Stack<T, Allocator>::Stack(core::Stack<T, Allocator> const &stack, AllocatorType *pAllocator)
        :m_array(stack.m_array, pAllocator)
        ,m_capacity(stack.m_capacity)
        ,m_size(stack.m_size){
        }
        //! a constructor
        template <typename T, typename Allocator>
        template <typename OtherAllocator>
        Stack<T, Allocator>::Stack(core::Stack<T, OtherAllocator> const &stack, AllocatorType *pAllocator)
        :m_array(pAllocator){
            this->operator=(stack);
        }
        //! a constructor
        template <typename T, typename Allocator>
        Stack<T, Allocator>::~Stack(){
        }
            
        //////////////////////////////////////////////////////////////////////////

        //! pushes an item onto the stack
        template <typename T, typename Allocator>
        void Stack<T, Allocator>::push(const ValueType &item){
            core::assert_error((m_size + 1) <= m_capacity);
            m_array[m_size++] = item;
        }
        //! pops an item from our stack
        template <typename T, typename Allocator>
        void Stack<T, Allocator>::pop(){
            core::assert_error((m_size - 1) >= 0);
            m_size--;
        }
        //! return the top item
        template <typename T, typename Allocator>
        typename Stack<T, Allocator>::ValueType& Stack<T, Allocator>::top(){
            core::assert_error((m_size - 1) >= 0);
            return m_array[m_size - 1];
        }
            
        //////////////////////////////////////////////////////////////////////////

        //! resize this buffer
        //! param[in] bufferSize the new buffer size
        template <typename T, typename Allocator>
        void Stack<T, Allocator>::resize(SizeType capacity){
            core::assert_error(capacity >= m_size, "Stack resizing will destroy data");
            
            size_t oldCapacity = m_capacity;
            if(oldCapacity == capacity){
                return;
            }else if(oldCapacity < capacity){
                m_array.resize(capacity);
                m_capacity = capacity;
            }else if(oldCapacity > capacity){
                m_array.resize(capacity);
                m_capacity = capacity;
            }
        }
        //! returns the buffer capacity
        //! \return the buffer capacity
        template <typename T, typename Allocator>
        typename Stack<T, Allocator>::SizeType Stack<T, Allocator>::getCapacity() const{
            return m_capacity;
        }
        //! returns the buffer size
        //! \return the buffer size
        template <typename T, typename Allocator>
        typename Stack<T, Allocator>::SizeType Stack<T, Allocator>::getSize() const{
            return m_size;
        }
        //! returns true if stack is empty
        //! \return true if stack is empty
        template <typename T, typename Allocator>
        bool Stack<T, Allocator>::isEmpty() const{
            return m_size == 0;
        }
        //! returns true if stack is full
        //! \return true if stack is full
        template <typename T, typename Allocator>
        bool Stack<T, Allocator>::isFull() const{
            return m_size == m_capacity;
        }
        //! clears this stack
        template <typename T, typename Allocator>
        void Stack<T, Allocator>::clear(){
            m_size = 0;
        }
            
        //! copy operator
        template <typename T, typename Allocator>
        Stack<T, Allocator>& Stack<T, Allocator>::operator=(core::Stack<T, Allocator> const &stack){
            m_array = stack.m_array;
            m_size = stack.m_size;
            m_capacity = stack.m_capacity;
            return *this;
        }
        //! copy operator
        template <typename T, typename Allocator>
        template <typename OtherAllocator>
        Stack<T, Allocator>& Stack<T, Allocator>::operator=(core::Stack<T, OtherAllocator> const &stack){
            clear();
            resize(stack.getSize());
            for(SizeType i = 0; i < stack.getSize(); i++){
                this->push(stack[i]);
            }
            return *this;
        }
        //! equality operator
        //! \param array the array to check for equality
        //! \return the true if equal
        template <typename T, typename Allocator>
        template <typename OtherAllocator>
        bool Stack<T, Allocator>::operator==(core::Stack<T, OtherAllocator> const &stack){
            return (m_array == stack.m_array) && (m_size == stack.m_size) && (m_capacity == stack.m_capacity);
        }
        //! inequality operator
        //! \param array the array to check for inequality
        //! \return the true if not equal
        template <typename T, typename Allocator>
        template <typename OtherAllocator>
        bool Stack<T, Allocator>::operator!=(core::Stack<T, OtherAllocator> const &stack){
            return !operator==(stack);
        }
            
        //! returns an alement
        template <typename T, typename Allocator>
        typename Stack<T, Allocator>::ReferenceType Stack<T, Allocator>::operator[](size_t index) const{
            return m_array[index];
        }
            
        //////////////////////////////////////////////////////////////////////////
        
    };
};

//////////////////////////////////////////////////////////////////////////