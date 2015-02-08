//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_resource_resourceloader_h__
#define __nimble_resource_resourceloader_h__

//////////////////////////////////////////////////////////////////////////

#include <nimble/resource/iresourceloader.h>
#include <map>
#include <string>

//////////////////////////////////////////////////////////////////////////

namespace nimble{
    namespace core{
        class SearchPaths;
    };
	namespace resource{
        class IResource;

        //! A resource loader that is able to map extensions
        //! (from paths) to loaders to execute.
		class ResourceLoader
        : public resource::IResourceLoader{
        private:
            
            // Maps extensions to loaders
            typedef std::map<std::string, resource::IResourceLoader*> ExtensionToLoaderIndex;

            // A list of paths to search against when loading resources
            core::SearchPaths       *m_pSearchPaths;
            // An index that maps extensions to loaders
            ExtensionToLoaderIndex  m_extensionToLoaderIndex;
            
        public:
            
            //! Constructor
            ResourceLoader(core::SearchPaths *pSearchPaths);
            //! Destructor
            virtual ~ResourceLoader();
            
        public:
            
            //! Adds a resource loader for an extension
            void addResourceLoaderForExtension(resource::IResourceLoader *pLoader, const char *extension);
            //! Removes a resource loader for an extension
            void removeResourceLoaderForExtension(const char *extension);
            //! Gets a resource loader for an extension
            resource::IResourceLoader* getResourceLoaderForExtension(const char *extension) const;
            
        public:
            
            //! Checks if we can load a file given the extension
            //! \param extension the extension of the file we want to check
            bool canLoadExtension(const char *extension) const;
            //! Checks if we can load this file given a path
            //! \param path the path of the file we want to check
            bool canLoadPath(const char *path) const;
            //! Checks if a file exists on a path
            //! \param path the path we want to check
            //! \return true if a file at the path exists
            bool existsPath(const char *path) const;
            
        public:
            
            //! loads a resource
            //! \param path the path of the file we want to load
            virtual resource::IResource* load(const char* path);
        };
	};
};

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////