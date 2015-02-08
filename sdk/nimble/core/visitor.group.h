//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_core_groupvisitor_h__
#define __nimble_core_groupvisitor_h__

//////////////////////////////////////////////////////////////////////////

#include <nimble/core/functor.h>
#include <nimble/core/typelist.h>
#include <vector>
#include <map>

//////////////////////////////////////////////////////////////////////////

namespace nimble{
namespace core{
    
    //! group based visitor
    template <typename T, typename K = int32_t>
    class GroupVisitor{
    public:
        
        typedef std::vector<T*>     List;
        typedef std::map<K, List>   Groups;
        
    private:
        
        typedef core::Functor<K, TLIST_1(T*)> Func;
        
        Func    m_grouper;
        Groups  &m_groups;
        
    public:
        
        //! Constructor
        GroupVisitor(Func grouper, Groups &groups)
        :m_grouper(grouper)
        ,m_groups(groups){
        }
        //! Destructor
        virtual ~GroupVisitor(){
        }
        
    public:
        
        //! Executes on an object
        virtual void execute(T *pObject){
            // call our group function
            K groupKey = m_grouper(pObject);
            m_groups[groupKey].push_back(pObject);
            
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