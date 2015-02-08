//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_core_stlallocator_h__
#define __nimble_core_stlallocator_h__

//////////////////////////////////////////////////////////////////////////

namespace nimble{
namespace core{
        
    #pragma message("TODO - implement STL allocator")
//    //! Overloaded STL allocator
//    template <class T>
//    class StlAllocator{
//    public:
//        
//        typedef T         value_type;
//        typedef size_t    size_type;
//        typedef ptrdiff_t difference_type;
//        typedef T*        pointer;
//        typedef const T*  const_pointer;
//        typedef T&        reference;
//        typedef const T&  const_reference;
//        template <class U> struct rebind{typedef StlAllocator<U> other;};
//        
//    public:
//        
//        //! Constructor
//        StlAllocator() throw(){
//        }
//        //! copy constructor
//        StlAllocator(const StlAllocator&) throw(){
//        }
//        //! copy constructor
//        template <class U> StlAllocator(const StlAllocator<U>&) throw(){
//        }
//        //! Destructor
//        ~StlAllocator() throw(){
//        }
//        
//    public:
//        
//        //! returns a pointer given a reference
//        pointer address(reference x) const{
//            return &x;
//        }
//        //! returns a const pointer given a reference
//        const_pointer address(const_reference x) const{
//            return &x;
//        }
//        //! returns the max size of this allocator
//        size_type max_size() const throw(){
//            return 10000;
//        }
//        
//    public:
//        
//        //! allocates a piece of memory
//        pointer allocate(size_type n){
//            size_type totalAllocationSize = n * sizeof(value_type);
//            
//            
//            //				pointer p = (pointer)core::getInstance()->allocate(totalAllocationSize);
//            //				memset((void*)p, 0, totalAllocationSize);
//            //				return p;
//            pointer p = (pointer)malloc(totalAllocationSize);
//            memset((void*)p, 0, totalAllocationSize);
//            return p;
//        }
//        //! deallocates the piece of memory
//        void deallocate(pointer p, size_type n){
//            //                return core::getInstance()->deallocate(p);
//            free((void*)p);
//        }
//        
//        //! Initializes the element p with value val
//        void construct(pointer p, const T& val){
//            new (p) T(val);
//        }
//        //! Destroys the element p without deallocating
//        void destroy(pointer p){
//            
//        }
//    };
//    
//    //! Base case void allocator
//    template <> class StlAllocator<void>{
//    public:
//        typedef void			value_type;
//        typedef void*			pointer;
//        typedef const void*		const_pointer;
//        template <class U> struct rebind{typedef StlAllocator<U> other;};
//    };
//    
//    //! returns true if Allocator<T1> can be deallocated by Allocator<A2>
//    template <class T1, class T2>
//    bool operator==(const StlAllocator<T1>&, const StlAllocator<T2>&) throw(){return false;}
//    //! returns true if Allocator<T1> can not be deallocated by Allocator<A2>
//    template <class T1, class T2>
//    bool operator!=(const StlAllocator<T1>&, const StlAllocator<T2>&) throw(){return false;}
};};

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////
