//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_core_object_h__
#define __nimble_core_object_h__

//////////////////////////////////////////////////////////////////////////

#include <nimble/core/typemetadata.h>

//////////////////////////////////////////////////////////////////////////

namespace nimble{
namespace core{
    class TypeMetaData;
    class ObjectFactory;
    
    //! Our base object for which all other objects inherit,
    //! built on top of our TypeMetaData system
    class Object{
    friend class nimble::core::ObjectFactory;
    private:
        
        core::TypeMetaData *m_pType;
        
    public:
        
        //! Constructor
        Object();
        //! Constructor
        Object(core::TypeMetaData *pType);
        //! Destructor
        virtual ~Object();
        
        //! Returns the type for this object
        //! \return the type for this object
        core::TypeMetaData* getTypeMetaData() const;
        //! Sets this object's type
        //! \param[in] pType the type to set
        void setTypeMetaData(core::TypeMetaData *pType);
    };
};};

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////