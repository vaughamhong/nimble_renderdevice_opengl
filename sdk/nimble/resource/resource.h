//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_resource_resource_h__
#define __nimble_resource_resource_h__

//////////////////////////////////////////////////////////////////////////

#include <nimble/core/object.h>
#include <nimble/resource/iresource.h>

//////////////////////////////////////////////////////////////////////////

namespace nimble{
namespace resource{
    
    //! A resource base type that tracks the cache it belongs
    //! to and the id that it has been assigned. This class is meant
    //! to be inherited.
    class Resource
    : public resource::IResource
    , public core::Object{
    private:
        
        //! The cache this resource belongs to
        resource::ResourceCache *m_pCache;
        
        //! The id of this resource
        resource::ResourceId    m_id;
        
    public:
        
        //! Constructor
        Resource();
        //! Destructor
        virtual ~Resource();
        
    public:
        
        //! Returns our identifier
        //! \return the the resource cache this belongs to
        virtual resource::ResourceCache* getResourceCache() const;
        //! Returns our identifier
        //! \return the resource Id
        virtual resource::ResourceId getResourceId() const;
        
    private:
        
        //! Sets our resource cache
        //! \param pCache the cache this resource belongs to
        virtual void setResourceCache(resource::ResourceCache *pCache);
        //! Sets our resource identifier
        //! \param id the identifier to set
        virtual void setResourceId(resource::ResourceId id);
    };
    
    //! A resource wrapper. This is useful for wrapping structs
    //! and classes that do not want to be poluted by the resource module.
    template <typename T>
    class ResourceWrapper
    : public resource::Resource
    , public T{
    public:
        
        //! Constructor
        ResourceWrapper();
        //! Destructor
        virtual ~ResourceWrapper();
    };
};};

//////////////////////////////////////////////////////////////////////////

#include "resource.inline.h"

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////