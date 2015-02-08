//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_core_future__
#define __nimble_core_future__

//////////////////////////////////////////////////////////////////////////

#include <nimble/core/smartptr.h>
#include <nimble/core/runloop.h>
#include <nimble/core/thread.h>
#include <nimble/core/thread.mutex.h>
#include <nimble/core/thread.condition.h>

//////////////////////////////////////////////////////////////////////////

namespace nimble{
namespace core{

    template <typename T = void*> class Future;
    template <typename T = void*> class Promise;

    //////////////////////////////////////////////////////////////////////////
    
    // SharedValue - a wrapper around a shared results value. Both the promise
    // and the future has a smart pointer reference to the SharedValue.
    //
    // Promise - a future provider and setter of the SharedValue. The callee
    // will create a promise and return a future to the caller. Once the promise
    // has been fullfilled, the future get will be unblocked or a continuation
    // will be called.
    //
    // Future - a future waits (blocks) when accessing the SharedValue results,
    // or calls a continuation when the SharedValue has been fullfilled.
    
    //////////////////////////////////////////////////////////////////////////
    
    typedef core::SmartPtr<core::Mutex> MutexPtr;
    typedef core::SmartPtr<core::Condition> ConditionPtr;

    //////////////////////////////////////////////////////////////////////////

    // TODO: consider making exceptions objects (eg. std::exception) instead of int32_t
    enum eFutureExceptions{
        kExceptionBrokenPromise = -1,
    };
    
    //////////////////////////////////////////////////////////////////////////
    
    //! A shared value that is satisfied (set) by a promise and
    //! retreived (get) by a future
    template <typename T>
    class SharedValue{
    private:
        T m_value;
        int32_t m_exception;
        bool m_hasValue;
        bool m_hasException;
        MutexPtr m_mutex;
        ConditionPtr m_condition;
    public:
        //! Constructor
        SharedValue(MutexPtr const &mutex, ConditionPtr const &condition);
        //! Destructor
        virtual ~SharedValue();
    public:
        //! sets a value
        virtual void set(T value);
        //! sets a exception
        virtual void setException(int exception);
        //! blocks until future has results
        virtual T& get();
        //! checks if the value is ready
        virtual bool isReady() const;
    private:
        //! notifies that a value has been set
        virtual void notify();
    };
    
    //! An object that provides a future and manages the fullfillment of a shared value
    template <typename T>
    class Promise{
    public:
        typedef core::SharedValue<T>        SharedValue;
        typedef core::SmartPtr<SharedValue> SharedValuePtr;
    private:
        SharedValuePtr m_sharedValue;
        MutexPtr m_mutex;
        ConditionPtr m_condition;
    public:
        //! Constructor
        Promise();
        //! Constructor
        Promise(Promise<T> const &promise);
        //! Destructor
        virtual ~Promise();
    public:
        Promise<T>& operator=(Promise<T> const &promise);
        //! returns a future to this promise
        virtual Future<T> getFuture();
        //! sets a exception for this promise
        virtual void setException(int exception);
        //! sets a value for this promise
        virtual void set(T value);
        //! sets a value for this promise
        virtual void operator=(T value);
    };
    
    //! Represents a value to be fullfilled at a later time
    //! The user can either call get (which blocks until the value is fullfilled)
    //! or the user can set a continuation callback (which is called when the value is fullfilled)
    //! The continuation callback always happens on the thread that it was registered on
    template <typename T>
    class Future{
    public:
        typedef core::Functor<void, TLIST_1(Future<T>&)> Continuation;
        typedef core::SharedValue<T>        SharedValue;
        typedef core::SmartPtr<SharedValue> SharedValuePtr;
    private:
        SharedValuePtr m_sharedValue;
        Continuation m_continuation;
        core::IRunLoop *m_pOperationRunLoop;
        RunLoopOperation m_operation;
    public:
        Future(SharedValuePtr const &sharedValue);
        //! Constructor
        Future(Future<T> const &future);
        //! Constructor
        Future();
        //! Destructor
        virtual ~Future();
    public:
        //! Equality operator
        bool operator==(Future<T> const &future);
        //! Assignment operator
        Future<T>& operator=(Future<T> const &future);
        //! returns the shared value
        T& operator->();
        //! returns the shared value
        T& get();
        
