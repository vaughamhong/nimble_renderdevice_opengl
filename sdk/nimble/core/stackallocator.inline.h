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
template <typename T>
StackAllocator<T>::StackAllocator(){
}
//! a constructor
template <typename T>
StackAllocator<T>::StackAllocator(SizeType size){
}
//! a constructor
template <typename T>
StackAllocator<T>::~StackAllocator(){
}
    
//////////////////////////////////////////////////////////////////////////

//! allocates memory - alignment must be suitable for any data type
//! \return allocated aligned memory
template <typename T>
void* StackAllocator<T>::allocate(size_t size){
    return 0;
}
//! deallocates memory
template <typename T>
void StackAllocator<T>::deallocate(void* pAllocation){
}

//////////////////////////////////////////////////////////////////////////
    
};};

//////////////////////////////////////////////////////////////////////////