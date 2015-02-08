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

        //! Constructor
        template <typename T, size_t kSize>
        StaticPool<T, kSize>::StaticPool()
        :m_dataSize(kSize)
        ,m_freeStackSize(kSize){
            clear();
        }
        //! Destructor
        template <typename T, size_t kSize>
        StaticPool<T, kSize>::~StaticPool(){
        }
        
        //! allocates item
        template <typename T, size_t kSize>
        typename StaticPool<T, kSize>::PointerType StaticPool<T, kSize>::allocate(){
            if(m_freeStackSize == 0){
                core::logger_error("core", "Failed to allocate from pool - out of memory");
                return 0;
            }
            m_freeStackSize -= 1;
            size_t index = m_freeStack[m_freeStackSize];
            m_freeFlags[index] = false;
            return &m_data[index];
        }
        //! Deallocates item
        template <typename T, size_t kSize>
        void StaticPool<T, kSize>::deallocate(typename StaticPool<T, kSize>::PointerType pItem){
            size_t index = pItem - &m_data[0];
            core::assert_error(0 <= index && index < kSize);
            
            // make sure it has not already been freed already
            if(m_freeFlags[index] == true){
                return;
            }
            
            // add freed index to free stack
            m_freeStack[m_freeStackSize] = index;
            m_freeFlags[index] = true;
            m_freeStackSize += 1;
        }
        
        //////////////////////////////////////////////////////////////////////////
        
        //! returns the buffer capacity
        //! \return the buffer capacity
        template <typename T, size_t kSize>
        typename StaticPool<T, kSize>::SizeType StaticPool<T, kSize>::getCapacity() const{
            return kSize - m_freeStackSize;
        }
        //! returns the buffer size
        //! \return the buffer size
        template <typename T, size_t kSize>
        typename StaticPool<T, kSize>::SizeType StaticPool<T, kSize>::getSize() const{
            return m_freeStackSize;
        }
        //! returns true if stack is empty
        //! \return true if stack is empty
        template <typename T, size_t kSize>
        bool StaticPool<T, kSize>::isEmpty() const{
            return m_freeStackSize == kSize;
        }
        //! returns true if stack is full
        //! \return true if stack is full
        template <typename T, size_t kSize>
        bool StaticPool<T, kSize>::isFull() const{
            return m_freeStackSize == 0;
        }
        //! clears this pool
        template <typename T, size_t kSize>
        void StaticPool<T, kSize>::clear(){
            // clear our data
            memset(&m_data[0], 0, sizeof(T) * kSize);
            // fill free stack indices
            for(size_t i = 0; i < kSize; i++){
                m_freeStack[i] = i;
                m_freeFlags[i] = true;
            }
        }
        
        //////////////////////////////////////////////////////////////////////////
        
        //! Constructor
        template <typename T, size_t kSize>
        StaticPoolAllocator<T, kSize>::StaticPoolAllocator(){
        }
        //! Destructor
        template <typename T, size_t kSize>
        StaticPoolAllocator<T, kSize>::~StaticPoolAllocator(){
        }
        
        //////////////////////////////////////////////////////////////////////////
        
        //! allocates memory - alignment must be suitable for any data type
        //! \return allocated aligned memory
        template <typename T, size_t kSize>
        void* StaticPoolAllocator<T, kSize>::allocate(size_t size){
            core::assert_error(size == sizeof(T));
            return (void*)m_pool.allocate();
        }
        //! deallocates memory
        template <typename T, size_t kSize>
        void StaticPoolAllocator<T, kSize>::deallocate(void* pAllocation){
            m_pool.deallocate((T*)pAllocation);
        }
        
        //////////////////////////////////////////////////////////////////////////
