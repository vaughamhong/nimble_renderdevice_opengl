//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_core_typemetadata_h__
#define __nimble_core_typemetadata_h__

//////////////////////////////////////////////////////////////////////////

#include <string>
#include <map>
#include <vector>
#include <nimble/core/assert.h>
#include <nimble/core/logger.h>
#include <nimble/core/hash.h>
#include <stdint.h>
#include <typeinfo>
#include <nimble/core/stringutil.h>

//////////////////////////////////////////////////////////////////////////

namespace nimble{
namespace core{
    class FieldMetaData;
    class EnumMetaData;
    class TypeMetaData;
    class TypeDatabase;
    
    //////////////////////////////////////////////////////////////////////////
    
    typedef int64_t TypeId;
    
    //////////////////////////////////////////////////////////////////////////
    
    //! Returns the typeId given a type
    template <typename T>
    TypeId getTypeId();
    
    //////////////////////////////////////////////////////////////////////////
    
    //! Given a pointer and a type, we can use the Field metadata to
    //! offset to a specific member variable
    class FieldMetaData{
    friend class nimble::core::TypeMetaData;
    public:
        
        enum{
            kFlagPointer    = (1 << 0),
            kFlagReadOnly   = (1 << 1),
        };
        
    private:
        
        std::string m_name;
        size_t m_offset;
        size_t m_size;
        core::TypeId m_typeId;
        core::TypeMetaData *m_pType;
        int32_t m_flags;
        
    public:
        
        //! Copy constructor
        //! \param[in] field to copy
        FieldMetaData(FieldMetaData const &metaData);
        //! Constructor
        //! \param[in] name the name of the field
        //! \param[in] field a pointer to the object member
        //! \param[in] flags the flags associated with this field
        template <typename OBJ_TYPE, typename FIELD_TYPE>
        FieldMetaData(const char *name, FIELD_TYPE OBJ_TYPE::*member, int32_t flags = 0);
        //! Destructor
        ~FieldMetaData();
        
        //! Returns the name of the field
        //! \return the name of the field
        const char* getName() const;
        //! Returns the memory offset from the base object
        //! \return the memory offset from the base object
        size_t getOffset() const;
        //! Returns the size of this field
        //! \return the size of this field
        size_t getSize() const;
        //! Returns the type for this field
        //! \return the type for this field
        core::TypeMetaData* getType() const;
        
        //! Returns true if this field is a pointer
        //! \return true if this field is a pointer
        bool isPointer() const;
        //! Returns true if this field is read only
        //! \return true if this field is read only
        bool isReadOnly() const;
        
    private:
        
        //! Returns the typeId of this field
        //! \return the typeId of this field
        core::TypeId typeId() const;
        
        //! Sets the typeId of this field
        //! \param[in] pType the type to set
        void setType(core::TypeMetaData *pType);
    };
    
    //////////////////////////////////////////////////////////////////////////
    
    //! Given a type, we can use Enumeration metadata to determine
    //! enumeration values associated with a type
    class EnumMetaData{
    private:
        
        std::string m_name;
        int32_t m_value;
        
    public:
        
        //! Copy constructor
        //! \param[in] enumeration to copy
        EnumMetaData(EnumMetaData const &metaData);
        //! Constructor
        //! \param[in] name the name of the enumeration
        //! \param[in] value the value of the enumeration
        EnumMetaData(const char *name, int32_t value);
        //! Destructor
        ~EnumMetaData();
        
        //! Returns the name of the enumeration
        //! \return the name of the enumeration
        const char* getName() const;
        //! Returns the value of the enumeration
        //! \return the value of the enumeration
        int32_t getValue() const;
    };
    
    //////////////////////////////////////////////////////////////////////////
    
    //! Holds all metadata asssociated with a type
    //! MetaData holds a collection of fields and enums with mapped offsets
    //! to allow runtime queries of class members. This is super useful
    //! when we need class member introspection.
    class TypeMetaData{
    public:
        
        typedef std::vector<core::FieldMetaData> FieldList;
        typedef std::vector<core::EnumMetaData> EnumList;
        typedef FieldList::iterator field_iterator;
        typedef FieldList::const_iterator const_field_iterator;
        typedef EnumList::iterator enumeration_iterator;
        typedef EnumList::const_iterator const_enumeration_iterator;
        
    private:
        
