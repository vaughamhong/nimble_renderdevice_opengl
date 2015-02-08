//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_resource_resourcecache_h__
#define __nimble_resource_resourcecache_h__

//////////////////////////////////////////////////////////////////////////

#include <map>
#include <vector>
#include <nimble/message/message.h>
#include <nimble/core/thread.mutex.h>
#include <nimble/resource/iresource.h>

//////////////////////////////////////////////////////////////////////////

namespace nimble{
namespace resource{
    
    //////////////////////////////////////////////////////////////////////////
    
    //! when a resource has been added
    class ResourceWasAdded
    : public message::MessageWrapper<ResourceWasAdded>{
    public:
        resource::ResourceId m_id;
    public:
        //! Constructor
        ResourceWasAdded():m_id(0){}
        //! Constructor
        ResourceWasAdded(resource::ResourceId id):m_id(id){}
    };
    //! when a resource has changed
    class OnResourceChanged
    : public message::MessageWrapper<OnResourceChanged>{
    public:
        resource::ResourceId m_id;
    public:
        //! Constructor
        OnResourceChanged():m_id(0){}
        //! Constructor
        OnResourceChanged(resource::ResourceId id):m_id(id){}
    };
    //! when a resource has been removed
    class ResourceWasRemoved
    : public message::MessageWrapper<ResourceWasRemoved>{
    public:
        resource::ResourceId m_id;
    public:
        //! Constructor
        ResourceWasRemoved():m_id(0){}
        //! Constructor
        ResourceWasRemoved(resource::ResourceId id):m_id(id){}
    };
    
    //////////////////////////////////////////////////////////////////////////

    typedef std::vector<resource::IResource*> ResourceList;

    //! Resource bookkeeping
    //! Adding a resource to the cache will assign it an id
    //! Removing a resource will nullify its id
    //! The ResourceCache is not responsible for creating / destroying of resources
    class ResourceCache{
    private:

        typedef std::map<resource::ResourceId, resource::IResource*> ResourceIdToResourceIndex;

        ResourceList                m_list;
        ResourceIdToResourceIndex   m_idToResourceIndex;
        resource::ResourceId        m_nextId;
        
        mutable nimble::core::Mutex m_lock;
        
    public:
        
        //! Constructor
        ResourceCache();
        //! Destructor
        ~ResourceCache();
        
    public:
        
        //! Adds a resource to our cache
        virtual void add(resource::IResource *pResource);
        //! Removes a resource from our cache
        virtual void remove(resource::ResourceId resourceId);
        //! Gets a resource from our cache
        virtual resource::IResource* find(resource::ResourceId resourceId) const;
        //! Clears all resources
        virtual void clear();
        
    public:
        
        //! Adds a object to our cache
        template <typename T>
        void add(T* pObject);
        //! Removes a object from our cache
        template <typename T>
        void remove(T* pObject);
        //! Gets a object from our cache
        template <typename T>
        T* find(resource::ResourceId resourceId) const;
        
    public:
        
        //! The begin resource iterator
        virtual ResourceList::iterator begin();
        //! The begin resource iterator
        virtual ResourceList::const_iterator begin() const;
        //! The end resource iterator
        virtual ResourceList::iterator end();
        //! The end resource iterator
        virtual ResourceList::const_iterator end() const;
    };
};};

//////////////////////////////////////////////////////////////////////////

#include "resourcecache.inline.h"

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////