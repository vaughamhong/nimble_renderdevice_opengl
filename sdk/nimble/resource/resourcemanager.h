//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_resource_resourcemanager_h__
#define __nimble_resource_resourcemanager_h__

//////////////////////////////////////////////////////////////////////////

#include <nimble/core/searchpaths.h>
#include <nimble/core/thread.mutex.h>
#include <nimble/core/future.h>
#include <nimble/resource/resourcecache.h>
#include <unordered_map>

//////////////////////////////////////////////////////////////////////////

namespace nimble{
    namespace core{
        class SearchPaths;
        class ThreadPool;
    };
	namespace resource{
        class ResourceCache;
        class ResourceLoader;
        class IResource;
        
        //! A resource future
        typedef core::Promise<resource::IResource*> ResourcePromise;
        typedef core::Future<resource::IResource*> ResourceFuture;
        
        //! A resource manager loads and manages path to resource pairs.
        class ResourceManager{
        private:

            //! Reference count info related to a resource
            struct resourceInfo_t{
                std::string path;
                resource::IResource *pResource;
                int32_t referenceCount;
            };
            typedef std::unordered_map<resource::IResource*, int64_t> ResourceToPathHashIndex;
            typedef std::unordered_map<int64_t, resourceInfo_t> PathHashToResourceInfoIndex;
            typedef std::vector<resource::IResource*> CleanupList;
            
            //! Mutax for updating reference info
            mutable core::Mutex m_lock;
            
            //! Maps resource to path hash
            ResourceToPathHashIndex m_resourceToPathHashIndex;
            //! Maps path hash to resource info
            PathHashToResourceInfoIndex m_pathHashToResourceInfoIndex;
            
            //! The resource loader for this manager
            resource::ResourceLoader *m_pResourceLoader;
            //! The resource cache for this manager
            resource::ResourceCache m_cache;
            
            //! List of resources to deallocate
            mutable core::Mutex m_cleanupLock;
            CleanupList m_cleanupList;
            
        public:
            
            //! Constructor
            //! \param pResourceLoader the resource loader this manager will use to load with
            ResourceManager(resource::ResourceLoader *pResourceLoader);
            //! Destructor
			virtual ~ResourceManager();
            
        public:
            
            //! Checks if we can load this file given a path
            //! \param path the path we want to check
            //! \return true if we can load from path
            bool canLoadPath(const char *path) const;
            //! Checks if a file exists on a path
            //! \param path the path we want to check
            //! \return true if a file at the path exists
            bool existsPath(const char *path) const;
            
            //! Loads a resource given a file path
            //! \param path the path we want to load from
            //! \return a resource given a file path
            resource::IResource* load(const char *path);
            //! Async load resource given a file path
            //! \param path the path we want to load from
            //! \pThreadPool the thread pool to dispatch async call
            //! \return a resource future
            resource::ResourceFuture asyncLoadResource(const char *path, core::ThreadPool *pThreadPool = 0);
            
            //! Releases a resource
            //! \param pResource the resource we want to release
            void releaseResource(resource::IResource *pResource);
            //! Releases a resource
            //! \param path the path of the resource we want to release
            void releaseResourceByPath(const char *path);
            
            //! Checks if there exists a pre-loaded resource at a path
            //! \param path the path of the resource we want to check
            bool existsResourceWithPath(const char *path);
            
            //! Cleanup resources
            void cleanupResources();
            
        private:
            
            //! Returns the resource info by resource
            resourceInfo_t* findResourceInfoByResource(resource::IResource *pResource);
            //! Returns the resource info by path
            resourceInfo_t* findResourceInfoByPath(const char *path);
		};
	};
};

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////