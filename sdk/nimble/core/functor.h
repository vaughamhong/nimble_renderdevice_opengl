//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_core_functor__
#define __nimble_core_functor__

//////////////////////////////////////////////////////////////////////////

#include <memory>
#include <nimble/core/typelist.h>

//////////////////////////////////////////////////////////////////////////

namespace nimble{
namespace core{

    //////////////////////////////////////////////////////////////////////////
    
    // Functors are generic function objects that wraps a function (in global
    // scope or object instance scope, and can be passed as a parameter,
    // returned from a subroutine, and assigned. Functors transform functions
    // into first class objects.
    //
    // Our Functors are inspired by the work of Alexandrescu, Meyers, Vlissides
    // and their implementation in their book "Modern C++ Design".
    // http://www.moderncppdesign.com/book/main.html
    
    //////////////////////////////////////////////////////////////////////////
    
    // Abstract functor base class
    template <typename R, class TList>
    class IFunctor{
    public:
        virtual ~IFunctor(){}
        virtual IFunctor* clone() const = 0;
        virtual bool equals(IFunctor *pFunc) const = 0;
    };
    // A functor with 0 parameter(s)
    template <typename R>
    class IFunctor<R, NullType>{
    public:
        virtual ~IFunctor(){}
        virtual R operator()() = 0;
        virtual IFunctor* clone() const = 0;
        virtual bool equals(IFunctor *pFunc) const = 0;
    };
    // A functor with 1 parameter(s)
    template <typename R, typename T1>
    class IFunctor<R, TLIST_1(T1)>{
    public:
        virtual ~IFunctor(){}
        virtual R operator()(T1 t1) = 0;
        virtual IFunctor* clone() const = 0;
        virtual bool equals(IFunctor *pFunc) const = 0;
    };
    // A functor with 2 parameter(s)
    template <typename R, typename T1, typename T2>
    class IFunctor<R, TLIST_2(T1, T2)>{
    public:
        virtual ~IFunctor(){}
        virtual R operator()(T1 t1, T2 t2) = 0;
        virtual IFunctor* clone() const = 0;
        virtual bool equals(IFunctor *pFunc) const = 0;
    };
    // A functor with 3 parameter(s)
    template <typename R, typename T1, typename T2, typename T3>
    class IFunctor<R, TLIST_3(T1, T2, T3)>{
    public:
        virtual ~IFunctor(){}
        virtual R operator()(T1 t1, T2 t2, T3 t3) = 0;
        virtual IFunctor* clone() const = 0;
        virtual bool equals(IFunctor *pFunc) const = 0;
    };
    // A functor with 4 parameter(s)
    template <typename R, typename T1, typename T2, typename T3, typename T4>
    class IFunctor<R, TLIST_4(T1, T2, T3, T4)>{
    public:
        virtual ~IFunctor(){}
        virtual R operator()(T1 t1, T2 t2, T3 t3, T4 t4) = 0;
        virtual IFunctor* clone() const = 0;
        virtual bool equals(IFunctor *pFunc) const = 0;
    };
    // A functor with 4 parameter(s)
    template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5>
    class IFunctor<R, TLIST_5(T1, T2, T3, T4, T5)>{
    public:
        virtual ~IFunctor(){}
        virtual R operator()(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5) = 0;
        virtual IFunctor* clone() const = 0;
        virtual bool equals(IFunctor *pFunc) const = 0;
    };
    
    //////////////////////////////////////////////////////////////////////////
    
    // The following handlers represents various calling conventions.
    // Each handler self contains everything it needs to call a method. For
    // example the FunctorHandler contains everything it needs to call a
    // non member function. The core::Functor generically wraps these
    // specializations, to be invoked.
    
