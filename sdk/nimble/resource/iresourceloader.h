//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_resource_iresourceloader_h__
#define __nimble_resource_iresourceloader_h__

//////////////////////////////////////////////////////////////////////////

namespace nimble{
    namespace resource{
        class IResource;
        
        //! A resource loader is a wrapper that allows users to load a
        //! resource from file without knowing its type. This is useful
        //! for loading resources given a path (eg. through an
        //! extension mapping).
        //! Each concrete resource loader should be constructor injected
        //! with whatever is needed to create a resource of the specific
        //! type. This may include one or more allocators.
        //! Resource loader(s) should be re-entrance. A load may be called
        //! from multiple threads (thread pool).
        class IResourceLoader{
        public:
            
            //! Constructor
            IResourceLoader(){}
            //! Destructor
            virtual ~IResourceLoader(){}
            
        public:
            
            //! loads a resource
            //! \param path the path of the file we want to load
            virtual resource::IResource* load(const char* path) = 0;
        };
    };
};

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////