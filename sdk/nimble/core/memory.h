//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_core_memory_h__
#define __nimble_core_memory_h__

//////////////////////////////////////////////////////////////////////////

#include <stdint.h>
#include <cstdlib>
#include <new>

//////////////////////////////////////////////////////////////////////////

#include <nimble/core/dlmallocallocator.h>
#include <nimble/core/mallocallocator.h>
#include <nimble/core/smallblockallocator.h>
#include <nimble/core/debugheap.h>
#include <nimble/core/threadsafeheap.h>
#include <nimble/core/profileheap.h>

//////////////////////////////////////////////////////////////////////////

// installs new / delete overloads
#define kOverloadNewAndDelete 1

//////////////////////////////////////////////////////////////////////////

namespace nimble{
namespace core{
    class IAllocator;

    //! Sets our global allocator
    //! \param pAllocator the global allocator to use
    void setGlobalAllocator(core::IAllocator *pAllocator);
    //! Returns our global allocator
    //! \return our global allocator
    core::IAllocator* getGlobalAllocator();
    
    //! Calculates aligned address
    void* alignAddress(void *pAddress, size_t alignment);
    
    // define our various allocators
	#if defined(NIMBLE_TARGET_WIN32)
		#if defined(NIMBLE_DEBUG)
			class Allocator: public core::DebugHeap<core::MallocAllocator>{};
			class SharedAllocator: public core::ThreadSafeHeap<core::ProfileHeap<core::DebugHeap<core::MallocAllocator> > >{};
		#else
			class Allocator: public core::MallocAllocator{};
			class SharedAllocator: public core::ThreadSafeHeap<core::MallocAllocator>{};
		#endif
	#else
		#if defined(NIMBLE_DEBUG)
			class Allocator: public core::DebugHeap<core::MallocAllocator>{};
			class SharedAllocator: public core::ThreadSafeHeap<core::ProfileHeap<core::DebugHeap<core::MallocAllocator> > >{};
		#else
			class Allocator: public core::MallocAllocator{};
			class SharedAllocator: public core::ThreadSafeHeap<core::MallocAllocator>{};
		#endif
	#endif
};};

//////////////////////////////////////////////////////////////////////////

#if kOverloadNewAndDelete
#if defined(NIMBLE_TARGET_WIN32)
	void* operator new(size_t size) throw();
#elif defined(NIMBLE_TARGET_OSX)
	void* operator new(size_t size) throw(std::bad_alloc);
#elif defined(NIMBLE_TARGET_ANDROID)
    void* operator new(size_t size);
#endif
	void* operator new(size_t size, const std::nothrow_t&) throw();
	void* operator new(size_t size, nimble::core::IAllocator *pAllocator);
	void operator delete(void* ptr) throw();
	void operator delete(void* ptr, const std::nothrow_t&) throw();

#if defined(NIMBLE_TARGET_WIN32)
	void* operator new[](size_t size) throw();
#elif defined(NIMBLE_TARGET_OSX)
	void* operator new[](size_t size) throw(std::bad_alloc);
#elif defined(NIMBLE_TARGET_ANDROID)
void* operator new[](size_t size);
#endif
	void* operator new[](size_t size, const std::nothrow_t&) throw();
	void* operator new[](size_t size, nimble::core::IAllocator *pAllocator);
	void operator delete[](void* ptr) throw();
	void operator delete[](void* ptr, const std::nothrow_t&) throw();
#endif

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////