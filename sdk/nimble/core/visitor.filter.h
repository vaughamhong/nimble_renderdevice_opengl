//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_core_filtervisitor_h__
#define __nimble_core_filtervisitor_h__

//////////////////////////////////////////////////////////////////////////

#include <nimble/core/functor.h>
#include <nimble/core/typelist.h>
#include <vector>

//////////////////////////////////////////////////////////////////////////

namespace nimble{
namespace core{
    
    //! filter based visitor
    template <typename T>
    class FilterVisitor{
    public:
        
        typedef std::vector<T*> List;
        typedef core::Functor<bool, TLIST_1(T*)> Func;
        
    private:
    
        Func    m_filter;
        List    &m_filteredList;
        
    public:
        
        //! Constructor
        FilterVisitor(Func filter, List &filteredList)
        :m_filter(filter)
        ,m_filteredList(filteredList){
        }
        //! Destructor
        virtual ~FilterVisitor(){
        }
        
    public:
        
        //! Executes on an object
        virtual void execute(T *pObject){
            // call our filter
            if(true == m_filter(pObject)){
                m_filteredList.push_back(pObject);
            }
            // update each object's children
            for(typename List::iterator it = pObject->firstChild(); it != pObject->lastChild(); it++){
                this->execute(*it);
            }
        }
    };
};};

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////