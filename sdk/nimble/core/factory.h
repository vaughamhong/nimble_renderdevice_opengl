//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_core_factory_h__
#define __nimble_core_factory_h__

//////////////////////////////////////////////////////////////////////////

#include <nimble/core/assert.h>
#include <nimble/core/stringutil.h>
#include <nimble/core/functor.h>
#include <nimble/core/logger.h>
#include <map>

//////////////////////////////////////////////////////////////////////////

// TODO: deprecated class

//////////////////////////////////////////////////////////////////////////

namespace nimble{
namespace core{
    
    //! Note: typeid(T).name()'s return value is non-standard.
    //! typeid(T).name() may equal typeid(T2).name() for certain vendors. Also, there is no
    //! garentee that typeid(T).name() maps to any human readable class name. The only thing
    //! typeid(T).name() is good for is debug output. This means we can't use typeid(T).name()
    //! as our (automatic) BuilderId
    
    //! Factory for building objects
    //! Handles
    //! + Allows registration / unregistration of builder functors
    //! + Constructs products by referencing a builderId
    //! + Products must have a default constructor
    //! + Does not handle product book keeping
    template <typename Product, typename BuilderId>
    class Factory{
    public:

        //! class builder
        template <typename T> static Product* classBuilder(){return new /*( external dynamic )*/ T();}
        
        typedef core::Functor<Product*> Builder;
        typedef std::map<BuilderId, Builder> Builders;

    private:

        Builders m_builders;

    public:

        //! Constructor
        Factory(){
            m_builders.clear();
        }
        //! Destructor
        virtual ~Factory(){
            m_builders.clear();
        }

    public:

        //! registers a builder
        //! \param callback the callback being registered
        //! \return true if successful
        void registerBuilder(BuilderId builderId, Builder builder){
            if(builderExists(builderId)){
                core::logger_warning("core", "[core::factory] trying to register non-existent builder %s", core::lexical_cast(builderId).c_str());
            }else{
                m_builders.insert(std::pair<BuilderId, Builder>(builderId, builder));
            }
        }
        //! registers a builder
        //! \param callback the callback being registered
        //! \return true if successful
        template <typename C>
        void registerBuilder(BuilderId builderId){
            if(builderExists(builderId)){
                core::logger_warning("core", "[core::factory] trying to register non-existent builder %s", core::lexical_cast(builderId).c_str());
            }else{
                m_builders.insert(std::pair<BuilderId, Builder>(builderId, core::Factory<Product, BuilderId>::classBuilder<C>));
            }
        }

        //! unregisters a builder
        //! \return true if successful
        void unregister(BuilderId builderId){
            if(!builderExists(builderId)){
                core::logger_warning("core", "[core::factory] trying to unregister non-existent builder %s", core::lexical_cast(builderId).c_str());
            }else{
                m_builders.erase(builderId);
            }
        }

        //! checks if a builder exists
        //! \return true if the builder exists
        bool builderExists(BuilderId builderId) const{
            return m_builders.find(builderId) != m_builders.end();
        }
        
        //! clear all builders
        void clearBuilders(){
            m_builders.clear();
        }

    public:

        //! creates a product
        //! \return returns the constructed product
        Product* build(BuilderId builderId) const{
            typename Builders::const_iterator it = m_builders.find(builderId);
            if(it != m_builders.end()){
                return it->second();
            }
            core::logger_warning("core", "[core::factory] could not create an object of type id \"%s\"", core::lexical_cast(builderId).c_str());
            return 0;
        }
        
        //! creates a product
        //! \return returns the constructed product
        template <typename TargetProduct>
        TargetProduct* build(BuilderId builderId) const{
            typename Builders::const_iterator it = m_builders.find(builderId);
            if(it != m_builders.end()){
                Product *pProduct = it->second();
                TargetProduct *pTargetProduct = dynamic_cast<TargetProduct*>(pProduct);
                core::assert_error(pTargetProduct != 0, "Could not dynamically cast built product into target product");
                return pTargetProduct;
            }
            core::logger_warning("core", "[core::factory] could not create an object of type id \"%s\"", core::lexical_cast(builderId).c_str());
            return 0;
        }
    };
};};

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////