    // Handles routing call to function pointer
    template <class Prototype, typename Func>
    class FunctorHandler
    : public IFunctor<typename Prototype::ResultType, typename Prototype::ParamList>{
    public:
        
        typedef typename Prototype::ParamList ParamList;
        typedef typename Prototype::ResultType ResultType;
        typedef typename Prototype::Param1 Param1;
        typedef typename Prototype::Param2 Param2;
        typedef typename Prototype::Param3 Param3;
        typedef typename Prototype::Param4 Param4;
        typedef typename Prototype::Param5 Param5;
        
        typedef IFunctor<typename Prototype::ResultType, typename Prototype::ParamList> BaseType;
        
    public:
        
        //! Copy constructor
        FunctorHandler(Func const &func):m_pFunc(func){}
        
        //! Clones this handler
        virtual BaseType* clone() const{
            return new /*( pool )*/ FunctorHandler<Prototype, Func>(*m_pFunc);
        }
        //! Returns true if function pointers are equal
        virtual bool equals(BaseType *pImpl) const{
            // make sure the input functor is a FunctorHandler (function pointer handler)
            if(FunctorHandler<Prototype, Func> *pConcrete = dynamic_cast<FunctorHandler<Prototype, Func>*>(pImpl)){
                return pConcrete->m_pFunc == m_pFunc;
            }
            return false;
        }
        
    public:
        
        inline ResultType operator()(){
            return m_pFunc();
        }
        inline ResultType operator()(Param1 p1){
            return m_pFunc(p1);
        }
        inline ResultType operator()(Param1 p1, Param2 p2){
            return m_pFunc(p1, p2);
        }
        inline ResultType operator()(Param1 p1, Param2 p2, Param3 p3){
            return m_pFunc(p1, p2, p3);
        }
        inline ResultType operator()(Param1 p1, Param2 p2, Param3 p3, Param4 p4){
            return m_pFunc(p1, p2, p3, p4);
        }
        inline ResultType operator()(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5){
            return m_pFunc(p1, p2, p3, p4, p5);
        }
        
    private:
        
        Func *m_pFunc;  // pointer to our functionc all
    };
    
    // Handles routing call to member functions
    template <class Prototype, typename ObjType, typename Func>
    class MemberFunctorHandler
    : public IFunctor<typename Prototype::ResultType, typename Prototype::ParamList>{
    public:
        
        typedef typename Prototype::ParamList ParamList;
        typedef typename Prototype::ResultType ResultType;
        typedef typename Prototype::Param1 Param1;
        typedef typename Prototype::Param2 Param2;
        typedef typename Prototype::Param3 Param3;
        typedef typename Prototype::Param4 Param4;
        typedef typename Prototype::Param5 Param5;
        
        typedef IFunctor<typename Prototype::ResultType, typename Prototype::ParamList> BaseType;

    public:
        
        //! Constructor
        MemberFunctorHandler(const ObjType &obj, const Func &func):m_obj(obj),m_func(func){}
        
        //! Clones this handler
        virtual BaseType* clone() const{
            return new MemberFunctorHandler<Prototype, ObjType, Func>(m_obj, m_func);
        }
        
        //! Returns true if function pointers are equal
        virtual bool equals(BaseType *pImpl) const{
            // make sure the input functor is a MemberFunctorHandler (member function handler)
            if(MemberFunctorHandler<Prototype, ObjType, Func> *pConcrete = dynamic_cast<MemberFunctorHandler<Prototype, ObjType, Func>*>(pImpl)){
                return (pConcrete->m_func == m_func) && (pConcrete->m_obj == m_obj);
            }
            return false;
        }
        
    public:
        
        inline ResultType operator()(){
            return ((*m_obj).*m_func)();
        }
        inline ResultType operator()(Param1 p1){
            return ((*m_obj).*m_func)(p1);
        }
        inline ResultType operator()(Param1 p1, Param2 p2){
            return ((*m_obj).*m_func)(p1, p2);
        }
        inline ResultType operator()(Param1 p1, Param2 p2, Param3 p3){
            return ((*m_obj).*m_func)(p1, p2, p3);
        }
        inline ResultType operator()(Param1 p1, Param2 p2, Param3 p3, Param4 p4){
            return ((*m_obj).*m_func)(p1, p2, p3, p4);
        }
        inline ResultType operator()(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5){
            return ((*m_obj).*m_func)(p1, p2, p3, p4, p5);
        }
        
    private:
        
        ObjType m_obj;  // pointer to our object
        Func m_func;    // pointer to our method call
    };
    
    // Handles routing call to bound functors
    template <class Func, class TList = NullType>
    class BindAllFunctor
    : public IFunctor<typename Func::ResultType, TList>{
    };
    
