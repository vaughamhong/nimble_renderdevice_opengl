//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

//////////////////////////////////////////////////////////////////////////

#include <nimble/core/logger.h>
#include <nimble/core/hash.h>
#include <unordered_map>

//////////////////////////////////////////////////////////////////////////

namespace nimble{
    namespace core{

        //! Statically locates an object identified by a scope
        //! At one point the Locator was built with a collection of activator
        //! functors which could create / destroy objects on the fly. This meant
        //! our objects were created on demand and could happen at any time. This
        //! make our object graph somewhat non-determinstic and more difficult to
        //! debug. Not to mention C++ functors are not the easiest concepts to grasp.
        //! We simplify this by removing the concept of activators, and force
        //! the application client to manage the creation / destruction of their own
        //! resources. The locator is just a static registery of objects, nothing more.
        
        template <typename T>
        struct Locator{
            typedef std::unordered_map<int64_t, T*> HashToObjectIndex;
            static HashToObjectIndex                m_hashToObjectIndex;
        };
        template <typename T>
        typename core::Locator<T>::HashToObjectIndex core::Locator<T>::m_hashToObjectIndex;
        
        //! gets an object for a scope
        template <typename T>
        T* locator_acquire(const char *scope){
            typedef typename core::Locator<T>::HashToObjectIndex HashToObjectIndex;
            HashToObjectIndex &hashToObjectIndex = core::Locator<T>::m_hashToObjectIndex;

            int64_t hash = core::hash_djb2(scope);
            typename HashToObjectIndex::const_iterator it = hashToObjectIndex.find(hash);
            if(it != hashToObjectIndex.end()){
                return it->second;
            }else{
                return 0;
            }
        }
        //! Sets an object for a scope
        template <typename T>
        void locator_provide(T *pObject, const char *scope){
            typedef typename core::Locator<T>::HashToObjectIndex HashToObjectIndex;
            HashToObjectIndex &hashToObjectIndex = core::Locator<T>::m_hashToObjectIndex;
            
            int64_t hash = core::hash_djb2(scope);
            typename HashToObjectIndex::const_iterator it = hashToObjectIndex.find(hash);
            if(it == hashToObjectIndex.end()){
                hashToObjectIndex.insert(std::make_pair(hash, pObject));
                return;
            }else{
                core::logger_warning("core", "Failed to provide object with scope \"%s\"", scope);
            }
        }
        //! Erases an object for a scope
        template <typename T>
        void locator_release(const char *scope){
            typedef typename core::Locator<T>::HashToObjectIndex HashToObjectIndex;
            HashToObjectIndex &hashToObjectIndex = core::Locator<T>::m_hashToObjectIndex;
            
            int64_t hash = core::hash_djb2(scope);
            typename HashToObjectIndex::iterator it = hashToObjectIndex.find(hash);
            if(it != hashToObjectIndex.end()){
                hashToObjectIndex.erase(it++);
            }else{
                core::logger_warning("core", "Failed to release object with scope \"%s\"", scope);
            }
        }
        //! clears all objects
        template <typename T>
        void locator_clear(){
            typedef typename core::Locator<T>::HashToObjectIndex HashToObjectIndex;
            HashToObjectIndex &hashToObjectIndex = core::Locator<T>::m_hashToObjectIndex;

            hashToObjectIndex.clear();
        }
        //! checks if a locator exists
        template <typename T>
        bool locator_exists(const char *scope){
            typedef typename core::Locator<T>::HashToObjectIndex HashToObjectIndex;
            HashToObjectIndex &hashToObjectIndex = core::Locator<T>::m_hashToObjectIndex;

            int64_t hash = core::hash_djb2(scope);
            typename HashToObjectIndex::iterator it = hashToObjectIndex.find(hash);
            return it != hashToObjectIndex.end();
        }
    };
};

//////////////////////////////////////////////////////////////////////////