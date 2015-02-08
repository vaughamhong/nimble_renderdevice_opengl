//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

//////////////////////////////////////////////////////////////////////////

namespace nimble{
    namespace core{
        
        //! Constructor
        template <typename T>
        Link<T>::Link()
        :m_pData(0)
        ,m_pNext(0)
        ,m_pPrev(0){
        }
        //! Constructor
        template <typename T>
        Link<T>::Link(Type *pData)
        :m_pData(pData)
        ,m_pNext(0)
        ,m_pPrev(0){
        }
        //! Destructor
        template <typename T>
        Link<T>::~Link(){
            unlink();
        }
            
        //! Insert next
        template <typename T>
        void Link<T>::insertNext(LinkType *pLink){
            if(m_pNext != 0){
                m_pNext->m_pPrev = pLink;
                pLink->m_pNext = m_pNext;
            }
            pLink->m_pPrev = this;
            this->m_pNext = pLink;
        }
        //! Insert prev
        template <typename T>
        void Link<T>::insertPrev(LinkType *pLink){
            if(m_pPrev != 0){
                m_pPrev->m_pNext = pLink;
                pLink->m_pPrev = m_pPrev;
            }
            pLink->m_pNext = this;
            this->m_pPrev = pLink;
        }
        //! Unlink
        template <typename T>
        void Link<T>::unlink(){
            if(m_pNext != 0){
                m_pNext->m_pPrev = m_pPrev;
            }
            if(m_pPrev != 0){
                m_pPrev->m_pNext = m_pNext;
            }
            m_pNext = 0;
            m_pPrev = 0;
        }
        
        //! Returns the next link
        template <typename T>
        typename core::Link<T>::LinkType* Link<T>::getNextLink() const{
            return m_pNext;
        }
        //! Returns the prev link
        template <typename T>
        typename core::Link<T>::LinkType* Link<T>::getPrevLink() const{
            return m_pPrev;
        }
        //! Sets the data
        template <typename T>
        void Link<T>::setData(typename core::Link<T>::Type *pData){
            m_pData = pData;
        }
        //! Returns the data
        template <typename T>
        typename core::Link<T>::Type* Link<T>::getData() const{
            return m_pData;
        }
        
        //////////////////////////////////////////////////////////////////////////
        
        //! Constructor
        template <typename T, typename Allocator>
        LinkList<T, Allocator>::LinkList()
        :m_pAllocator(&m_defaultAllocator)
        ,m_pBack(0)
        ,m_pFront(0)
        ,m_numItems(0){
        }
        //! Constructor
        template <typename T, typename Allocator>
        LinkList<T, Allocator>::LinkList(AllocatorType *pAllocator)
        :m_pAllocator(pAllocator ? pAllocator : &m_defaultAllocator)
        ,m_pBack(0)
        ,m_pFront(0)
        ,m_numItems(0){
        }
        //! Destructor
        template <typename T, typename Allocator>
        LinkList<T, Allocator>::~LinkList(){
            clear();
        }
        
        //! returns the number of items in this link list
        //! \return the number of items in this link list
        template <typename T, typename Allocator>
        typename core::LinkList<T, Allocator>::SizeType LinkList<T, Allocator>::getSize() const{
            return m_numItems;
        }
        
        //! Adds a link to the back of the list
        template <typename T, typename Allocator>
        void LinkList<T, Allocator>::pushBack(typename core::LinkList<T, Allocator>::Type *pData){
            typedef typename core::LinkList<T, Allocator>::LinkType LinkType;
            LinkType *pLink = (LinkType*)m_pAllocator->allocate(sizeof(LinkType));
            core::assert_error(pLink != 0);
            if(m_pBack != 0){
                m_pBack->insertNext(pLink);
            }else{
                m_pFront = pLink;
            }
            pLink->setData(pData);
            m_pBack = pLink;
            m_numItems += 1;
        }
        //! Adds a link to the front of the list
        template <typename T, typename Allocator>
        void LinkList<T, Allocator>::pushFront(typename core::LinkList<T, Allocator>::Type *pData){
            typedef typename core::LinkList<T, Allocator>::LinkType LinkType;
            LinkType *pLink = (LinkType*)m_pAllocator->allocate(sizeof(LinkType));
            core::assert_error(pLink != 0);
            if(m_pFront != 0){
                m_pFront->insertPrev(pLink);
            }else{
                m_pBack = pLink;
            }
            pLink->setData(pData);
            m_pFront = pLink;
            m_numItems += 1;
        }
        //! Removes a link from the back of the list
        template <typename T, typename Allocator>
        void LinkList<T, Allocator>::popBack(){
            typedef typename core::LinkList<T, Allocator>::LinkType LinkType;
            if(m_pBack != 0){
                LinkType *pBack = m_pBack;
                m_pBack = m_pBack->getPrevLink();
                pBack->unlink();
                m_pAllocator->deallocate(pBack);
            }
            if(m_pBack == 0){
                m_pFront = 0;
            }
            m_numItems -= 1;
        }
        //! Removes a link from the front of the list
        template <typename T, typename Allocator>
        void LinkList<T, Allocator>::popFront(){
            typedef typename core::LinkList<T, Allocator>::LinkType LinkType;
            if(m_pFront != 0){
                LinkType *pFront = m_pFront;
                m_pFront = m_pFront->getNextLink();
                pFront->unlink();
                m_pAllocator->deallocate(pFront);
            }
            if(m_pFront == 0){
                m_pBack = 0;
            }
            m_numItems -= 1;
        }
        //! Clear all links
        template <typename T, typename Allocator>
        void LinkList<T, Allocator>::clear(){
            while(m_pFront != 0){
                popFront();
            }
        }
        
        //! Returns the back link
        template <typename T, typename Allocator>
        typename core::LinkList<T, Allocator>::LinkType* LinkList<T, Allocator>::getBackLink() const{
            return m_pBack;
        }
        //! Returns the front link
        template <typename T, typename Allocator>
        typename core::LinkList<T, Allocator>::LinkType* LinkList<T, Allocator>::getFrontLink() const{
            return m_pFront;
        }        
    };
};

//////////////////////////////////////////////////////////////////////////