    // Binds first parameter
    template <class Func, class TList = NullType>
    class BindFirstFunctor
    : public IFunctor<typename Func::ResultType, TList>{
    };
    
    //////////////////////////////////////////////////////////////////////////
    
    // Functor implementation
    template <typename R, class TList = core::NullType>
    class Functor{
    public:
        
        typedef TList ParamList;
        typedef R ResultType;
        
        typedef typename TListTypeAt<TList, 0>::Result Param1;
        typedef typename TListTypeAt<TList, 1>::Result Param2;
        typedef typename TListTypeAt<TList, 2>::Result Param3;
        typedef typename TListTypeAt<TList, 3>::Result Param4;
        typedef typename TListTypeAt<TList, 4>::Result Param5;
        
        typedef IFunctor<R, TList> Impl;
                
        Impl *m_pImpl;
        
    public:
        
        //! default constructor
        Functor()
        :m_pImpl(0){
        }
        //! copy constructor
        Functor(Functor const &func)
        :m_pImpl(func.clone()){
        }
        //! routes calls to function pointer
        template <typename Func>
        Functor(Func const &func)
        :m_pImpl(new FunctorHandler<Functor, Func>(func)){
        }
        //! routes calls to object method
        template <typename ObjType, typename Func>
        Functor(const ObjType &obj, Func const &func)
        :m_pImpl(new MemberFunctorHandler<Functor, ObjType, Func>(obj, func)){
        }
        //! routes calls to bound functor
        template <class Func>
        Functor(BindAllFunctor<Func> const &func)
        :m_pImpl(new BindAllFunctor<Func>(func)){
        }
        //! routes calls to bound functor
        template <class Func>
        Functor(BindFirstFunctor<Func> const &func)
        :m_pImpl(new BindFirstFunctor<Func>(func)){
        }
        //! Destructor
        virtual ~Functor(){
            delete m_pImpl;
            m_pImpl = 0;
        }
        
    public:
        
        //! copies the input functor
        virtual Functor<R, TList> operator=(Functor const &func){
            if(m_pImpl != 0){delete m_pImpl; m_pImpl = 0;}
            m_pImpl = func.clone();
            return *this;
        }
        //! checks if this functor is equal to the input functor
        virtual bool operator==(Functor const &func){
            return func.m_pImpl->equals(this->m_pImpl);
        }
        
        //! clone
        virtual Impl* clone() const{
            if(m_pImpl != 0){
                return m_pImpl->clone();
            }else{
                return 0;
            }
        }
        //! is valid
        virtual bool isValid() const{
            return m_pImpl != 0;
        }
        
    public:
        
        inline R operator()() const{
            return (*m_pImpl)();
        }
        inline R operator()(Param1 p1) const{
            return (*m_pImpl)(p1);
        }
        inline R operator()(Param1 p1, Param2 p2) const{
            return (*m_pImpl)(p1, p2);
        }
        inline R operator()(Param1 p1, Param2 p2, Param3 p3) const{
            return (*m_pImpl)(p1, p2, p3);
        }
        inline R operator()(Param1 p1, Param2 p2, Param3 p3, Param4 p4) const{
            return (*m_pImpl)(p1, p2, p3, p4);
        }
        inline R operator()(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5) const{
            return (*m_pImpl)(p1, p2, p3, p4, p5);
        }
    };
    
    //////////////////////////////////////////////////////////////////////////
    
    // Binds a functor with 1 parameter(s)
    template <typename R, typename T1>
    class BindAllFunctor<Functor<R, TLIST_1(T1)> >
    : public IFunctor<R, NullType>{
    public:
        
        typedef TLIST_1(T1) TList;
        typedef Functor<R, TList> Func;
        typedef typename Func::ResultType ResultType;
        typedef typename Func::Param1 Param1;
        typedef IFunctor<R, NullType>  BaseType;

    public:

        //! Constructor
        BindAllFunctor(){}
        //! Constructor
        BindAllFunctor(const BindAllFunctor &func, Param1 p1):m_func(func.m_func), m_p1(p1){}
        //! Constructor
        BindAllFunctor(const Func &func, Param1 p1):m_func(func), m_p1(p1){}
        
    public:
        
        //! Clones this handler
        virtual BaseType* clone() const{
            return new BindAllFunctor<Func>(m_func, m_p1);
        }
        //! Returns true if function pointers are equal
        virtual bool equals(BaseType *pImpl) const{
            // make sure the input functor is a BindAllFunctor (bound function handler)
            if(BindAllFunctor *pConcrete = dynamic_cast<BindAllFunctor*>(pImpl)){
                return (pConcrete->m_func == m_func);
            }
            return false;
        }
        
    public:

        inline ResultType operator()(){
            return m_func(m_p1);
        }
        
    private:
        
        Func m_func;
        Param1 m_p1;
    };
    
