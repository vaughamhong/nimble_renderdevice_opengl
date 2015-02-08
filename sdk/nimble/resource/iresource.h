//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_resource_iresource_h__
#define __nimble_resource_iresource_h__

//////////////////////////////////////////////////////////////////////////

#include <stdint.h>

//////////////////////////////////////////////////////////////////////////

namespace nimble{
    namespace resource{
        class ResourceCache;
        
        //! ResourceId type
        typedef int32_t ResourceId;
        
        //! The null resourceId
        static const int32_t kNullResourceId = -1;
        
        //! An abstract resource
        class IResource{
        friend class resource::ResourceCache;
        public:
            
            //! Constructor
            IResource(){}
            //! Destructor
            virtual ~IResource(){}
            
        public:
            
            //! Returns our identifier
            //! \return the the resource cache this belongs to
            virtual resource::ResourceCache* getResourceCache() const = 0;
            //! Returns our identifier
            //! \return the resource Id
            virtual resource::ResourceId getResourceId() const = 0;
            
        private:
            
            //! Sets our resource cache
            //! \param pCache the cache this resource belongs to
            virtual void setResourceCache(resource::ResourceCache *pCache) = 0;
            //! Sets our resource identifier
            //! \param id the identifier to set
            virtual void setResourceId(resource::ResourceId id) = 0;
        };
    };
};

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////