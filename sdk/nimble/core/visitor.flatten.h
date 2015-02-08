//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_core_flattenvisitor_h__
#define __nimble_core_flattenvisitor_h__

//////////////////////////////////////////////////////////////////////////

#include <nimble/core/functor.h>
#include <nimble/core/typelist.h>
#include <vector>

//////////////////////////////////////////////////////////////////////////

namespace nimble{
namespace core{
    
    //! flattens a hierarchy of objects
    template <typename T>
    class FlattenVisitor{
    public:
        
        typedef std::vector<T*> List;
        
        enum eType{
            kBreadthFirst,
            kDepthFirst,
            kDefaultType = kBreadthFirst,
        };
        
    private:
        
        List    &m_list;
        eType   m_type;
        
    public:
        
        //! Constructor
        FlattenVisitor(List &list, eType type = kDefaultType)
        :m_list(list)
        ,m_type(type){
        }
        //! Destructor
        virtual ~FlattenVisitor(){
        }
        
    public:
        
        //! Executes on an object
        virtual void execute(T *pObject){
            if(m_type == kBreadthFirst){
                m_list.push_back(pObject);
            }
            
            // update each object's children
            for(typename List::iterator it = pObject->firstChild(); it != pObject->lastChild(); it++){
                this->execute(*it);
            }
            
            if(m_type == kDepthFirst){
                m_list.push_back(pObject);
            }
        }
    };
};};

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////