    // Binds a functor with 2 parameter(s)
    template <typename R, typename T1, typename T2>
    class BindAllFunctor<Functor<R, TLIST_2(T1, T2)> >
    : public virtual IFunctor<R, NullType>{
    public:
        
        typedef TLIST_2(T1, T2) TList;
        typedef Functor<R, TList> Func;
        typedef typename Func::ResultType ResultType;
        typedef typename Func::Param1 Param1;
        typedef typename Func::Param2 Param2;
        typedef IFunctor<R, NullType>  BaseType;
        
    public:
        
        //! Constructor
        BindAllFunctor(){}
        //! Copy constructor
        BindAllFunctor(const BindAllFunctor &func, Param1 p1, Param2 p2):m_func(func.m_func), m_p1(p1), m_p2(p2){}
        //! Copy constructor
        BindAllFunctor(const Func &func, Param1 p1, Param2 p2):m_func(func), m_p1(p1), m_p2(p2){}
        
    public:
        
        //! Clones this handler
        virtual BaseType* clone() const{
            return new BindAllFunctor<Func>(m_func, m_p1, m_p2);
        }
        //! Returns true if function pointers are equal
        virtual bool equals(BaseType *pImpl) const{
            // make sure the input functor is a BindAllFunctor (bound function handler)
            if(BindAllFunctor *pConcrete = dynamic_cast<BindAllFunctor*>(pImpl)){
                return (pConcrete->m_func == m_func);
            }
            return false;
        }
        
    public:
        
        inline ResultType operator()(){
            return m_func(m_p1, m_p2);
        }
        
    private:
        
        Func m_func;
        Param1 m_p1;
        Param2 m_p2;
    };
    
    // Binds a functor with 3 parameter(s)
    template <typename R, typename T1, typename T2, typename T3>
    class BindAllFunctor<Functor<R, TLIST_3(T1, T2, T3)> >
    : public IFunctor<R, NullType>{
    public:
        
        typedef TLIST_3(T1, T2, T3) TList;
        typedef Functor<R, TList> Func;
        typedef typename Func::ResultType ResultType;
        typedef typename Func::Param1 Param1;
        typedef typename Func::Param2 Param2;
        typedef typename Func::Param3 Param3;
        typedef IFunctor<R, NullType>  BaseType;
        
    public:

        //! Constructor
        BindAllFunctor(){}
        //! Copy constructor
        BindAllFunctor(const BindAllFunctor &func, Param1 p1, Param2 p2, Param3 p3):m_func(func.m_func), m_p1(p1), m_p2(p2), m_p3(p3){}
        //! Copy constructor
        BindAllFunctor(const Func &func, Param1 p1, Param2 p2, Param3 p3):m_func(func), m_p1(p1), m_p2(p2), m_p3(p3){}

    public:
        
        //! Clones this handler
        virtual BaseType* clone() const{
            return new BindAllFunctor<Func>(m_func, m_p1, m_p2, m_p3);
        }
        //! Returns true if function pointers are equal
        virtual bool equals(BaseType *pImpl) const{
            // make sure the input functor is a BindAllFunctor (bound function handler)
            if(BindAllFunctor *pConcrete = dynamic_cast<BindAllFunctor*>(pImpl)){
                return (pConcrete->m_func == m_func);
            }
            return false;
        }
        
    public:
        
        inline ResultType operator()(){
            return m_func(m_p1, m_p2, m_p3);
        }
        
    private:
        
        Func m_func;
        Param1 m_p1;
        Param2 m_p2;
        Param3 m_p3;
    };
    
