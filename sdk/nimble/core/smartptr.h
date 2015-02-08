//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_core_smartptr_h__
#define __nimble_core_smartptr_h__

//////////////////////////////////////////////////////////////////////////

#include <nimble/core/thread.mutex.h>
#include <nimble/core/assert.h>
#include <string>

//////////////////////////////////////////////////////////////////////////

namespace nimble{
namespace core{

    //! reference count ownership policy
    template <typename T>
    class ReferenceCountOwnershipPolicy{
    public:
    
        int32_t     *m_pRefCount;
        core::Mutex     *m_pLock;
    
    public:
    
        //! Constructor
        ReferenceCountOwnershipPolicy()
        :m_pRefCount(0)
        ,m_pLock(0){
            clone();
        }
        //! copy constructor
        ReferenceCountOwnershipPolicy(const ReferenceCountOwnershipPolicy<T>& rhs)
        :m_pRefCount(rhs.m_pRefCount)
        ,m_pLock(rhs.m_pLock){
            core::assert_warn(m_pRefCount != 0, "The reference count policy is storing a 0 reference counter");
            core::assert_warn(m_pLock != 0, "The reference count policy is storing a 0 lock");
            clone();
        }
        //! copy constructor
        template <typename K>
        ReferenceCountOwnershipPolicy(const K& rhs)
        :m_pRefCount(rhs.m_pRefCount)
        ,m_pLock(rhs.m_pLock){
            core::assert_warn(m_pRefCount != 0, "The reference count policy is storing a 0 reference counter");
            core::assert_warn(m_pLock != 0, "The reference count policy is storing a 0 lock");
            clone();
        }
    
    protected:
    
        //! Destructor
        ~ReferenceCountOwnershipPolicy(){
            release();
        }
    
    public:
    
        //! clone
        void clone(){
            if(!m_pRefCount){
                m_pRefCount = new /*( external dynamic )*/ int32_t(0);
                m_pLock = new /*( external dynamic )*/ core::Mutex();
            }
            this->incrementCounter();
        }
        //! release
        void release(){
            this->decrementCounter();
            if(*m_pRefCount == 0){
                delete m_pRefCount;
                m_pRefCount = 0;
                delete m_pLock;
                m_pLock = 0;
            }
        }
        //! checks if this is the last reference
        bool isLast(){
            core::ScopedLock lock(m_pLock);
            return (*m_pRefCount == 1);
        }
    
    private:
    
        void incrementCounter(){
            core::ScopedLock lock(m_pLock);
            (*m_pRefCount) += 1;
        }
        void decrementCounter(){
            core::ScopedLock lock(m_pLock);
            (*m_pRefCount) -= 1;
        }
    
    protected:
    
        //! swaps two pointers
        void swap(ReferenceCountOwnershipPolicy& rhs){
            core::ScopedLock lock(m_pLock);
            std::swap(m_pRefCount, rhs.m_pRefCount);
            std::swap(m_pLock, rhs.m_pLock);
        }
    };

    //! default lock policy (passthrough)
    template <typename T>
    class DefaultLockPolicy{
    public:
    
        T *m_pPointee;
    
    public:
    
        //! Constructor
        DefaultLockPolicy(T *pPointee)
        :m_pPointee(pPointee){
        }
        //! Destructor
        ~DefaultLockPolicy(){
        }
        //! operator
        operator T*(){
            return m_pPointee;
        }
        //! arrow operator
        T* operator->(){
            return m_pPointee;
        }
    
        //! operator
        operator T&(){
            return *m_pPointee;
        }
        //! reference operator
        T& operator*(){
            return m_pPointee;
        }
    };

    //! thread safe lock policy
    template <typename T>
    class ThreadSafeLockPolicy{
    public:
    
        T *m_pPointee;
    
    public:
    
        //! Constructor
        ThreadSafeLockPolicy(T *pPointee)
        :m_pPointee(pPointee){
            if(m_pPointee){
                m_pPointee->lock();
            }
        }
        //! Destructor
        ~ThreadSafeLockPolicy(){
            if(m_pPointee){
                m_pPointee->unlock();
            }
        }
    
        //! operator
        operator T*(){
            return m_pPointee;
        }
        //! pointer operator
        T* operator->(){
            return m_pPointee;
        }
    
        //! operator
        operator T&(){
            return *m_pPointee;
        }
        //! reference operator
        T& operator*(){
            return m_pPointee;
        }
    };

    //! default storage policy
    template <typename T>
    class DefaultStoragePolicy{
    public:
    
        typedef T           Type;
        typedef T           *PointerType;
        typedef const T     *ConstPointerType;
        typedef T&			ReferenceType;
        typedef const T&	ConstReferenceType;
    
