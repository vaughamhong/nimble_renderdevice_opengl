//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_core_zipfile_h__
#define __nimble_core_zipfile_h__
#if !defined(WIN32)

//////////////////////////////////////////////////////////////////////////

#include <nimble/resource/resource.h>
#include <nimble/resource/resourceloader.h>
#include <nimble/core/buffer.h>
//#include <unzip.h>
//#include <zip.h>

//////////////////////////////////////////////////////////////////////////

namespace nimble{
	namespace core{
        
//		//! Zip file
//		class ZipFile{
//        private:
//            
//            static const int    kMaxFilenameSize = 512;
//            static const char   kDirDelimeter = '/';
//
//            unzFile             m_zipFile;
//            unz_global_info     m_globalInfo;
//                        
//        public:
//            
//            //! Constructor
//            ZipFile();
//            //! Constructor
//            ZipFile(const char *path);
//            //! Destructor
//            virtual ~ZipFile();
//            
//        public:
//            
//            //! Load from file
//            void loadFromFile(const char *path);
//            //! Save to file
//            void saveToFile(const char *path);
//            
//        public:
//            
//            //! Check if a path exists
//            bool existsFileInArchive(const char *path);
//            
//        private:
//            
//            //! 
//		};
//        
//        //! Plain zip file resource loader
//        class ZextFileLoader
//        : public resource::IResourceLoader{
//        public:
//            
//            //! Constructor
//            ZextFileLoader();
//            //! Destructor
//            virtual ~ZextFileLoader();
//            
//            //! loads a resource
//            //! \param path the path of the file we want to load
//            virtual resource::IResource* load(const char* path);
//        };
	};
};

//////////////////////////////////////////////////////////////////////////

#endif
#endif

//////////////////////////////////////////////////////////////////////////