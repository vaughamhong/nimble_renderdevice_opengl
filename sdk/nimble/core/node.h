//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_core_node__
#define __nimble_core_node__

//////////////////////////////////////////////////////////////////////////

#include <stdint.h>
#include <algorithm>
#include <vector>
#include <nimble/core/thread.mutex.h>

//////////////////////////////////////////////////////////////////////////

namespace nimble{
namespace core{

    //! Manages a parent child tree (or graph) of relationships.
    template <typename T>
    class Node{
    public:
        
        typedef std::vector<T*> ListType;
        typedef size_t          SizeType;

    public:
        
        class Delegate{
        public:
            //! Called when a child was added
            virtual void childWasAdded(T *pNode, T *pChild){};
            //! Called when added to a parent
            virtual void nodeWasAttached(T *pNode, T *pParent){};
            //! Called when a child was removed
            virtual void childWasRemoved(T *pNode, T *pChild){};
            //! Called when removed from parent
            virtual void nodeWasDetached(T *pNode, T *pParent){};
        };
        
    private:
        
        T           *m_pParent;
        ListType    m_children;
        Delegate    *m_pDelegate;
        
        mutable core::Mutex m_lock;
        
    public:
        
        //! Constructor
        Node();
        //! Constructor
        Node(Delegate *pDelegate);
        //! Destructor
        virtual ~Node();
        
    public:
        
        //! Sets our delegate
        virtual void setDelegate(Delegate *pDelegate);
        
    public:
        
        //! adds a child
        virtual void addChild(T *pChild);
        //! removes a child
        virtual void removeChild(T *pChild);
        //! clear all children
        virtual void clearChildren();
        //! returns the number of children
        virtual SizeType getNumChildren();
        //! checks if a child already exists
        virtual bool childExists(T *pChild);

        //! returns all children
        virtual void getChildren(typename core::Node<T>::ListType &children) const;
                
    public:

        //! returns the parent
        virtual T* getParent();
        //! returns the parent
        virtual const T* getParent() const;
        //! returns true if this child has a prent
        virtual bool hasParent() const;
        //! removes this node from its parent
        virtual void detachFromParent();
        
    private:
        
        //! sets our parent
        virtual void setParent(T *pParentNode);
    };
};};

//////////////////////////////////////////////////////////////////////////

#include "node.inline.h"

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////