        //! continuation
        void then(Continuation continuation, core::IRunLoop *pRunLoop = 0);
        //! continuation
        template <typename R>
        core::Future<R> then(core::Functor<R, TLIST_1(Future<T>&)> const &continuation, core::IRunLoop *pRunLoop = 0);
        
        //! returns true if valid
        bool isValid() const;
        //! returns true if value is ready
        bool isReady() const;
    private:
        //! check if
        void checkFutureWasFullfilled();
    };
    
    //////////////////////////////////////////////////////////////////////////
    
    //! Constructor
    template <typename T>
    SharedValue<T>::SharedValue(MutexPtr const &mutex, ConditionPtr const &condition)
    :m_hasValue(false)
    ,m_hasException(false)
    ,m_mutex(mutex)
    ,m_condition(condition){
    }
    //! Destructor
    template <typename T>
    SharedValue<T>::~SharedValue(){
    }
    //! sets a value
    template <typename T>
    void SharedValue<T>::set(T value){
        core::ScopedLock lock(&(*m_mutex));
        if(m_hasValue){return;}
        m_value = value;
        m_hasValue = true;
        notify();
    }
    //! sets a exception
    template <typename T>
    void SharedValue<T>::setException(int exception){
        core::ScopedLock lock(&(*m_mutex));
        if(m_hasException){return;}
        m_exception = exception;
        m_hasException = true;
        notify();
    }
    //! blocks until future has results
    template <typename T>
    T& SharedValue<T>::get(){
        core::ScopedLock lock(&(*m_mutex));
        if(m_hasException){
            throw m_exception;
        }else{
            while(!m_hasValue){
                m_condition->wait(&(*m_mutex));
            }
        }
        return m_value;
    }
    //! checks if the value is ready
    template <typename T>
    bool SharedValue<T>::isReady() const{
        return m_hasValue || m_hasException;
    }
    //! notifies that a value has been set
    template <typename T>
    void SharedValue<T>::notify(){
        core::ScopedLock lock(&(*m_mutex));
        m_condition->broadcast();
    }
    
    //////////////////////////////////////////////////////////////////////////
    
    //! Constructor
    template <typename T>
    Promise<T>::Promise(){
        m_mutex = new /*( ??? )*/ core::Mutex();
        m_condition = new /*( ??? )*/ core::Condition();
        m_sharedValue = new /*( ??? )*/ core::SharedValue<T>(m_mutex, m_condition);
    }
    //! Constructor
    template <typename T>
    Promise<T>::Promise(Promise<T> const &promise){
        if(m_sharedValue.isValid() && m_sharedValue->isReady() == false){
            m_sharedValue->setException(kExceptionBrokenPromise);
        }
        
        m_mutex = promise.m_mutex;
        m_condition = promise.m_condition;
        m_sharedValue = promise.m_sharedValue;
    }
    //! Destructor
    template <typename T>
    Promise<T>::~Promise(){
    }
    //! Assignment operator
    template <typename T>
    Promise<T>& Promise<T>::operator=(Promise<T> const &promise){
        if(m_sharedValue.isValid() && m_sharedValue->isReady() == false){
            m_sharedValue->setException(kExceptionBrokenPromise);
        }
        m_mutex = promise.m_mutex;
        m_condition = promise.m_condition;
        m_sharedValue = promise.m_sharedValue;
        return *this;
    }
    //! returns a future to this promise
    template <typename T>
    Future<T> Promise<T>::getFuture(){
        return Future<T>(m_sharedValue);
    }
    //! sets a exception for this promise
    template <typename T>
    void Promise<T>::setException(int exception){
        m_sharedValue->setException(exception);
    }
    //! sets a value for this promise
    template <typename T>
    void Promise<T>::set(T value){
        m_sharedValue->set(value);
    }
    //! sets a value for this promise
    template <typename T>
    void Promise<T>::operator=(T value){
        m_sharedValue->set(value);
    }
    
    //////////////////////////////////////////////////////////////////////////

    //! Fullfills a promise
    template <typename R, typename T>
    void fullfillPromise(core::Promise<R> promise, core::Functor<R, TLIST_1(core::Future<T>&)> continuation, core::Future<T> &future){
        R results = continuation(future);
        promise.set(results);
    }
    