    // Binds a functor with 4 parameter(s)
    template <typename R, typename T1, typename T2, typename T3, typename T4>
    class BindAllFunctor<Functor<R, TLIST_4(T1, T2, T3, T4)> >
    : public IFunctor<R, NullType>{
    public:
        
        typedef TLIST_4(T1, T2, T3, T4) TList;
        typedef Functor<R, TList> Func;
        typedef typename Func::ResultType ResultType;
        typedef typename Func::Param1 Param1;
        typedef typename Func::Param2 Param2;
        typedef typename Func::Param3 Param3;
        typedef typename Func::Param4 Param4;
        typedef IFunctor<R, NullType>  BaseType;
        
    public:
        
        //! Constructor
        BindAllFunctor(){}
        //! Copy constructor
        BindAllFunctor(const BindAllFunctor &func, Param1 p1, Param2 p2, Param3 p3, Param4 p4):m_func(func.m_func), m_p1(p1), m_p2(p2), m_p3(p3), m_p4(p4){}
        //! Copy constructor
        BindAllFunctor(const Func &func, Param1 p1, Param2 p2, Param3 p3, Param4 p4):m_func(func), m_p1(p1), m_p2(p2), m_p3(p3), m_p4(p4){}
        
    public:
        
        //! Clones this handler
        virtual BaseType* clone() const{
            return new BindAllFunctor<Func>(m_func, m_p1, m_p2, m_p3, m_p4);
        }
        //! Returns true if function pointers are equal
        virtual bool equals(BaseType *pImpl) const{
            // make sure the input functor is a BindAllFunctor (bound function handler)
            if(BindAllFunctor *pConcrete = dynamic_cast<BindAllFunctor*>(pImpl)){
                return (pConcrete->m_func == m_func);
            }
            return false;
        }
        
    public:
        
        inline ResultType operator()(){
            return m_func(m_p1, m_p2, m_p3, m_p4);
        }
        
    private:
        
        Func m_func;
        Param1 m_p1;
        Param2 m_p2;
        Param3 m_p3;
        Param4 m_p4;
    };
    
    // Binds a functor with 4 parameter(s)
    template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5>
    class BindAllFunctor<Functor<R, TLIST_5(T1, T2, T3, T4, T5)> >
    : public IFunctor<R, NullType>{
    public:
        
        typedef TLIST_5(T1, T2, T3, T4, T5) TList;
        typedef Functor<R, TList> Func;
        typedef typename Func::ResultType ResultType;
        typedef typename Func::Param1 Param1;
        typedef typename Func::Param2 Param2;
        typedef typename Func::Param3 Param3;
        typedef typename Func::Param4 Param4;
        typedef typename Func::Param5 Param5;
        typedef IFunctor<R, NullType>  BaseType;
        
    public:
        
        //! Constructor
        BindAllFunctor(){}
        //! Copy constructor
        BindAllFunctor(const BindAllFunctor &func, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5):m_func(func.m_func), m_p1(p1), m_p2(p2), m_p3(p3), m_p4(p4), m_p5(p5){}
        //! Copy constructor
        BindAllFunctor(const Func &func, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5):m_func(func), m_p1(p1), m_p2(p2), m_p3(p3), m_p4(p4), m_p5(p5){}
        
    public:
        
        //! Clones this handler
        virtual BaseType* clone() const{
            return new BindAllFunctor<Func>(m_func, m_p1, m_p2, m_p3, m_p4, m_p5);
        }
        //! Returns true if function pointers are equal
        virtual bool equals(BaseType *pImpl) const{
            // make sure the input functor is a BindAllFunctor (bound function handler)
            if(BindAllFunctor *pConcrete = dynamic_cast<BindAllFunctor*>(pImpl)){
                return (pConcrete->m_func == m_func);
            }
            return false;
        }
        
    public:
        
        inline ResultType operator()(){
            return m_func(m_p1, m_p2, m_p3, m_p4, m_p5);
        }
        
    private:
        
        Func m_func;
        Param1 m_p1;
        Param2 m_p2;
        Param3 m_p3;
        Param4 m_p4;
        Param5 m_p5;
    };
    
