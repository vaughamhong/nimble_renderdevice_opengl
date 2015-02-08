//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_core_tlist__
#define __nimble_core_tlist__

//////////////////////////////////////////////////////////////////////////

#include <stdint.h>

//////////////////////////////////////////////////////////////////////////

namespace nimble{
namespace core{
    
    //! null type
    class NullType{};
    
    //! holds type information
    //! can be chained to hold N types
    template <typename H, typename T>
    class TypeList{
    public:
        typedef H Head;
        typedef T Tail;
    };
    
    //! helper defines
    #define TLIST_1(T1) nimble::core::TypeList<T1, nimble::core::NullType>
    #define TLIST_2(T1, T2) nimble::core::TypeList<T1, TLIST_1(T2)>
    #define TLIST_3(T1, T2, T3) nimble::core::TypeList<T1, TLIST_2(T2, T3)>
    #define TLIST_4(T1, T2, T3, T4) nimble::core::TypeList<T1, TLIST_3(T2, T3, T4)>
    #define TLIST_5(T1, T2, T3, T4, T5) nimble::core::TypeList<T1, TLIST_4(T2, T3, T4, T5)>
    
    //! calculates length
    template <class TList> struct TListLength;
    template <> struct TListLength<NullType>{
        enum { value = 0 };
    };
    template <class T, class U>
    struct TListLength<TypeList<T, U> >{
        enum { value = 1 + TListLength<U>::value };
    };
    
    //! calculates the i'th type
    template <class TList, uint32_t Index>
    struct TListTypeAt{
        typedef core::NullType Result;
    };
    template <class T, class U>
    struct TListTypeAt<TypeList<T, U>, 0>{
        typedef T Result;
    };
    template <class T, class U, uint32_t Index>
    struct TListTypeAt<TypeList<T, U>, Index>{
        typedef typename TListTypeAt<U, Index - 1>::Result Result;
    };
};};

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////