        core::TypeDatabase *m_pTypeDatabase;
        core::TypeId m_typeId;
        std::string m_name;
        int32_t m_size;
        std::vector<core::FieldMetaData> m_fields;
        std::vector<core::EnumMetaData> m_enums;
        
    public:
        
        //! Copy constructor
        //! \param[in] metadata the metadata to copy
        TypeMetaData(core::TypeMetaData const &metaData);
        //! Constructor
        //! \param[in] pOwner the owner DB of this type
        //! \param[in] typeId the typeId of this type
        //! \param[in] name the name of this type
        //! \param[in] size the size (bytes) of this type
        TypeMetaData(core::TypeDatabase *pTypeDatabase, core::TypeId typeId, const char *name, int32_t size);
        //! Destructor
        ~TypeMetaData();
        
        //! Sets the owner db
        void setTypeDatabase(core::TypeDatabase *pTypeDatabase);
        //! Returns the owner db
        //! \return the owner db
        core::TypeDatabase* getTypeDatabase() const;
        //! Returns the typeId
        //! \return the typeId
        core::TypeId getTypeId() const;
        //! Returns the type name
        //! \return the type name
        const char* getName() const;
        //! Returns the type size (bytes)
        //! \return the type size (bytes)
        int32_t getSize() const;
        
        //! Sets the fields associated with this type
        //! \param[in] fields the fields to be set
        //! \return the type that was modified
        template <std::size_t N>
        core::TypeMetaData* fields(core::FieldMetaData (&fields)[N]);
        
        //! Sets the enumerations associated with this type
        //! \param[in] enumerations the enumerations to be set
        //! \return the type that was modified
        template <std::size_t N>
        core::TypeMetaData* enums(core::EnumMetaData (&enums)[N]);
        
        //! Returns a field associated with a name
        //! \return a field associated with a name
        core::FieldMetaData* findField(const char *name);
        
        //! Returns the number of fields
        //! \return the number of fields
        size_t getNumFields();
        //! Returns the field by index
        core::FieldMetaData const* getFieldByIndex(size_t index) const;
        
        //! Returns the begin field iterator
        //! \return the begin field iterator
        field_iterator beginField();
        //! Returns the end field iterator
        //! \return the end field iterator
        field_iterator endField();
        //! Returns the begin const field iterator
        //! \return the begin const field iterator
        const_field_iterator beginField() const;
        //! Returns the end const field iterator
        //! \return the end const field iterator
        const_field_iterator endField() const;

        //! Returns the begin enumeration iterator
        //! \return the begin enumeration iterator
        enumeration_iterator beginEnumeration();
        //! Returns the end enumeration iterator
        //! \return the end enumeration iterator
        enumeration_iterator endEnumeration();
        //! Returns the begin const enumeration iterator
        //! \return the begin const enumeration iterator
        const_enumeration_iterator beginEnumeration() const;
        //! Returns the end const enumeration iterator
        //! \return the end const enumeration iterator
        const_enumeration_iterator endEnumeration() const;
    };
    
    //////////////////////////////////////////////////////////////////////////
    
    //! A database of types
    class TypeDatabase{
    private:
        
        typedef std::map<core::TypeId, core::TypeMetaData*> TypeIdToTypeIndex;
        typedef std::map<std::string, core::TypeId> NameToTypeIdIndex;
        TypeIdToTypeIndex m_typeIdToTypeIndex;
        NameToTypeIdIndex m_nameToTypeIdIndex;
        
    public:
        
        //! Constructor
        TypeDatabase();
        //! Constructor
        TypeDatabase(TypeDatabase const &typeDatabase);
        //! Destructor
        ~TypeDatabase();
        
        //! Registers a type
        //! \param[in] name the name of the type to register
        //! \return the type that was generated
        template <typename T>
        core::TypeMetaData* registerType(const char *name, bool replace = false);
        //! Unregister a type
        //! \param[in[ name the name of the type to unregister
        void unregisterType(const char *name);
        
        //! Returns a type by name
        //! \return a type by name
        core::TypeMetaData* findType(const char *name);
        //! Returns a type by typeId
        //! \return a type by typeId
        core::TypeMetaData* findType(core::TypeId typeId);
        //! Returns a type by type
        //! \return a type by type
        template <typename T>
        core::TypeMetaData* findType();
    };
    
