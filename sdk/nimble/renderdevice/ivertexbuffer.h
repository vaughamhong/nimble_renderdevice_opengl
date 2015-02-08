//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_renderdevice_ivertexbuffer_h__
#define __nimble_renderdevice_ivertexbuffer_h__

//////////////////////////////////////////////////////////////////////////

#include <stdint.h>
#include <nimble/renderdevice/vertexformat.h>

//////////////////////////////////////////////////////////////////////////

namespace nimble{
	namespace renderdevice{
        
        //! An abstract interface representing a hardware buffer
        class IVertexBuffer{
        public:
            
            //! Destructor
			virtual ~IVertexBuffer(){}
            
        public:
            
            //! returns the usage of this array
			//! \return the usage of this array
			virtual uint32_t getUsage() const = 0;
            //! returns the vertex format
            virtual const renderdevice::VertexFormat& getVertexFormat() const = 0;
            //! returns the vertex stride
            virtual size_t getVertexStride() const = 0;
            //! returns the number of vertices
            //! \return the number of vertices
            virtual size_t getNumVertices() const = 0;
            //! returns the number of bytes in this array
			//! \return the number of bytes in this array
			virtual size_t getBufferSize() const = 0;
        };
        //! \return the vertex format
        template <typename T>
        inline renderdevice::VertexFormat getVertexFormat(){
            return T::getFormat();
        }
    };
};

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////