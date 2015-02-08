//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_renderdevice_vertexformat_h__
#define __nimble_renderdevice_vertexformat_h__

//////////////////////////////////////////////////////////////////////////

#include <stdint.h>
#include <cstdlib>
#include <string>

//////////////////////////////////////////////////////////////////////////

#define VERTEXFORMAT_ATTRIBUTENAME_TUPLESET \
VERTEXFORMAT_ATTRIBUTENAME_TUPLE(kSemanticPosition,     kPositionName,     "v_position") \
VERTEXFORMAT_ATTRIBUTENAME_TUPLE(kSemanticNormal,       kNormalName,       "v_normal") \
VERTEXFORMAT_ATTRIBUTENAME_TUPLE(kSemanticColor,        kColorName,        "v_color") \
VERTEXFORMAT_ATTRIBUTENAME_TUPLE(kSemanticTangent1,     kTangent1Name,     "v_tangent1") \
VERTEXFORMAT_ATTRIBUTENAME_TUPLE(kSemanticTexCoord1,    kTexCoord1Name,    "v_texCoord1") \
VERTEXFORMAT_ATTRIBUTENAME_TUPLE(kSemanticTexCoord2,    kTexCoord2Name,    "v_texCoord2") \
VERTEXFORMAT_ATTRIBUTENAME_TUPLE(kSemanticTexCoord3,    kTexCoord3Name,    "v_texCoord3")

//////////////////////////////////////////////////////////////////////////

namespace nimble{
	namespace renderdevice{
        
        //! vertex format
        class VertexFormat{
        public:
            
            //! define attribute binding names
            #define VERTEXFORMAT_ATTRIBUTENAME_TUPLE(ENUM, NAME, STRING) static const char* NAME;
                VERTEXFORMAT_ATTRIBUTENAME_TUPLESET
            #undef VERTEXFORMAT_ATTRIBUTENAME_TUPLE
            
            //! semantic enumerations for vertex attribute
			enum eAttributeSemantic{
                kSemanticNull = -1,
                
            #define VERTEXFORMAT_ATTRIBUTENAME_TUPLE(ENUM, NAME, STRING) ENUM,
                VERTEXFORMAT_ATTRIBUTENAME_TUPLESET
            #undef VERTEXFORMAT_ATTRIBUTENAME_TUPLE
                
                kMaxAttributeSemantics
			};
            
            //! type enumerations for vertex attribute
			enum eAttributeType{
                kTypeNull = -1,
                
				kTypeFloat1,
				kTypeFloat2,
				kTypeFloat3,
				kTypeFloat4,
                
                kTypeByte1,
				kTypeByte2,
				kTypeByte3,
				kTypeByte4,
                
                kTypeShort1,
				kTypeShort2,
				kTypeShort3,
				kTypeShort4,
				
                kMaxAttributeTypes,
				kFirstAttributeType = kTypeFloat1
			};
            
            //! defines information regarding a vertex attribute
			struct attribute_t{
				eAttributeSemantic	semantic;
                eAttributeType      type;
                std::string         name;
                bool                normalize;
                size_t              offset;
			};
            
        private:
            
            size_t              m_vertexStride;                         //!< the size of the offset from one vertex to the next
			size_t              m_numAttributes;						//<! the number of attributes in our vertex
            attribute_t         m_attributes[kMaxAttributeSemantics];   //<! information on each of the elements in our vertex
            
        public:
            
            //! Constructor
            VertexFormat();
            //! Constructor
            VertexFormat(VertexFormat const &vertexFormat);
            //! Destructor
            ~VertexFormat();
            
        public:

            //! returns the size of the offset from one vertex to the next
			//! \return returns the size of the offset from one vertex to the next
			size_t getVertexStride() const;
            //! returns the number of elements in each vertex
			//! \return returns the number of elements in each vertex
			size_t getNumAttributes() const;
            
			//! adds an attribute
			//! \param attributeIndex the index of the element we are interested in
			//! \param semantic the attribute semantic
			//! \param type the attribute type
			void addAttribute(eAttributeSemantic semantic, eAttributeType type, bool normalize = false);
			//! clears all our attributes
			void clearAttributes();
			
            //! returns the vertex element's semantic
			//! \param attributeIndex the index of the element we are interested in
			//! \return returns the vertex element's semantic
			eAttributeSemantic getAttributeSemantic(uint32_t attributeIndex) const;
            //! returns the vertex element's type
			//! \param attributeIndex the index of the element we are interested in
			//! \return returns the vertex element's type
			eAttributeType getAttributeType(uint32_t attributeIndex) const;
            //! returns the vertex element's name
			//! \param attributeIndex the index of the element we are interested in
			//! \return returns the vertex element's name
			const char* getAttributeName(uint32_t attributeIndex) const;
            //! returns the vertex element's normalize flag
            //! \param attributeIndex the index of the element we are interested in
            //! \return returns the vertex element's normalize flag
            bool getAttributeNormalize(uint32_t attributeIndex) const;
			//! returns the byte offset to a specific attribute
            //! \return the byte offset to a specific attribute
            size_t getAttributeByteOffset(uint32_t attributeIndex) const;
            
            //! returns the byte offset to a specific attribute
            //! \return the byte offset to a specific attribute
            size_t getAttributeByteOffsetBySemantic(eAttributeSemantic semantic) const;
            //! returns the vertex element's type
			//! \return returns the vertex element's type
			eAttributeType getAttributeTypeBySemantic(eAttributeSemantic semantic) const;
			//!	gets the size in bytes for the type specified
            //! \param type the type we are interested in
            //! \return the size in bytes for the type specified
            size_t getAttributeTypeByteSize(VertexFormat::eAttributeType type) const;
            
            //! returns if a vertex in this array has an element with a specific semantic
			//! \param semantic the semantic we are interested in
			//! \return returns true if a vertex in this array has an element with a specific semantic
			bool hasAttribute(eAttributeSemantic semantic) const;
            
            //! copy
            //! \param vertexFormat the vertex format to copy against
            //! \return returns the copied vertex format
            VertexFormat& copy(VertexFormat const &vertexFormat);
            //! assignment operator
            //! \param vertexFormat the vertex format to copy against
            //! \return returns the copied vertex format
            VertexFormat& operator=(VertexFormat const &vertexFormat);

            //! returns true if matching vertex format
            //! \param vertexFormat the vertex format to compare against
            //! \return returns true if matching vertex format
            bool equals(VertexFormat const &vertexFormat) const;
            //! returns true if matching vertex format
            //! \param vertexFormat the vertex format to compare against
            //! \return returns true if matching vertex format
            bool operator==(VertexFormat const &vertexFormat) const;
            //! returns true if matching vertex format
            //! \param vertexFormat the vertex format to compare against
            //! \return returns true if matching vertex format
            bool operator!=(VertexFormat const &vertexFormat) const;
            
            //! returns the vertex format sort index
            int64_t getSortIndex() const;
            
        private:
            
            //! Updates our vertex stride
            void updateVertexStrideAndOffsets();
        };
	};
};

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////