    template <typename R, typename T1>
    core::Functor<R, NullType> bindAll(core::Functor<R, TLIST_1(T1)> const &func, T1 p1){
        return core::Functor<R, NullType>(core::BindAllFunctor<core::Functor<R, TLIST_1(T1)> >(func, p1));
    }
    template <typename R, typename T1, typename T2>
    core::Functor<R, NullType> bindAll(core::Functor<R, TLIST_2(T1, T2)> const &func, T1 p1, T2 p2){
        return core::Functor<R, NullType>(core::BindAllFunctor<core::Functor<R, TLIST_2(T1, T2)> >(func, p1, p2));
    }
    template <typename R, typename T1, typename T2, typename T3>
    core::Functor<R, NullType> bindAll(core::Functor<R, TLIST_3(T1, T2, T3)> const &func, T1 p1, T2 p2, T3 p3){
        return core::Functor<R, NullType>(core::BindAllFunctor<core::Functor<R, TLIST_3(T1, T2, T3)> >(func, p1, p2, p3));
    }
    template <typename R, typename T1, typename T2, typename T3, typename T4>
    core::Functor<R, NullType> bindAll(core::Functor<R, TLIST_4(T1, T2, T3, T4)> const &func, T1 p1, T2 p2, T3 p3, T4 p4){
        return core::Functor<R, NullType>(core::BindAllFunctor<core::Functor<R, TLIST_4(T1, T2, T3, T4)> >(func, p1, p2, p3, p4));
    }
    template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5>
    core::Functor<R, NullType> bindAll(core::Functor<R, TLIST_5(T1, T2, T3, T4, T5)> const &func, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5){
        return core::Functor<R, NullType>(core::BindAllFunctor<core::Functor<R, TLIST_5(T1, T2, T3, T4, T5)> >(func, p1, p2, p3, p4, p5));
    }
    
    //////////////////////////////////////////////////////////////////////////

    // Binds first parameter of a functor with 1 parameter(s)
    template <typename R, typename T1>
    class BindFirstFunctor<Functor<R, TLIST_1(T1)> >
    : public virtual IFunctor<R, NullType>{
    public:
        
        typedef TLIST_1(T1) TList;
        typedef Functor<R, TList> Func;
        typedef typename Func::ResultType ResultType;
        typedef typename Func::Param1 Param1;
        typedef IFunctor<R, NullType> BaseType;
        
    public:
        
        //! Constructor
        BindFirstFunctor(){}
        //! Copy constructor
        BindFirstFunctor(const BindFirstFunctor &func, Param1 p1):m_func(func.m_func), m_p1(p1){}
        //! Copy constructor
        BindFirstFunctor(const Func &func, Param1 p1):m_func(func), m_p1(p1){}
        
    public:
        
        //! Clones this handler
        virtual BaseType* clone() const{
            return new BindFirstFunctor<Func>(m_func, m_p1);
        }
        //! Returns true if function pointers are equal
        virtual bool equals(BaseType *pImpl) const{
            // make sure the input functor is a BindAllFunctor (bound function handler)
            if(BindFirstFunctor *pConcrete = dynamic_cast<BindFirstFunctor*>(pImpl)){
                return (pConcrete->m_func == m_func);
            }
            return false;
        }
        
    public:
        
        inline ResultType operator()(){
            return m_func(m_p1);
        }
        
    private:
        
        Func m_func;
        Param1 m_p1;
    };
    
