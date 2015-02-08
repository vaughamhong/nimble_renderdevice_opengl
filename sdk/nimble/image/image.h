//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_image_image_h__
#define __nimble_image_image_h__

//////////////////////////////////////////////////////////////////////////

#include <nimble/resource/resource.h>
#include <nimble/resource/resourceloader.h>
#include <nimble/core/Lockable.h>
#include <nimble/core/buffer.h>

//////////////////////////////////////////////////////////////////////////

#define IMAGE_TUPLESET \
IMAGE_TUPLE(kFormatR8G8B8,         sizeof(char) * 3) \
IMAGE_TUPLE(kFormatR16G16B16,      sizeof(short) * 3) \
IMAGE_TUPLE(kFormatRGBF,           sizeof(float) * 3) \
\
IMAGE_TUPLE(kFormatR8G8B8A8,       sizeof(char) * 4) \
IMAGE_TUPLE(kFormatR16G16B16A16,   sizeof(short) * 4) \
IMAGE_TUPLE(kFormatRGBAF,          sizeof(float) * 4) \
\
IMAGE_TUPLE(kFormatB8G8R8,         sizeof(char) * 3) \
IMAGE_TUPLE(kFormatB8G8R8A8,       sizeof(char) * 4) \
\
IMAGE_TUPLE(kFormatDepth16,        sizeof(short) * 2) \
IMAGE_TUPLE(kFormatDepth24,        sizeof(short) * 3) \
IMAGE_TUPLE(kFormatDepth32,        sizeof(short) * 4)

//////////////////////////////////////////////////////////////////////////

namespace nimble{
	namespace image{

		//! image definition
		class Image
        : public core::Lockable{
        public:
            
            #define IMAGE_TUPLE(ENUM, PIXEL_SIZE) ENUM,
                enum eFormat{
                    IMAGE_TUPLESET
                    
                    kMaxFormats,
                    kUnknownFormat = -1,
                };
            #undef IMAGE_TUPLE

        private:
            
            uint32_t        m_width;
            uint32_t        m_height;
            eFormat         m_format;
            
            core::Buffer<>  m_buffer;
            
		public:

            //! Constructor
            Image();
            //! Cosntructor
            Image(uint32_t width, uint32_t height, image::Image::eFormat format);
            //! Construtor
            Image(Image const &image);
            //! Constructor
            Image(const char *path);
            //! Destructor
			virtual ~Image();
            
        public:
            
            //! Load from file
            void loadFromFile(const char *path);
            
		public:

            //! returns true if valid
            bool isValid();
            
            //! gets the format of this image
			image::Image::eFormat getFormat() const;
			//! gets the width of the image
			uint32_t getWidth() const;
			//! gets the height of the image
			uint32_t getHeight() const;
            
            //!	gets the size in bytes for a single pixel
			uint32_t getBytesPerPixel();
            //! gets the size of our image in bytes
            uint32_t getSize();
            
        public:
            
            //! Copies an image
            void copy(Image const &image);
            //! Copies an image
            void operator=(Image const &image);
            
        protected:
            
            //! attempts to map a buffer
            virtual char* mapBuffer(core::eLockType lockType);
            //! attempts to map a buffer
            virtual char* mapBufferRange(core::eLockType lockType, uint32_t offset, uint32_t size);
            //! attempts to unmap a buffer
            virtual void unmapBuffer();
		};
        
        //! Image file resource loader
        class ImageLoader
        : public resource::IResourceLoader{
        public:
            
            //! Constructor
            ImageLoader();
            //! Destructor
            virtual ~ImageLoader();
            
            //! loads a resource
            //! \param path the path of the file we want to load
            virtual resource::IResource* load(const char* path);
        };
	};
};

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////