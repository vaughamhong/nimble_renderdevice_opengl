//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#include <nimble/resource/resourcecache.h>

//////////////////////////////////////////////////////////////////////////

namespace nimble{
namespace resource{

//////////////////////////////////////////////////////////////////////////
    
//! Adds a object to our cache
template <typename T>
void ResourceCache::add(T* pObject){
    this->add(dynamic_cast<resource::IResource*>(pObject));
}
//! Removes a object from our cache
template <typename T>
void ResourceCache::remove(T* pObject){
    resource::IResource *pResource = dynamic_cast<resource::IResource*>(pObject);
    if(pResource == 0){
        core::logger_warning("resource", "Failed to remove resource - invalid input resource param");
        return;
    }
    this->remove(pResource->getResourceId());
}
//! Gets a object from our cache
template <typename T>
T* ResourceCache::find(resource::ResourceId resourceId) const{
    // find our resource
    resource::IResource *pResource = this->find(resourceId);
    if(pResource == 0){
        return 0 ;
    }
    
    // try and cast to target type
    T *pObject = dynamic_cast<T*>(pResource);
    if(pObject == 0){
        core::logger_warning("resource", "Failed to find resource - cast to target type failed");
    }
    
    // return object
    return pObject;
}
    
//////////////////////////////////////////////////////////////////////////
    
};};

//////////////////////////////////////////////////////////////////////////