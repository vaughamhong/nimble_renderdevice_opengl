//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_com_unknown_h__
#define __nimble_com_unknown_h__

//////////////////////////////////////////////////////////////////////////

#include <stdint.h>
#include <assert.h>
#include <algorithm>
#include <vector>

//////////////////////////////////////////////////////////////////////////

namespace nimble{
namespace core{

    //! COM style unknown interface provides a standard way to
    //! manage and access object interfaces.
    class Unknown{
    public:

        enum{
            kInterfaceFound = 0,
            kInterfaceNotFound = 1,
        };

    private:

        typedef std::vector<core::Unknown*>     InterfaceList;
        typedef InterfaceList::iterator			InterfaceIterator;
        typedef InterfaceList::const_iterator   InterfaceConstIterator;
        InterfaceList							m_interfaceList;

    public:

        //! Constructor
        Unknown(){
            m_interfaceList.clear();
        }
        //! Destructor
        virtual ~Unknown(){
            removeAllInterfaces();
        }

    public:

        //! Checks if an interface exists
        template <typename T> bool interfaceExists(){
            T* pInterface = 0;
            return (queryInterface<T>(&pInterface) == 0);
        }
        //! Returns an interface
        //! \param ppInterface the pointer to our interface pointer (to set)
        //! \return the error code
        template<typename T> int32_t queryInterface(T** ppInterface){
            // look for interface from this pointer
            *ppInterface = dynamic_cast<T*>(this);
            if(*ppInterface != 0){
                return kInterfaceFound;
            }
            // look for interface from our interface list
            for(InterfaceIterator it = m_interfaceList.begin(); it != m_interfaceList.end(); it++){
                *ppInterface = dynamic_cast<T*>(*it);
                if(*ppInterface != 0){
                    return kInterfaceFound;
                }
            }
            return kInterfaceNotFound;
        }
        //! Returns an interface
        //! \param ppInterface the pointer to our interface pointer (to set)
        //! \return the error code
        template<typename T> int32_t queryInterface(const T** ppInterface) const{
            // look for interface from this pointer
            *ppInterface = dynamic_cast<const T*>(this);
            if(*ppInterface != 0){
                return kInterfaceFound;
            }
            // look for interface from our interface list
            for(InterfaceConstIterator it = m_interfaceList.begin(); it != m_interfaceList.end(); it++){
                *ppInterface = dynamic_cast<T*>(*it);
                if(*ppInterface != 0){
                    return kInterfaceFound;
                }
            }
            return kInterfaceNotFound;
        }
        //! Call with interface
        //! \return a pointer to the interface (to call on)
        template <typename T> T* callInterface(){
            T *pInterface = 0;
            if(this->queryInterface<T>(&pInterface) == kInterfaceFound){
                return pInterface;
            }
            return 0;
        }
        
    public:

        //! Adds a new interface
        //! \param pInterface the interface to add
        //! \return the error code
        void addInterface(Unknown* pInterface){
            InterfaceList::iterator it = std::find(m_interfaceList.begin(), m_interfaceList.end(), pInterface);
            if(it == m_interfaceList.end()){
                m_interfaceList.push_back(pInterface);
            }
        }
        //! Removes an interface
        //! \return the error code
        void removeInterface(Unknown* pInterface){
            InterfaceList::iterator it = std::find(m_interfaceList.begin(), m_interfaceList.end(), pInterface);
            if(it != m_interfaceList.end()){
                m_interfaceList.erase(it);
            }
        }
        //! Removes all interfaces
        //! \return the error code
        void removeAllInterfaces(){
            m_interfaceList.clear();
        }
    };
};};

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////