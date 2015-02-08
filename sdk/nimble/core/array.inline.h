//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

//////////////////////////////////////////////////////////////////////////

#include <nimble/math/mathops.h>

//////////////////////////////////////////////////////////////////////////

#if defined(NIMBLE_TARGET_ANDROID)
    #include <type_traits>
#endif

//////////////////////////////////////////////////////////////////////////

namespace nimble{
namespace core{
    
//////////////////////////////////////////////////////////////////////////

//! a constructor
template <typename T, typename Allocator>
Array<T, Allocator>::Array(core::IAllocator *pAllocator)
:m_pAllocator(pAllocator ? pAllocator : &m_defaultAllocator)
,m_pBuffer(0)
,m_pData(0)
,m_size(0){
}
//! a constructor
template <typename T, typename Allocator>
Array<T, Allocator>::Array(SizeType size, core::IAllocator *pAllocator)
:m_pAllocator(pAllocator ? pAllocator : &m_defaultAllocator)
,m_pBuffer(0)
,m_pData(0)
,m_size(0){
    this->resize(size);
}
//! a constructor
template <typename T, typename Allocator>
Array<T, Allocator>::Array(T const *pData, SizeType size, core::IAllocator *pAllocator)
:m_pAllocator(pAllocator ? pAllocator : &m_defaultAllocator)
,m_pBuffer(0)
,m_pData(0)
,m_size(0){
    this->rangedAssign(0, pData, size);
}
//! a constructor
//! \param array the array to copy
template <typename T, typename Allocator>
Array<T, Allocator>::Array(core::Array<T, Allocator> const &array, core::IAllocator *pAllocator)
:m_pAllocator(pAllocator ? pAllocator : &m_defaultAllocator)
,m_pBuffer(0)
,m_pData(0)
,m_size(0){
    this->rangedAssign(0, array);
}
//! a constructor
template <typename T, typename Allocator>
template <typename OtherAllocator>
Array<T, Allocator>::Array(core::Array<T, OtherAllocator> const &array, core::IAllocator *pAllocator)
:m_pAllocator(pAllocator ? pAllocator : &m_defaultAllocator)
,m_pBuffer(0)
,m_pData(0)
,m_size(0){
    this->rangedAssign(0, array);
}
//! a constructor
template <typename T, typename Allocator>
Array<T, Allocator>::~Array(){
    if(m_pBuffer != 0){
        // call destructor on all items if object is destructable
        if(std::is_destructible<T>::value){
            for(SizeType i = 0; i < m_size; i++){
                m_pData[i].~T();
            }
        }
        // destroy our buffer
        m_pAllocator->deallocate(m_pBuffer);
        m_pBuffer = 0;
        m_pData = 0;
    }
    m_size = 0;
}

//////////////////////////////////////////////////////////////////////////

//! resize this buffer
//! param[in] bufferSize the new buffer size
template <typename T, typename Allocator>
void Array<T, Allocator>::resize(SizeType size){
    if(size == 0){
        // resizing to size 0 (destroy internal buffers)
        if(m_pBuffer != 0){
            // call destructor on all items if object is destructable
            if(std::is_destructible<T>::value){
                for(SizeType i = 0; i < m_size; i++){
                    m_pData[i].~T();
                }
            }
            // deallocate buffer
            m_pAllocator->deallocate(m_pBuffer);
        }
        m_pBuffer = 0;
        m_pData = 0;
        m_size = 0;
    }else if(m_pBuffer == 0){
        // buffer has not been created yet
        m_pBuffer = (char*)m_pAllocator->allocate(size * sizeof(T));
        // placement new initialize items
        if(std::is_default_constructible<T>::value){
            m_pData = new (m_pBuffer) T[size];
        }else{
            m_pData = (T*)m_pBuffer;
        }
        m_size = size;
    }else{
        // resizing from existing buffer (copy old data over)
        char *pOldBuffer = m_pBuffer;
        PointerType pOldData = m_pData;
        
        // allocate new buffer and placement new initialize items
        m_pBuffer = (char*)m_pAllocator->allocate(size * sizeof(T));
        if(std::is_default_constructible<T>::value){
            m_pData = new (m_pBuffer) T[size];
        }else{
            m_pData = (T*)m_pBuffer;
        }
        
        // copy old array of items to our new array
        SizeType copySize = math::min(size, m_size);
        m_size = size;
        this->rangedAssign(0, pOldData, copySize);
        
        // deallocate old buffer
        m_pAllocator->deallocate(pOldBuffer);
    }
}
//! returns the buffer size
//! \return the buffer size
template <typename T, typename Allocator>
typename Array<T, Allocator>::SizeType Array<T, Allocator>::getSize() const{
    return m_size;
}
    
//////////////////////////////////////////////////////////////////////////
    
//! copies raw array
//! \param destOffset the offset to copy to
//! \param pArray the array to copy
//! \param size the array size
template <typename T, typename Allocator>
void Array<T, Allocator>::rangedAssign(OffsetType destOffset, T const *pArray, SizeType size){
    core::assert_error(std::is_pod<T>::value || std::is_copy_assignable<T>::value);

    // resize only if we require more space for our copy operation
    SizeType requiredSize = destOffset + size;
    if(requiredSize > m_size){
        this->resize(requiredSize);
    }
    
    // depending on the type, we may be able to do a fast memcpy
    if(std::is_copy_assignable<T>::value){
        // if our type is not a POD (eg. a virtual class), we have to manually call copy on each item
        for(OffsetType i = 0; i < size; i++){
            m_pData[destOffset + i] = pArray[i];
        }
    }else if(std::is_pod<T>::value){
        // if our type is a POD, we can just do a memcpy
        memcpy((void*)&m_pData[destOffset], (void*)pArray, sizeof(T) * size);
    }
}
//! copies a buffer
//! \param destOffset the offset to copy to
//! \param buffer the buffer to copy
template <typename T, typename Allocator>
template <typename OtherAllocator>
void Array<T, Allocator>::rangedAssign(OffsetType destOffset, core::Array<T, OtherAllocator> const &array){
    this->rangedAssign(destOffset, array.getArrayPointer(), array.getSize());
}
    
//////////////////////////////////////////////////////////////////////////
    
//! copy operator
template <typename T, typename Allocator>
Array<T, Allocator>& Array<T, Allocator>::operator=(core::Array<T, Allocator> const &array){
    this->rangedAssign(0, array);
    return *this;
}
//! copy operator
template <typename T, typename Allocator>
template <typename OtherAllocator>
Array<T, Allocator>& Array<T, Allocator>::operator=(core::Array<T, OtherAllocator> const &array){
    this->rangedAssign(0, array);
    return *this;
}
    
//////////////////////////////////////////////////////////////////////////
    
//! equality operator
//! \param array the array to check for equality
//! \return the true if equal
template <typename T, typename Allocator>
template <typename OtherAllocator>
bool Array<T, Allocator>::operator==(core::Array<T, OtherAllocator> const &array){
    if(array.getSize() != m_size){return false;}
    if(&array[0] != m_pData){return false;}
    return true;
}
//! inequality operator
//! \param array the array to check for inequality
//! \return the true if not equal
template <typename T, typename Allocator>
template <typename OtherAllocator>
bool Array<T, Allocator>::operator!=(core::Array<T, OtherAllocator> const &array){
    return !operator==(array);
}
    
//////////////////////////////////////////////////////////////////////////
    
//! returns an alement
template <typename T, typename Allocator>
typename Array<T, Allocator>::ReferenceType Array<T, Allocator>::operator[](size_t index) const{
    core::assert_error(0 <= index && index < m_size);
    return m_pData[index];
}

//////////////////////////////////////////////////////////////////////////
    
//! returns the array pointer
template <typename T, typename Allocator>
typename Array<T, Allocator>::PointerType Array<T, Allocator>::getArrayPointer() const{
    return m_pData;
}

//////////////////////////////////////////////////////////////////////////
    
};};

//////////////////////////////////////////////////////////////////////////