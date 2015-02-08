//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_core_threadlocalstorage__
#define __nimble_core_threadlocalstorage__

//////////////////////////////////////////////////////////////////////////

#include <string>
#if !defined(NIMBLE_TARGET_WIN32)
	#include <pthread.h>
#else
	#include <windows.h> 
	#include <stdio.h> 
#endif

//////////////////////////////////////////////////////////////////////////

namespace nimble{
namespace core{
    
    //! pthread thread local storage impl
    template <typename T>
    class ThreadLocalStorage{
    private:
        
#if !defined(NIMBLE_TARGET_WIN32)
        pthread_key_t m_key;
#else
        DWORD m_key;
#endif
        
    public:
        
        //! Constructor
        ThreadLocalStorage(){
#if !defined(NIMBLE_TARGET_WIN32)
            pthread_key_create(&m_key, 0);
#else
            m_key = TlsAlloc();
#endif
        }
        //! Destructor
        virtual ~ThreadLocalStorage(){
#if !defined(NIMBLE_TARGET_WIN32)
            pthread_key_delete(m_key);
#else
            TlsFree(m_key);
#endif
        }
        
    public:
        
        //! asignment operator
        ThreadLocalStorage& operator=(T* p){
#if !defined(NIMBLE_TARGET_WIN32)
            pthread_setspecific(m_key, p);
            return *this;
#else
            TlsSetValue(m_key, p);
            return *this;
#endif
        }
        //! not operator
        bool operator!(){
#if !defined(NIMBLE_TARGET_WIN32)
            return pthread_getspecific(m_key) == 0;
#else
            return TlsGetValue(m_key) == 0;
#endif
        }
        //! pointer access operator
        T* operator->(){
#if !defined(NIMBLE_TARGET_WIN32)
            return static_cast<T*>(pthread_getspecific(m_key));
#else
            return static_cast<T*>(TlsGetValue(m_key));
#endif
        }
        //! returns data
        T* get(){
#if !defined(NIMBLE_TARGET_WIN32)
            return static_cast<T*>(pthread_getspecific(m_key));
#else
            return static_cast<T*>(TlsGetValue(m_key));
#endif
        }
    };
};};

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////