    // Binds first parameter of a functor with 2 parameter(s)
    template <typename R, typename T1, typename T2>
    class BindFirstFunctor<Functor<R, TLIST_2(T1, T2)> >
    : public virtual IFunctor<R, TLIST_1(T2)>{
    public:
        
        typedef TLIST_2(T1, T2) TList;
        typedef Functor<R, TList> Func;
        typedef typename Func::ResultType ResultType;
        typedef typename Func::Param1 Param1;
        typedef typename Func::Param2 Param2;
        typedef IFunctor<R, TLIST_1(T2)> BaseType;
        
    public:
        
        //! Constructor
        BindFirstFunctor(){}
        //! Copy constructor
        BindFirstFunctor(const BindFirstFunctor &func, Param1 p1):m_func(func.m_func), m_p1(p1){}
        //! Copy constructor
        BindFirstFunctor(const Func &func, Param1 p1):m_func(func), m_p1(p1){}
        
    public:
        
        //! Clones this handler
        virtual BaseType* clone() const{
            return new BindFirstFunctor<Func>(m_func, m_p1);
        }
        //! Returns true if function pointers are equal
        virtual bool equals(BaseType *pImpl) const{
            // make sure the input functor is a BindAllFunctor (bound function handler)
            if(BindFirstFunctor *pConcrete = dynamic_cast<BindFirstFunctor*>(pImpl)){
                return (pConcrete->m_func == m_func);
            }
            return false;
        }
        
    public:
        
        inline ResultType operator()(Param2 p2){
            return m_func(m_p1, p2);
        }
        
    private:
        
        Func m_func;
        Param1 m_p1;
    };
    
    // Binds first parameter of a functor with 3 parameter(s)
    template <typename R, typename T1, typename T2, typename T3>
    class BindFirstFunctor<Functor<R, TLIST_3(T1, T2, T3)> >
    : public virtual IFunctor<R, TLIST_2(T2, T3)>{
    public:
        
        typedef TLIST_3(T1, T2, T3) TList;
        typedef Functor<R, TList> Func;
        typedef typename Func::ResultType ResultType;
        typedef typename Func::Param1 Param1;
        typedef typename Func::Param2 Param2;
        typedef typename Func::Param3 Param3;
        typedef IFunctor<R, TLIST_2(T2, T3)> BaseType;
        
    public:
        
        //! Constructor
        BindFirstFunctor(){}
        //! Copy constructor
        BindFirstFunctor(const BindFirstFunctor &func, Param1 p1):m_func(func.m_func), m_p1(p1){}
        //! Copy constructor
        BindFirstFunctor(const Func &func, Param1 p1):m_func(func), m_p1(p1){}
        
    public:
        
        //! Clones this handler
        virtual BaseType* clone() const{
            return new BindFirstFunctor<Func>(m_func, m_p1);
        }
        //! Returns true if function pointers are equal
        virtual bool equals(BaseType *pImpl) const{
            // make sure the input functor is a BindAllFunctor (bound function handler)
            if(BindFirstFunctor *pConcrete = dynamic_cast<BindFirstFunctor*>(pImpl)){
                return (pConcrete->m_func == m_func);
            }
            return false;
        }
        
    public:
        
        inline ResultType operator()(Param2 p2, Param3 p3){
            return m_func(m_p1, p2, p3);
        }
        
    private:
        
        Func m_func;
        Param1 m_p1;
    };
    
    // Binds first parameter of a functor with 4 parameter(s)
    template <typename R, typename T1, typename T2, typename T3, typename T4>
    class BindFirstFunctor<Functor<R, TLIST_4(T1, T2, T3, T4)> >
    : public virtual IFunctor<R, TLIST_3(T2, T3, T4)>{
    public:
        
        typedef TLIST_4(T1, T2, T3, T4) TList;
        typedef Functor<R, TList> Func;
        typedef typename Func::ResultType ResultType;
        typedef typename Func::Param1 Param1;
        typedef typename Func::Param2 Param2;
        typedef typename Func::Param3 Param3;
        typedef typename Func::Param4 Param4;
        typedef IFunctor<R, TLIST_3(T2, T3, T4)> BaseType;
        
    public:
        
        //! Constructor
        BindFirstFunctor(){}
        //! Copy constructor
        BindFirstFunctor(const BindFirstFunctor &func, Param1 p1):m_func(func.m_func), m_p1(p1){}
        //! Copy constructor
        BindFirstFunctor(const Func &func, Param1 p1):m_func(func), m_p1(p1){}
        
    public:
        
        //! Clones this handler
        virtual BaseType* clone() const{
            return new BindFirstFunctor<Func>(m_func, m_p1);
        }
        //! Returns true if function pointers are equal
        virtual bool equals(BaseType *pImpl) const{
            // make sure the input functor is a BindAllFunctor (bound function handler)
            if(BindFirstFunctor *pConcrete = dynamic_cast<BindFirstFunctor*>(pImpl)){
                return (pConcrete->m_func == m_func);
            }
            return false;
        }
        
    public:
        
        inline ResultType operator()(Param2 p2, Param3 p3, Param4 p4){
            return m_func(m_p1, p2, p3, p4);
        }
        
    private:
        
        Func m_func;
        Param1 m_p1;
    };
    
