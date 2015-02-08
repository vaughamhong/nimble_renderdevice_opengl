//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

//////////////////////////////////////////////////////////////////////////

namespace nimble{
    namespace core{
  
        //////////////////////////////////////////////////////////////////////////
        
        //! Constructor
        template <typename T>
        Node<T>::Node()
        :m_pParent(0)
        ,m_pDelegate(0){
            clearChildren();
        }
        //! Constructor
        template <typename T>
        Node<T>::Node(Delegate *pDelegate)
        :m_pParent(0)
        ,m_pDelegate(pDelegate){
            clearChildren();
        }
        //! Destructor
        template <typename T>
        Node<T>::~Node(){
            clearChildren();
        }
        
        //////////////////////////////////////////////////////////////////////////
        
        //! Sets our delegate
        template <typename T>
        void Node<T>::setDelegate(Delegate *pDelegate){
            m_pDelegate = pDelegate;
        }
        
        //////////////////////////////////////////////////////////////////////////
        
        //! adds a child
        template <typename T>
        void Node<T>::addChild(T *pChild){
            core::ScopedLock lock(&m_lock);
            
            // do nothing if the child already exists
            if(this->childExists(pChild)){
                return;
            }
            
            // detach child if it already has a parent
            if(pChild->hasParent()){
                pChild->detachFromParent();
            }
            
            // set this node as the new parent
            pChild->setParent(dynamic_cast<T*>(this));
            m_children.push_back(pChild);
            if(m_pDelegate){
                m_pDelegate->childWasAdded(dynamic_cast<T*>(this), pChild);
            }
        }
        //! removes a child
        template <typename T>
        void Node<T>::removeChild(T* pChild){
            core::ScopedLock lock(&m_lock);
            
            // try and find the child within our list
            typename core::Node<T>::ListType::iterator it = std::find(m_children.begin(), m_children.end(), pChild);
            
            // exit if we did not find the child
            if(it == m_children.end()){
                return;
            }
            
            // detach child from this parent node, and remove child from this node's child list
            pChild->setParent(0);
            m_children.erase(it);
            if(m_pDelegate){
                m_pDelegate->childWasRemoved(dynamic_cast<T*>(this), pChild);
            }
        }
        //! clear all children
        template <typename T>
        void Node<T>::clearChildren(){
            core::ScopedLock lock(&m_lock);
            
            // iterate through each child and remove from this parent node
            for(typename core::Node<T>::ListType::iterator it = m_children.begin(); it != m_children.end(); it++){
                T *pChild = *it;
                pChild->setParent(0);
                if(m_pDelegate){
                    m_pDelegate->childWasRemoved(dynamic_cast<T*>(this), pChild);
                }
            }
            m_children.clear();
        }
        //! returns the number of children
        template <typename T>
        typename Node<T>::SizeType Node<T>::getNumChildren(){
            core::ScopedLock lock(&m_lock);
            return m_children.size();
        }
        //! checks if a child already exists
        template <typename T>
        bool Node<T>::childExists(T *pChild){
            core::ScopedLock lock(&m_lock);
            return std::find(m_children.begin(), m_children.end(), pChild) != m_children.end();
        }
        
        //////////////////////////////////////////////////////////////////////////
        
        //! returns all children
        template <typename T>
		void Node<T>::getChildren(typename core::Node<T>::ListType &children) const{
            core::ScopedLock lock(&m_lock);
            
            // note: We favor the getChildren API in favor of iterators because
            // iterators can be invalidedated in a multi-threaded environment. One
            // thread may invalidate another thread's iterators by inserting / deleting (into the node).
            
            // Having said that, it is still possible that we return a list of children while
            // another thread deletes children. This problem relates to lifetime management,
            // and should not be the concern of the node class.
            
            children = m_children;
        }
        
        //////////////////////////////////////////////////////////////////////////
        
        //! returns the parent
        template <typename T>
        T* Node<T>::getParent(){
            return m_pParent;
        }
        //! returns the parent
        template <typename T>
        const T* Node<T>::getParent() const{
            return m_pParent;
        }
        //! returns true if this child has a prent
        template <typename T>
        bool Node<T>::hasParent() const{
            return m_pParent != 0;
        }
        //! removes this node from its parent
        template <typename T>
        void Node<T>::detachFromParent(){
            if(hasParent()){
                m_pParent->removeChild(dynamic_cast<T*>(this));
            }
        }
        //! sets our parent
        template <typename T>
        void Node<T>::setParent(T *pParentNode){
            if(m_pDelegate && m_pParent && (pParentNode != m_pParent)){
                m_pDelegate->nodeWasDetached(dynamic_cast<T*>(this), m_pParent);
            }
            m_pParent = pParentNode;
            if(m_pDelegate){
                m_pDelegate->nodeWasAttached(dynamic_cast<T*>(this), pParentNode);
            }
        }
    };
};

//////////////////////////////////////////////////////////////////////////

