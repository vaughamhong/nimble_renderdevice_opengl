//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_core_textfile_h__
#define __nimble_core_textfile_h__

//////////////////////////////////////////////////////////////////////////

#include <nimble/resource/resource.h>
#include <nimble/resource/resourceloader.h>
#include <nimble/core/buffer.h>

//////////////////////////////////////////////////////////////////////////

namespace nimble{
	namespace core{
        class IAllocator;
        
		//! Plain text file
		class TextFile{
        private:
            
            //! The buffer that will contain our text file data
            core::Buffer<> m_buffer;
            
        public:
            
            //! Constructor
            //! \param pAllocator the allocator to use for our data
            TextFile(core::IAllocator *pAllocator = 0);
            //! Constructor
            //! \param path the local file path to load from
            //! \param pAllocator the allocator to use for our data
            TextFile(const char *path, core::IAllocator *pAllocator = 0);
            //! Destructor
            virtual ~TextFile();
            
        public:
            
            //! Load from file
            //! \param path the local file path to load from
            void loadFromFile(const char *path);
            
        public:
            
            //! Returns a const pointer
            const char* getConstPointer() const;
            //! Returns buffer
            char* getPointer() const;
            //! Returns the file length
            size_t getSize() const;
		};
        
        //! Plain text file resource loader
        class TextFileLoader
        : public resource::IResourceLoader{
        public:
            
            //! Constructor
            TextFileLoader();
            //! Destructor
            virtual ~TextFileLoader();
            
            //! loads a resource
            //! \param path the path of the file we want to load
            virtual resource::IResource* load(const char* path);
        };
	};
};

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////