//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_core_linklist_h__
#define __nimble_core_linklist_h__

//////////////////////////////////////////////////////////////////////////

#include <nimble/core/memory.h>

//////////////////////////////////////////////////////////////////////////

namespace nimble{
namespace core{
    
    //! A link within a link list
    template <typename T>
    class Link{
    public:
        
        typedef T               Type;
        typedef core::Link<T>   LinkType;
        
    private:
        
        //! The data this link is holding on to
        Type        *m_pData;
        
        //! The next link
        LinkType    *m_pNext;
        //! The previous link
        LinkType    *m_pPrev;
        
    public:
        
        //! Constructor
        Link();
        //! Constructor
        Link(Type *pData);
        //! Destructor
        ~Link();
        
    public:
        
        //! Insert next
        void insertNext(LinkType *pLink);
        //! Insert prev
        void insertPrev(LinkType *pLink);
        //! Unlink
        void unlink();
        
    public:
        
        //! Returns the next link
        LinkType* getNextLink() const;
        //! Returns the prev link
        LinkType* getPrevLink() const;
        
        //! Sets the data
        void setData(Type *pData);
        //! Returns the data
        Type* getData() const;
    };
    
    //! A list of links
    template <typename T, typename Allocator = core::Allocator>
    class LinkList{
    public:
        
        typedef typename core::Link<T>::Type        Type;
        typedef typename core::Link<T>::LinkType    LinkType;
        typedef size_t                              SizeType;
        typedef Allocator                           AllocatorType;

    private:
        
        // STL containers makes a copy of the input allocator for later use. This is as a result
        // of STL container policy assuming allocators are state-less. This means
        // allocators of the same type are allowed to allocate / deallocate even across
        // different allocator instances. Allocators of the same type are are essentially singletons.
        
        // Our implementation allows stateful allocators. This means allocators (of the same type)
        // can be constructed / configured separately (eg. with different heaps). This adds
        // flexibility but requires more specific attention appiled to application level allocator design.
        
        // The default allocator is used if no external allocator
        // is specified on construction. Although this takes up a bit
        // more space, it is much easier to maintain (cleans up after itself
        // on destruction, no additional heap allocations, no additional management).
        AllocatorType m_defaultAllocator;
        AllocatorType *m_pAllocator;

        // The front link
        LinkType *m_pFront;
        // The back link
        LinkType *m_pBack;
        
        // The number of items in this list
        SizeType m_numItems;
        
    public:
        
        //! Constructor
        LinkList();
        //! Constructor
        LinkList(AllocatorType *pAllocator = 0);
        //! Destructor
        ~LinkList();
        
    public:
        
        //! returns the number of items in this link list
        //! \return the number of items in this link list
        virtual SizeType getSize() const;

    public:
        
        //! Adds a link to the back of the list
        void pushBack(Type *pData);
        //! Adds a link to the front of the list
        void pushFront(Type *pData);

        //! Removes a link from the back of the list
        void popBack();
        //! Removes a link from the front of the list
        void popFront();
        
        //! Clear all links
        void clear();

    public:
        
        //! Returns the back link
        LinkType* getBackLink() const;
        //! Returns the front link
        LinkType* getFrontLink() const;
    };
};};

//////////////////////////////////////////////////////////////////////////

#include "linklist.inline.h"

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////