    // Binds first parameter of a functor with 5 parameter(s)
    template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5>
    class BindFirstFunctor<Functor<R, TLIST_5(T1, T2, T3, T4, T5)> >
    : public virtual IFunctor<R, TLIST_4(T2, T3, T4, T5)>{
    public:
        
        typedef TLIST_5(T1, T2, T3, T4, T5) TList;
        typedef Functor<R, TList> Func;
        typedef typename Func::ResultType ResultType;
        typedef typename Func::Param1 Param1;
        typedef typename Func::Param2 Param2;
        typedef typename Func::Param3 Param3;
        typedef typename Func::Param4 Param4;
        typedef typename Func::Param5 Param5;
        typedef IFunctor<R, TLIST_4(T2, T3, T4, T5)> BaseType;
        
    public:
        
        //! Constructor
        BindFirstFunctor(){}
        //! Copy constructor
        BindFirstFunctor(const BindFirstFunctor &func, Param1 p1):m_func(func.m_func), m_p1(p1){}
        //! Copy constructor
        BindFirstFunctor(const Func &func, Param1 p1):m_func(func), m_p1(p1){}
        
    public:
        
        //! Clones this handler
        virtual BaseType* clone() const{
            return new BindFirstFunctor<Func>(m_func, m_p1);
        }
        //! Returns true if function pointers are equal
        virtual bool equals(BaseType *pImpl) const{
            // make sure the input functor is a BindAllFunctor (bound function handler)
            if(BindFirstFunctor *pConcrete = dynamic_cast<BindFirstFunctor*>(pImpl)){
                return (pConcrete->m_func == m_func);
            }
            return false;
        }
        
    public:
        
        inline ResultType operator()(Param2 p2, Param3 p3, Param4 p4, Param5 p5){
            return m_func(m_p1, p2, p3, p4, p5);
        }
        
    private:
        
        Func m_func;
        Param1 m_p1;
    };
    
    template <typename R, typename T1>
    core::Functor<R, NullType> bindFirst(core::Functor<R, TLIST_1(T1)> func, T1 p1){
        return core::Functor<R, NullType>(core::BindFirstFunctor<core::Functor<R, TLIST_1(T1)> >(func, p1));
    }
    template <typename R, typename T1, typename T2>
    core::Functor<R, TLIST_1(T2)> bindFirst(core::Functor<R, TLIST_2(T1, T2)> func, T1 p1){
        return core::Functor<R, TLIST_1(T2)>(core::BindFirstFunctor<core::Functor<R, TLIST_2(T1, T2)> >(func, p1));
    }    
    template <typename R, typename T1, typename T2, typename T3>
    core::Functor<R, TLIST_2(T2, T3)> bindFirst(core::Functor<R, TLIST_3(T1, T2, T3)> func, T1 p1){
        return core::Functor<R, TLIST_2(T2, T3)>(core::BindFirstFunctor<core::Functor<R, TLIST_3(T1, T2, T3)> >(func, p1));
    }
    template <typename R, typename T1, typename T2, typename T3, typename T4>
    core::Functor<R, TLIST_3(T2, T3, T4)> bindFirst(core::Functor<R, TLIST_4(T1, T2, T3, T4)> func, T1 p1){
        return core::Functor<R, TLIST_3(T2, T3, T4)>(core::BindFirstFunctor<core::Functor<R, TLIST_4(T1, T2, T3, T4)> >(func, p1));
    }
    template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5>
    core::Functor<R, TLIST_4(T2, T3, T4, T5)> bindFirst(core::Functor<R, TLIST_5(T1, T2, T3, T4, T5)> func, T1 p1){
        return core::Functor<R, TLIST_4(T2, T3, T4, T5)>(core::BindFirstFunctor<core::Functor<R, TLIST_5(T1, T2, T3, T4, T5)> >(func, p1));
    }
};};

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////