    public:
    
        PointerType         m_pPointee;
    
    public:
    
        //! Constructor
        DefaultStoragePolicy()
        :m_pPointee(0){
        }
        //! Constructor
        DefaultStoragePolicy(PointerType pPointee)
        :m_pPointee(pPointee){
        }
        //! copy constructor
        DefaultStoragePolicy(const DefaultStoragePolicy<T>& rhs)
        :m_pPointee(rhs.m_pPointee){
        }
        //! copy constructor
        template <typename K>
        DefaultStoragePolicy(const K& rhs)
        :m_pPointee(dynamic_cast<T*>(rhs.m_pPointee)){
        }
    
    protected:
    
        //! Destructor
        ~DefaultStoragePolicy(){
        }
    
    public:
    
        //! arrow operator
        PointerType operator->() const{
            return m_pPointee;
        }
        //! dereference operator
        ReferenceType operator*() const{
            return *m_pPointee;
        }
    
        //! returns the pointer
        PointerType getPointer() const{
            return m_pPointee;
        }
        //! returns the const pointer
        ConstPointerType getConstPointer() const{
            return m_pPointee;
        }
    
        //! Destroy
        void destroy(){
            delete m_pPointee;
            m_pPointee = 0;
        }
        //! checks if this pointer is valid
        bool isValid() const{
            return 0 != m_pPointee;
        }
    
    protected:
    
        //! swaps two pointers
        void swap(DefaultStoragePolicy& rhs){ 
            std::swap(m_pPointee, rhs.m_pPointee); 
        }
    };

    //! smart pointer implementation
    template <typename T, 
    typename STORAGE_POLICY = DefaultStoragePolicy<T>, 
    typename LOCK_POLICY = DefaultLockPolicy<T>, 
    typename OWNERSHIP_POLICY = ReferenceCountOwnershipPolicy<T> >
    class SmartPtr
    :public STORAGE_POLICY
    ,public OWNERSHIP_POLICY{
    public:
    
        typedef STORAGE_POLICY                      SP;
        typedef LOCK_POLICY                         LP;
        typedef OWNERSHIP_POLICY                    OP;
    
        typedef typename SP::Type                   Type;
        typedef typename SP::PointerType            PointerType;
        typedef typename SP::ConstPointerType       ConstPointerType;
        typedef typename SP::ReferenceType          ReferenceType;
        typedef typename SP::ConstReferenceType     ConstReferenceType;
    
    public:
    
        //! Constructor
        SmartPtr(){
        }
        //! Constructor
        SmartPtr(PointerType pPointee)
        :SP(pPointee){
        }
        //! copy constructor
        SmartPtr(const SmartPtr<T, SP, LP, OP>& rhs)
        :SP(rhs)
        ,OP(rhs){
        }
        //! copy constructor
        template <typename K>
        SmartPtr(const K& rhs)
        :SP(rhs)
        ,OP(rhs){
        }
        //! Destructor
        ~SmartPtr(){
            if(OP::isLast()){
                SP::destroy();
            }
        }
    
    public:
    
        //! arrow operator
        PointerType operator->(){
            return LP(SP::operator->());
        }
        //! arrow operator
        PointerType operator->() const{
            return LP(SP::operator->());
        }
        //! dereference operator
        ReferenceType operator*(){
            return LP(&SP::operator*());
        }
    
    public:
    
        //! assignment operator
        SmartPtr<T, SP, LP, OP>& operator= (SmartPtr<T, SP, LP, OP>& rhs){
            SmartPtr<T, SP, LP, OP> temp(rhs);
            temp.swap(*this);
            return *this;
        }
        //! assignment operator
        template <typename K>
        SmartPtr<T, SP, LP, OP>& operator= (const K& rhs){
            SmartPtr<T, SP, LP, OP> temp(rhs);
            temp.swap(*this);
            return *this;
        }
    
    public:
    
        //! comparison operator
        bool operator== (ConstPointerType rhs) const{
            return SP::getConstPointer() == rhs;
        }
        //! comparison operator
        bool operator!= (ConstPointerType rhs) const{
            return SP::getConstPointer() != rhs;
        }
        //! comparison operator
        bool operator== (const SmartPtr<T, SP, LP, OP>& rhs) const{
            return SP::getConstPointer() == rhs.getConstPointer();
        }
        //! comparison operator
        bool operator!= (const SmartPtr<T, SP, LP, OP>& rhs) const{
            return SP::getConstPointer() != rhs.getConstPointer();
        }
    
    protected:
    
        //! swaps two pointers
        void swap(SmartPtr<T, SP, LP, OP>& rhs){
            SP::swap(rhs);
            OP::swap(rhs);
        }
    };
};};

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////