    //! Constructor
    template <typename T>
    Future<T>::Future(SharedValuePtr const &sharedValue)
    :m_sharedValue(sharedValue)
    ,m_pOperationRunLoop(0)
    ,m_operation(core::RunLoopOperation(this, &core::Future<T>::checkFutureWasFullfilled)){
    }
    //! Constructor
    template <typename T>
    Future<T>::Future(Future<T> const &future)
    :m_sharedValue(future.m_sharedValue)
    ,m_continuation(future.m_continuation)
    ,m_operation(core::RunLoopOperation(this, &core::Future<T>::checkFutureWasFullfilled)){
        if(m_continuation.isValid()){
            m_pOperationRunLoop = future.m_pOperationRunLoop;
            m_pOperationRunLoop->addLoopOperation(m_operation);
        }
    }
    //! Constructor
    template <typename T>
    Future<T>::Future()
    :m_pOperationRunLoop(0)
    ,m_operation(core::RunLoopOperation(this, &core::Future<T>::checkFutureWasFullfilled)){
    }
    //! Destructor
    template <typename T>
    Future<T>::~Future(){
        if(m_continuation.isValid() && m_pOperationRunLoop){
            m_pOperationRunLoop->removeLoopOperation(m_operation);
        }
        m_pOperationRunLoop = 0;
    }
    //! Equality operator
    template <typename T>
    bool Future<T>::operator==(Future<T> const &future){
        return (m_sharedValue == future.m_sharedValue) &&
        (m_continuation == future.m_continuation) &&
        (m_pOperationRunLoop == future.m_pOperationRunLoop) &&
        (m_operation == future.m_operation);
    }
    //! Assignment operator
    template <typename T>
    Future<T>& Future<T>::operator=(Future<T> const &future){
        if(m_continuation.isValid() && m_pOperationRunLoop){
            m_pOperationRunLoop->removeLoopOperation(m_operation);
        }
        
        m_sharedValue = future.m_sharedValue;
        m_continuation = future.m_continuation;
        m_pOperationRunLoop = 0;
        
        if(m_continuation.isValid()){
            m_pOperationRunLoop = core::getCurrentRunLoop();
            m_pOperationRunLoop->addLoopOperation(m_operation);
        }
        
        return *this;
    }
    //! returns the shared value
    template <typename T>
    T& Future<T>::operator->(){
        return m_sharedValue->get();
    }
    //! returns the shared value
    template <typename T>
    T& Future<T>::get(){
        return m_sharedValue->get();
    }
    
    //! continuation
    template <typename T>
    void Future<T>::then(Continuation continuation, core::IRunLoop *pRunLoop){
        // if the previous continuation and operation run loop is valid
        // remove it before registering the new continuation
        if(m_continuation.isValid() && m_pOperationRunLoop){
            m_pOperationRunLoop->removeLoopOperation(m_operation);
        }
        
        // if input continuation is not valid, invalidate this future
        if(!continuation.isValid()){
            m_continuation = Continuation();
            m_pOperationRunLoop = 0;
            return;
        }
        
        // set runloop and continuation
        m_continuation = continuation;
        if(pRunLoop){
            m_pOperationRunLoop = pRunLoop;
        }else{
            m_pOperationRunLoop = core::getMainRunLoop();
        }
        
        // add operation to our runloop which will check
        // shared value on every runloop
        m_pOperationRunLoop->addLoopOperation(m_operation);
    }
    //! continuation
    template <typename T> template <typename R>
    core::Future<R> Future<T>::then(core::Functor<R, TLIST_1(Future<T>&)> const &continuation, core::IRunLoop *pRunLoop){
        // if the previous continuation and operation run loop is valid
        // remove it before registering the new continuation
        if(m_continuation.isValid() && m_pOperationRunLoop){
            m_pOperationRunLoop->removeLoopOperation(m_operation);
        }
        
        // wrap our input continuation
        core::Promise<R> promise;
        typedef core::Functor<R, TLIST_1(core::Future<T>&)> ContinuationType;
        typedef core::Promise<R> PromiseType;
        typedef core::Future<T> FutureType;
        m_continuation =  core::bindFirst<void, ContinuationType, FutureType&>(core::bindFirst<void, PromiseType, ContinuationType, FutureType&>(fullfillPromise<R, T>, promise), continuation);
        m_pOperationRunLoop = 0;
        
        if(m_continuation.isValid()){
            if(pRunLoop){
                m_pOperationRunLoop = pRunLoop;
            }else{
                m_pOperationRunLoop = core::getMainRunLoop();
            }
            m_pOperationRunLoop->addLoopOperation(m_operation);
        }
        return promise.getFuture();
    }
    //! returns true if valid
    template <typename T>
    bool Future<T>::isValid() const{
        return m_sharedValue.isValid();
    }
    //! returns true if value is ready
    template <typename T>
    bool Future<T>::isReady() const{
        if(m_sharedValue.isValid()){
            return m_sharedValue->isReady();
        }else{
            return false;
        }
    }
    //! check if
    template <typename T>
    void Future<T>::checkFutureWasFullfilled(){
        if(m_sharedValue->isReady()){
            // the check should only be valid once, which means if
            // it was valid, we stop checking
            m_pOperationRunLoop->removeLoopOperation(m_operation);
            m_pOperationRunLoop = 0;
            
            // call continuation with our future
            // the owner of the callback should manually call
            // future.get(), which will either return a valid
            // return or throw an exception.
            m_continuation(*this);
            m_continuation = Continuation();
        }
    }

