//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_renderdevice_iindexbuffer_h__
#define __nimble_renderdevice_iindexbuffer_h__

//////////////////////////////////////////////////////////////////////////

#include <stdint.h>
#include <cstdlib>
#include <nimble/core/assert.h>

//////////////////////////////////////////////////////////////////////////

#define INDEXTYPE_TUPLESET \
INDEXTYPE_TUPLE(kIndexTypeUInt8,    1) \
INDEXTYPE_TUPLE(kIndexTypeUInt16,   2) \
INDEXTYPE_TUPLE(kIndexTypeUInt32,   4)

//////////////////////////////////////////////////////////////////////////

#pragma message("TODO: Consider removing PrimitiveType from index buffer - more than one mesh may share an IndexBuffer")

//////////////////////////////////////////////////////////////////////////

namespace nimble{
	namespace renderdevice{
        
        //! index type
        enum eIndexType{
            #define INDEXTYPE_TUPLE(ENUM, SIZE) ENUM,
                INDEXTYPE_TUPLESET
            #undef INDEXTYPE_TUPLE
            kMaxIndexTypes
        };
        
        //! the primitive format of the index array
        enum ePrimitiveType{
            kPrimitiveTriangleList,
            kPrimitiveTriangleFan,
            kPrimitiveTriangleStrip,
            kPrimitiveQuadList,
            kPrimitivePointList,
            kPrimitiveLineList,
            kMaxPrimitiveTypes
        };

        //! An abstract interface representing a hardware buffer
        class IIndexBuffer{
		public:

			//! Destructor
			virtual ~IIndexBuffer(){}

		public:

            //! returns the usage of this array
			//! \return the usage of this array
			virtual uint32_t getUsage() const = 0;
            //! returns the number of bytes for a single index
            //! \return the number of bytes for a single index
            virtual size_t getIndexSize() const = 0;
            //! returns the primitive type of this index array
			//! \return value of type enum ePrimitiveType
			virtual eIndexType getIndexType() const = 0;
			//! returns the primitive type of this index array
			//! \return value of type enum ePrimitiveType
			virtual ePrimitiveType getPrimitiveType() const = 0;
            //! returns the number of indices
            //! \return the number of indices
            virtual size_t getNumIndices() const = 0;
            //! returns the number of bytes in this array
			//! \return the number of bytes in this array
			virtual size_t getBufferSize() const = 0;
		};
        
        //! \return the index type size
        inline size_t getIndexTypeSize(eIndexType type){
            #define INDEXTYPE_TUPLE(ENUM, SIZE) if(type == ENUM){return SIZE;}
                INDEXTYPE_TUPLESET
            #undef INDEXTYPE_TUPLE
            return 0;
        }
        //! \return the index type
        template <typename T>
        inline eIndexType getIndexType(){
            core::assert_error(false, "Failed to retreive unsupported index type");
            return kIndexTypeUInt8;
        }
        //! \return the index type (specialization)
        template <>
        inline renderdevice::eIndexType getIndexType<uint32_t>(){
            return kIndexTypeUInt32;
        }
        //! \return the index type (specialization)
        template <>
        inline renderdevice::eIndexType getIndexType<uint16_t>(){
            return kIndexTypeUInt16;
        }
        //! \return the index type (specialization)
        template <>
        inline renderdevice::eIndexType getIndexType<uint8_t>(){
            return kIndexTypeUInt8;
        }
	};
};

//////////////////////////////////////////////////////////////////////////

#endif
