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
template <typename Allocator>
Buffer<Allocator>::Buffer(core::IAllocator *pAllocator)
:m_array(pAllocator){
}
//! a constructor
template <typename Allocator>
Buffer<Allocator>::Buffer(uint32_t size, core::IAllocator *pAllocator)
:m_array(pAllocator){
    resize(size);
}
//! a constructor
template <typename Allocator>
Buffer<Allocator>::Buffer(core::Buffer<Allocator> const &buffer, core::IAllocator *pAllocator)
:m_array(buffer.m_array, pAllocator){
}
//! a constructor
template <typename Allocator>
template <typename OtherAllocator>
Buffer<Allocator>::Buffer(core::Buffer<OtherAllocator> const &buffer, core::IAllocator *pAllocator)
:m_array(pAllocator){
    this->operator=(buffer);
}
//! a constructor
template <typename Allocator>
Buffer<Allocator>::~Buffer(){
}

//////////////////////////////////////////////////////////////////////////

//! resize this buffer
//! param[in] bufferSize the new buffer size
template <typename Allocator>
void Buffer<Allocator>::resize(SizeType size){
    m_array.resize(size);
}
//! returns the buffer size
//! \return the buffer size
template <typename Allocator>
typename Buffer<Allocator>::SizeType Buffer<Allocator>::getSize() const{
    return m_array.getSize();
}
//! copy operator
template <typename Allocator>
Buffer<Allocator>& Buffer<Allocator>::operator=(core::Buffer<Allocator> const &buffer){
    m_array = buffer.m_array;
    return *this;
}
//! copy operator
template <typename Allocator>
template <typename OtherAllocator>
Buffer<Allocator>& Buffer<Allocator>::operator=(core::Buffer<OtherAllocator> const &buffer){
    m_array.rangedAssign(0, buffer.getConstPointer(), buffer.getSize());
    return *this;
}
//! equality operator
//! \param array the array to check for equality
//! \return the true if equal
template <typename Allocator>
template <typename OtherAllocator>
bool Buffer<Allocator>::operator==(core::Buffer<OtherAllocator> const &buffer){
    if(m_array.getSize() != buffer.getSize()){return false;}
    if(&operator[](0) != &buffer[0]){return false;}
    return true;
}
//! inequality operator
//! \param array the array to check for inequality
//! \return the true if not equal
template <typename Allocator>
template <typename OtherAllocator>
bool Buffer<Allocator>::operator!=(core::Buffer<OtherAllocator> const &buffer){
    return !operator==(buffer);
}
//! returns an alement
template <typename Allocator>
char& Buffer<Allocator>::operator[](int32_t index) const{
    return m_array[index];
}

//////////////////////////////////////////////////////////////////////////

//! returns a const pointer to the buffer
//! \return a const pointer to the buffer
template <typename Allocator>
const char* Buffer<Allocator>::getConstPointer(int32_t offset) const{
    return &this->operator[](offset);
}
//! returns a pointer to the buffer
//! \return a pointer to the buffer
template <typename Allocator>
char* Buffer<Allocator>::getPointer(int32_t offset) const{
    return &this->operator[](offset);
}

//////////////////////////////////////////////////////////////////////////
    
};};

//////////////////////////////////////////////////////////////////////////