//
//        //! Constructor
//        template <typename T, typename Allocator>
//        Pool<T, Allocator>::Pool(){
//        }
//        //! Constructor
//        template <typename T, typename Allocator>
//        Pool<T, Allocator>::Pool(typename core::Pool<T, Allocator>::SizeType size)
//        :m_data(size)
//        ,m_freeStack(size){
//            for(int32_t i = 0; i < size; i++){
//                m_freeStack.push(i);
//            }
//        }
//        //! Destructor
//        template <typename T, typename Allocator>
//        Pool<T, Allocator>::~Pool(){
//        }
//        
//        //! allocates item
//        template <typename T, typename Allocator>
//        T* Pool<T, Allocator>::allocate(){
//            if(m_freeStack.isEmpty()){
//                core::logger_error("core", "Failed to allocate from pool - out of memory");
//                return 0;
//            }
//            int32_t index = m_freeStack.top(); m_freeStack.pop();
//            return &m_data[index];
//        }
//        //! Deallocates item
//        template <typename T, typename Allocator>
//        void Pool<T, Allocator>::deallocate(T* pItem){
//            int32_t index = pItem - &m_data[0];
//            m_freeStack.push(index);
//        }
//        
//        //////////////////////////////////////////////////////////////////////////
//
//        //! resize this buffer
//        //! \param size the new buffer size
//        template <typename T, typename Allocator>
//        void Pool<T, Allocator>::resize(SizeType capacity){
//            core::assert_error(capacity >= getSize(), "Stack resizing will destroy data");
//
//            // resizing to storage with larger capacity is safe
//            // when resizing to smaller storage, we need to make sure
//            // that we rejuggle items at the higher range of storage to
//            // a lower range before shrinking.
//            
//            size_t oldCapacity = m_freeStack.getCapacity();
//            if(oldCapacity == capacity){
//                return;
//            }else if(oldCapacity < capacity){
//                
//                // resize free stack
//                m_data.resize(capacity);
//                m_freeStack.resize(capacity);
//                
//                // copy all valid indices
//                for(size_t i = oldCapacity; i < m_freeStack.getCapacity(); i++){
//                    m_freeStack.push(i);
//                }
//            }else if(oldCapacity > capacity){
//                // find the set of items residing in the high range
//                // that needs to be reallocted
//                StackType reallocIndices(oldCapacity - capacity);
//                for(size_t j = capacity; j < oldCapacity; j++){
//                    
//                    // try and find index (that will be out of range)
//                    // within the free stack
//                    bool foundFreeIndex = false;
//                    for(size_t i = 0; i < m_freeStack.getSize(); i++){
//                        size_t index = m_freeStack[i];
//                        if(index == j){
//                            foundFreeIndex = true;
//                            break;
//                        }
//                    }
//                    
//                    // if we failed to find the index (that will be out of range)
//                    // this means it has been allocated, we we need to reallocate
//                    if(!foundFreeIndex){
//                        reallocIndices.push(j);
//                    }
//                }
//                
//                // filter out indices that are at the higher range
//                StackType filteredFreeStack = m_freeStack;
//                m_freeStack.resize(capacity);
//                while(!filteredFreeStack.isEmpty()){
//                    size_t index = filteredFreeStack.top();
//                    if(index < capacity){
//                        m_freeStack.push(index);
//                    }
//                    filteredFreeStack.pop();
//                }
//
//                // reallocate
//                for(size_t i = 0; i < reallocIndices.getSize(); i++){
//                    size_t reallocIndex = reallocIndices[i];
//                    size_t index = m_freeStack.top(); m_freeStack.pop();
//                    m_data[index] = m_data[reallocIndex];
//                }
//                m_data.resize(capacity);
//            }
//        }
//        //! returns the buffer capacity
//        //! \return the buffer capacity
//        template <typename T, typename Allocator>
//        typename core::Pool<T, Allocator>::SizeType Pool<T, Allocator>::getCapacity() const{
//            return m_freeStack.getCapacity();
//        }
//        //! returns the buffer size
//        //! \return the buffer size
//        template <typename T, typename Allocator>
//        typename core::Pool<T, Allocator>::SizeType Pool<T, Allocator>::getSize() const{
//            return m_freeStack.getCapacity() - m_freeStack.getSize();
//        }
//        //! returns true if stack is empty
//        //! \return true if stack is empty
//        template <typename T, typename Allocator>
//        bool Pool<T, Allocator>::isEmpty() const{
//            return m_freeStack.isEmpty();
//        }
//        //! returns true if stack is full
//        //! \return true if stack is full
//        template <typename T, typename Allocator>
//        bool Pool<T, Allocator>::isFull() const{
//            return m_freeStack.isFull();
//        }
//        
//        //! clears this stack
//        template <typename T, typename Allocator>
//        void Pool<T, Allocator>::clear(){
//            m_freeStack.clear();
//            for(int32_t i = 0; i < m_freeStack.getCapacity(); i++){
//                m_freeStack.push(i);
//            }
//        }
        
        //////////////////////////////////////////////////////////////////////////        
    };
};

//////////////////////////////////////////////////////////////////////////