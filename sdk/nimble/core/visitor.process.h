//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_core_processvisitor_h__
#define __nimble_core_processvisitor_h__

//////////////////////////////////////////////////////////////////////////

#include <nimble/core/functor.h>
#include <nimble/core/typelist.h>

//////////////////////////////////////////////////////////////////////////

namespace nimble{
namespace core{
    
    //! group based visitor
    template <typename T>
    class ProcessVisitor{
    private:
        
        typedef core::Functor<void, TLIST_1(T*)> PreTraverseFunc;
        typedef core::Functor<void, TLIST_1(T*)> PostTraverseFunc;
        
        PreTraverseFunc m_preTraverse;
        PostTraverseFunc m_postTraverse;
                    
    public:
        
        //! Constructor
        ProcessVisitor(PreTraverseFunc preTraverse, PostTraverseFunc postTraverse)
        :m_preTraverse(preTraverse)
        ,m_postTraverse(postTraverse){
        }
        //! Destructor
        virtual ~ProcessVisitor(){
        }
        
    public:
        
        //! Executes on an object
        virtual void execute(T *pObject){
            m_preTraverse(pObject);
            
            // update each object's children
            for(typename List::iterator it = pObject->firstChild(); it != pObject->lastChild(); it++){
                this->execute(*it);
            }
            
            m_postTraverse(pObject);
        }
    };
};};

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////