    //////////////////////////////////////////////////////////////////////////
    
//    //! thread main helper data payload
//    template <typename Func>
//    struct AsyncThreadData{
//        typedef core::Promise<typename Func::ResultType> PromiseType;
//
//        AsyncThreadData(Func func)
//        :m_func(func){
//        }
//
//        PromiseType m_promise;
//        Func        m_func;
//    };
//    //! thread main helper function
//    template <typename Func>
//    void* asyncThreadMain(void *pData){
//        AsyncThreadData<Func> *asyncThreadData = (AsyncThreadData<Func>*)pData;
//        asyncThreadData->m_promise.set(asyncThreadData->m_func());
//        delete asyncThreadData;
//        return 0;
//    }
//    //! executes a functor job
//    template <typename Func>
//    class AsyncFunctorTask
//    : public core::Task{
//    public:
//        AsyncThreadData<Func> *m_pData;
//    public:
//        //! constructor
//        AsyncFunctorTask(AsyncThreadData<Func> *pData)
//        :m_pData(pData){
//        }
//        //! destructor
//        virtual ~AsyncFunctorTask(){
//        }
//        //! execute
//        virtual void execute(){
//            m_pData->m_promise.set(m_pData->m_func());
//            delete m_pData;
//        }
//    };
//    
//    //! an async callback mechanism
//    template <typename Func>
//    core::Future<typename Func::ResultType> async(Func func, core::ThreadPool *pThreadPool = 0){
//        typedef core::Promise<typename Func::ResultType>    PromiseType;
//        typedef typename PromiseType::FutureType            FutureType;
//        
//        if(pThreadPool){
//            // note: we should be careful here. Thread pools should consume
//            // jobs that are non-blocking. Futures (and promise pipeling) are blocking
//            // concepts which may result in deadlock.
//            
//            // start our job
//            AsyncThreadData<Func> *pData = new /*( ??? )*/ AsyncThreadData<Func>(func);
//            FutureType future = pData->m_promise.getFuture();
//            pThreadPool->executeAsyncTask(new /*( ??? )*/ AsyncFunctorTask<Func>(pData));
//            return future;
//        }else{
//            // note: we create a detached thread which is
//            // not joinable, but cleans up resources when the thread
//            // has finished running
//            pthread_t thread;
//            pthread_attr_t threadAttr;
//            
//            // create thread attributes
//            pthread_attr_init(&threadAttr);
//            
//            // set thread attribute parameters
//            struct sched_param param;
//            pthread_attr_getschedparam(&threadAttr, &param);
//            
//            // set our thread params / attributes
//            pthread_attr_setschedparam(&threadAttr, &param);
//            pthread_attr_setdetachstate(&threadAttr, PTHREAD_CREATE_DETACHED);
//            
//            // start our thread (detached)
//            AsyncThreadData<Func> *pData = new AsyncThreadData<Func>(func);
//            FutureType future = pData->m_promise.getFuture();
//            int error = pthread_create(&thread, &threadAttr, core::asyncThreadMain<Func>, (void *)pData);
//            core::assert_error(error == 0, "[ThreadRunLoop] error %s", strerror(error));
//            return future;
//        }
//    }
};};

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////