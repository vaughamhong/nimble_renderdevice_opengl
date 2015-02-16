//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#include <nimble/renderdevice/opengl/arraybuffer.h>
#include <nimble/core/ilockable.h>
#include <nimble/core/assert.h>

//////////////////////////////////////////////////////////////////////////

using namespace nimble;
using namespace nimble::renderdevice::opengl;

//////////////////////////////////////////////////////////////////////////

// TODO
// + Be able to make orphan buffer explicit

//////////////////////////////////////////////////////////////////////////

//! a constructor
//! \param numElements the number of elements in this buffer
//! \param elementSize the element size
//! \param usage the usage of this buffer
ArrayBuffer::ArrayBuffer(uint32_t numElements, uint32_t elementSize, uint32_t usage, GLenum target)
:m_handle(0)
,m_target(target)
,m_usage(usage)
,m_created(false)
,m_numElements(numElements)
,m_elementSize(elementSize){
    NIMBLE_ASSERT(m_numElements > 0);
    NIMBLE_ASSERT(m_elementSize > 0);
    createBuffers();
}
//! a copy constructor
//! \param buffer the buffer to copy
ArrayBuffer::ArrayBuffer(ArrayBuffer& buffer)
:m_handle(0)
,m_target(buffer.m_target)
,m_usage(buffer.m_usage)
,m_created(false)
,m_numElements(buffer.m_numElements)
,m_elementSize(buffer.m_elementSize){
    NIMBLE_ASSERT(m_numElements > 0);
    NIMBLE_ASSERT(m_elementSize > 0);
    createBuffers();

    // copy our source data to our destination
    char* pSrPointer = 0;
    char* pDestPointer = 0;
    if(buffer.lock(core::kLockTypeRead, (char**)&pSrPointer)){
        if(this->lock(core::kLockTypeWrite, (char**)&pDestPointer)){
            memcpy(pDestPointer, pSrPointer, m_numElements * m_elementSize);
            this->unlock();
            buffer.unlock();
        }else{
            core::logger_error(__LINE__, __FILE__, "graphics", "Failed to lock destination array buffer");
            buffer.unlock();
        }
    }else{
        core::logger_error(__LINE__, __FILE__, "graphics", "Failed to lock source array buffer");
    }
}
//! a destructor
ArrayBuffer::~ArrayBuffer(){
	destroyBuffers();
}

//////////////////////////////////////////////////////////////////////////

//! returns the usage of this array
//! \return the usage of this array
uint32_t ArrayBuffer::getUsage() const{
    return m_usage;
}
//! returns the number of elements in this array
//! \return the number of elements in this array
size_t ArrayBuffer::getNumElements() const{
    return m_numElements;
}
//! returns the size of the elements in this array
//! \return the size of the elements in this array
size_t ArrayBuffer::getElementSize() const{
    return m_elementSize;
}
//! returns the number of bytes in this array
//! \return the number of bytes in this array
size_t ArrayBuffer::getBufferSize() const{
    return m_numElements * m_elementSize;
}

//////////////////////////////////////////////////////////////////////////

//!	creates array buffers
void ArrayBuffer::createBuffers(){
    NIMBLE_ASSERT(!m_created);
    NIMBLE_ASSERT(m_numElements > 0);
    NIMBLE_ASSERT(m_elementSize > 0);

    uint32_t bufferSize = getBufferSize();
    NIMBLE_ASSERT(bufferSize > 0);

    // track previously bound
    GLint boundHandle = 0;
    if(m_target == GL_ARRAY_BUFFER){
        GLDEBUG(glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &boundHandle));
    }else{
        GLDEBUG(glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &boundHandle));
    }
    
    // create our array
    GLDEBUG(glGenBuffers(1, &m_handle));
    GLDEBUG(glBindBuffer(m_target, m_handle));
    if(m_usage & renderdevice::kArrayUsageVolitile){
        GLDEBUG(glBufferData(m_target, bufferSize, 0, GL_DYNAMIC_DRAW));
    }else if(m_usage & renderdevice::kArrayUsageStatic){
        GLDEBUG(glBufferData(m_target, bufferSize, 0, GL_STATIC_DRAW));
    }else{
        GLDEBUG(glBufferData(m_target, bufferSize, 0, GL_DYNAMIC_DRAW));
    }
    
    // restore previously bound
    GLDEBUG(glBindBuffer(m_target, boundHandle));
    m_created = true;
}
//!	destroys array buffers
void ArrayBuffer::destroyBuffers(){
    NIMBLE_ASSERT(m_created);
    
    if(m_handle){
        GLDEBUG(glDeleteBuffers(1, &m_handle));
        m_handle = 0;
    }
    m_created = false;
}

//////////////////////////////////////////////////////////////////////////

//! returns the handle
GLuint ArrayBuffer::getArrayHandle() const{
    return m_handle;
}
//! returns the target type
GLuint ArrayBuffer::getTargetType() const{
    return m_target;
}

//////////////////////////////////////////////////////////////////////////

//! attempts to map a buffer
char* ArrayBuffer::mapBuffer(core::eLockType lockType){
    NIMBLE_ASSERT(m_created);
    NIMBLE_ASSERT(!isLocked());
    return this->mapBufferRange(lockType, 0, this->getBufferSize());
}
//! attempts to map a buffer
char* ArrayBuffer::mapBufferRange(core::eLockType lockType, uint32_t offset, uint32_t size){
    NIMBLE_ASSERT(m_created);
    NIMBLE_ASSERT(!isLocked());
    NIMBLE_ASSERT(offset < this->getBufferSize());
    NIMBLE_ASSERT((offset + size) <= this->getBufferSize());
    
    //! maps RenderDevice enums to GL
    static int bufferLockMap[core::kMaxLockTypes] ={
        GL_READ_ONLY,
        GL_WRITE_ONLY,
        GL_READ_WRITE};
    NIMBLE_ASSERT(bufferLockMap[lockType] != -1);
    
    // bind buffer if not already done so
    GLDEBUG(glBindBuffer(m_target, m_handle));

    // tell driver to orphan our previous buffer and
    // allocate a new one. This removes the need to synchronize (which
    // blocks until commands are flushed).
    if(m_usage & renderdevice::kArrayUsageVolitile){
        GLDEBUG(glBufferData(m_target, size, 0, GL_DYNAMIC_DRAW));
    }else if(m_usage & renderdevice::kArrayUsageStatic){
        GLDEBUG(glBufferData(m_target, size, 0, GL_STATIC_DRAW));
    }else{
        GLDEBUG(glBufferData(m_target, size, 0, GL_DYNAMIC_DRAW));
    }

    // map our buffer
    GLenum readWrite = bufferLockMap[lockType];
    void *ptr = GLDEBUG(glMapBuffer(m_target, readWrite));
    if(ptr){
        return &((char*)ptr)[offset];
    }
    core::Lockable::unlock();
    return 0;
}
//! attempts to unmap a buffer
void ArrayBuffer::unmapBuffer(){
    NIMBLE_ASSERT(m_created);
    GLDEBUG(glUnmapBuffer(m_target));
    GLDEBUG(glBindBuffer(m_target, 0));
}

//////////////////////////////////////////////////////////////////////////