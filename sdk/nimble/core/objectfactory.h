//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_core_objectfactory_h__
#define __nimble_core_objectfactory_h__

//////////////////////////////////////////////////////////////////////////

#include <map>
#include <nimble/core/functor.h>
#include <nimble/core/typemetadata.h>
#include <nimble/core/object.h>

//////////////////////////////////////////////////////////////////////////

namespace nimble{
namespace core{
    class Object;
    
    class ObjectFactory{
    public:
        
        typedef core::Functor<core::Object*> ConstructorFunc;
        typedef core::Functor<void, TLIST_1(core::Object*)> DestructorFunc;
        
        //! default constructor
        template <typename T> static core::Object* defaultConstructor(){return new /*( external dynamic )*/ T();}
        //! default destructor
        template <typename T> static void defaultDestructor(core::Object* pObject){delete pObject;}
        
    private:
        
        //! Holds additional metadata for an Object
        struct ObjectInfo{
            ConstructorFunc constructor;
            DestructorFunc destructor;
            
            ObjectInfo(ConstructorFunc constructor, DestructorFunc destructor)
            :constructor(constructor)
            ,destructor(destructor){
            }
            ObjectInfo(ObjectInfo const &objectInfo)
            :constructor(objectInfo.constructor)
            ,destructor(objectInfo.destructor){
            }
        };
        typedef std::map<std::string, core::TypeId> NameToTypeIdIndex;
        typedef std::map<core::TypeId, ObjectInfo> TypeIdToObjectInfoIndex;
        
        core::TypeDatabase m_typeDatabase;
        NameToTypeIdIndex m_nameToTypeIdIndex;
        TypeIdToObjectInfoIndex m_typeIdToObjectInfoIndex;

    public:

        //! Constructor
        ObjectFactory(){
        }
        //! Copy constructor
        ObjectFactory(ObjectFactory const &objectFactory)
        :m_typeDatabase(objectFactory.m_typeDatabase)
        ,m_nameToTypeIdIndex(objectFactory.m_nameToTypeIdIndex)
        ,m_typeIdToObjectInfoIndex(objectFactory.m_typeIdToObjectInfoIndex){
        }
        //! Destructor
        ~ObjectFactory(){
        }
        
    public:
                    
        //! Registers a type to be built
        //! \param[in] name the name of the type to build
        template <typename T>
        core::TypeMetaData* registerType(const char *name, ConstructorFunc constructor = defaultConstructor<T>, DestructorFunc destructor = defaultDestructor<T>, bool replace = false){
            if(!m_typeDatabase.findType<T>()){
                core::TypeMetaData *pTypeInfo = m_typeDatabase.registerType<T>(name, replace);
                core::TypeId typeId = pTypeInfo->getTypeId();
                m_nameToTypeIdIndex.insert(std::pair<std::string, core::TypeId>(name, typeId));
                m_typeIdToObjectInfoIndex.insert(std::pair<core::TypeId, ObjectInfo>(typeId, ObjectInfo(constructor, defaultDestructor<T>)));
                return pTypeInfo;
            }else{
                core::logger_warning("object", "Failed to register duplicate type with name \"%s\"", name);
                return 0;
            }
        }
        //! Unregister a type
        //! \param[in] name the name of the type to unregister
        void unregisterType(const char *name);
        
        //! Creates an object by name
        //! \param[in] name the name of the object type to create from
        //! \return the created object
        core::Object* create(const char *name);
        //! Destroy an object
        //! \param[in] pObject the object to destroy
        void destroy(core::Object *pObject);
        
    public:
        
        //! Creates an object from file
        //! \param name the name of the object to create
        //! \return a pointer to the object
        template <typename T>
        T* create(const char *name){
            if(core::Object *pObject = this->create(name)){
                T *pTargetObject = dynamic_cast<T*>(pObject);
                core::assert_error(pTargetObject != 0, "Failed to cast created object of type \"%s\" to target", name);
                return pTargetObject;
            }
            core::logger_warning("object", "Failed to create object with name \"%s\"", name);
            return 0;
        }
        //! Destroys an object
        //! \param pComponent the object to destroy
        template <typename T>
        void destroy(T *pTargetObject){
            core::Object *pObject = dynamic_cast<core::Object*>(pTargetObject);
            core::assert_error(pObject != 0, "Failed to cast to object from target");
            this->destroy(pObject);
        }
        //! Checks for existence
        template <typename T>
        bool exists(){
            return m_typeDatabase.findType<T>() != 0;
        }
    };
};};

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////