    //////////////////////////////////////////////////////////////////////////
    
    //! Returns the typeId given a type
    template <typename T>
    TypeId getTypeId(){
        static core::TypeId typeId = core::hash_djb2(typeid(T).name());\
        return typeId;
    }
    
    //! Constructor
    //! \param[in] name the name of the field
    //! \param[in] field a pointer to the object member
    //! \param[in] flags the flags associated with this field
    template <typename OBJ_TYPE, typename FIELD_TYPE>
    FieldMetaData::FieldMetaData(const char *name, FIELD_TYPE OBJ_TYPE::*member, int32_t flags)
    :m_name(name)
    ,m_offset(((std::size_t)&(((OBJ_TYPE*)0)->*member)))
    ,m_size(sizeof(FIELD_TYPE))
    ,m_typeId(core::getTypeId<FIELD_TYPE>())
    ,m_pType(0)
    ,m_flags(flags){
    }
    
    //! Sets the fields associated with this type
    //! \param[in] fields the fields to be set
    //! \return the type that was modified
    template <std::size_t N>
    core::TypeMetaData* TypeMetaData::fields(core::FieldMetaData (&fields)[N]){
        m_fields.clear();
        for(int32_t i = 0; i < N; i++){
            core::FieldMetaData field = fields[i];
            if(m_pTypeDatabase){
                field.setType(m_pTypeDatabase->findType(field.typeId()));
            }
            m_fields.push_back(field);
        }
        return this;
    };
    //! Sets the enumerations associated with this type
    //! \param[in] enumerations the enumerations to be set
    //! \return the type that was modified
    template <std::size_t N>
    core::TypeMetaData* TypeMetaData::enums(core::EnumMetaData (&enums)[N]){
        m_enums.clear();
        for(int32_t i = 0; i < N; i++){
            m_enums.push_back(enums[i]);
        }
        return this;
    };
    
    //! Registers a type
    //! \param[in] name the name of the type to register
    //! \return the type that was generated
    template <typename T>
    core::TypeMetaData* TypeDatabase::registerType(const char *name, bool replace){
        NameToTypeIdIndex::iterator it = m_nameToTypeIdIndex.find(name);
        
        // remove old type
        if(it != m_nameToTypeIdIndex.end()){
            if(replace == true){
                TypeId typeId = it->second;
                TypeIdToTypeIndex::iterator it2 = m_typeIdToTypeIndex.find(typeId);
                delete it2->second;
                m_nameToTypeIdIndex.erase(it);
                m_typeIdToTypeIndex.erase(it2);
                core::logger_info("type", "Replacing type with name \"%s\"", name);
            }else{
                core::logger_error("type", "Failed to register type - duplicate name \"%s\" found", name);
                return 0;
            }
        }
        
        // add type
        {
            TypeId typeId = core::getTypeId<T>();
            TypeIdToTypeIndex::iterator it = m_typeIdToTypeIndex.find(typeId);
            if(it == m_typeIdToTypeIndex.end()){
                core::TypeMetaData *pType = new /*( metadata static )*/ core::TypeMetaData(this, typeId, name, sizeof(T));
                m_typeIdToTypeIndex.insert(std::make_pair(typeId, pType));
                m_nameToTypeIdIndex.insert(std::make_pair(name, typeId));
                core::logger_info("type", "Type \"%s\" was registered with id %s", name, core::lexical_cast(typeId).c_str());
                return pType;
            }else{
                core::logger_error("type", "Failed to register type with name \"%s\" - duplicate id \"%s\" found", name, core::lexical_cast(typeId).c_str());
                return 0;
            }
        }
    }
    
    //! Returns a type by type
    //! \return a type by type
    template <typename T>
    core::TypeMetaData* TypeDatabase::findType(){
        TypeIdToTypeIndex::iterator it = m_typeIdToTypeIndex.find(core::getTypeId<T>());
        if(it != m_typeIdToTypeIndex.end()){
            return it->second;
        }
        return 0;
    }

    //////////////////////////////////////////////////////////////////////////
    
    template <typename T>
    core::TypeMetaData* createTypeMetaData(const char *name, core::TypeDatabase *pTypeDatabase = 0){
        return new /* (metadata) */ TypeMetaData(pTypeDatabase, core::getTypeId<T>(), name, sizeof(T));
    }
};};

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////
