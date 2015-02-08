//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_core_smartptrmap_h__
#define __nimble_core_smartptrmap_h__

//////////////////////////////////////////////////////////////////////////

#include <nimble/core/smartptr.h>
#include <nimble/core/assert.h>
#include <map>

//////////////////////////////////////////////////////////////////////////

namespace nimble{
namespace core{

    //! The repository is a container for a set of smart pointer objects
    template <typename K, typename T>
    class SmartPtrMap{
    public:
        
        typedef K                               Key;
        typedef core::SmartPtr<T>               SmartPtr;
        typedef std::map<Key, SmartPtr>         Map;
        typedef typename Map::iterator          Iterator;
        typedef typename Map::const_iterator    ConstIterator;
        
    public:

//        //! Owns the garbage collection of a repository
//        class GarbageCollector
//        : public Repository<T, KEY, SMARTPTR>{
//        private:
//            
//            Repository  *m_pRepository;
//            
//        public:
//
//            //! Constructor
//            GarbageCollector(Repository *pRepository):m_pRepository(pRepository){}
//            //! Destructor
//            virtual ~GarbageCollector(){}
//
//        public:    
//        
//            //! removes all resources that have been collected
//            virtual void update(){
//                typedef typename core::Repository<T, KEY, SMARTPTR>::Iterator Iterator;
//                typedef typename core::Repository<T, KEY, SMARTPTR>::SmartPtr SmartPtr;
//                
//                // remove (and delete) all resources that have been collected
//                for(Iterator it = m_database.begin(); it != m_database.end();){
//                    SmartPtr& ptr = it->second;
//                    if(ptr.isLast()){
//                        Iterator removeIt = it++;
//                        this->removeResource(removeIt);
//                    }else{
//                        it++;
//                    }
//                }
//            }
//
//            //! collect resource to garbage collect
//            virtual void collectGarbage(bool waitOnGarbageCollect = true){
//                typedef typename core::Repository<T, KEY, SMARTPTR>::Iterator Iterator;
//                typedef typename core::Repository<T, KEY, SMARTPTR>::SmartPtr SmartPtr;
//                assert(m_pRepository != 0);
//                
//                // collect all resources that are no longer referenced
//                for(Iterator it = m_pRepository->begin(); it != m_pRepository->end();){
//                    SmartPtr& ptr = it->second;
//                    if(ptr.isLast()){
//                        this->addResource(it->first, it->second);
//                        Iterator removeIt = it++;
//                        m_pRepository->removeResource(removeIt);
//                    }else{
//                        it++;
//                    }
//                }
//                // wait until all resources have been removed (and deleted)
//                if(waitOnGarbageCollect){
//                    while(this->getNumResources() != 0){
//                        update();
//                    }
//                }
//            }
//        };

    protected:

        Map m_database;

    public:

        //! Constructor
        SmartPtrMap(){
        }
        //! Destructor
        virtual ~SmartPtrMap(){
        }

    public:
        
        //! adds an item
        //! \param key the item key
        //! \param ptr the item to add
        virtual void add(Key key, SmartPtr& ptr){
            if(!exists(key) && ptr.isValid()){
                m_database[key] = ptr;
            }else{
                core::assert_warn(!exists(key), "[Repository::add] Adding duplicate object");
                core::assert_warn(ptr.isValid(), "[Repository::remove] Invalid smart pointer");
            }
        }
        //! removes an item
        //! \param key the unique key
        virtual void remove(Key key){
            Iterator it = m_database.find(key);
            if(it != m_database.end()){
                it->second.release();
                m_database.erase(it);
            }else{
                core::logger_warning("core", "[Repository::remove] Could not find object");
            }
        }
        //! gets an item
        //! \param key the unique key
        //! \return a smart SmartPtr to the item
        virtual SmartPtr get(Key key) const{
            ConstIterator it = m_database.find(key);
            if(it != m_database.end()){
                return it->second;
            }
            return SmartPtr();
        }
        //! checks an item exists
        //! \param key the unique key
        //! \return true if the item exists
        virtual bool exists(Key key){
            Iterator it = m_database.find(key);
            return it != m_database.end();
        }
        //! returns the number of item in this repository
        //! \return the number of item in this repository
        virtual uint32_t getSize(){
            return m_database.size();
        }
        //! returns true if there are no item in this repository
        virtual bool isEmpty() const{
            return m_database.size() == 0;
        }
        //! clear our database
        virtual void clear(){
            m_database.clear();
        }
        
        //! returns the begin iterator
        virtual Iterator begin(){
            return m_database.begin();
        }
        //! returns the end iterator
        virtual Iterator end(){
            return m_database.end();
        }
    };
};};

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////