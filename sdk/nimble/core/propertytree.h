//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_core_propertytree__
#define __nimble_core_propertytree__

//////////////////////////////////////////////////////////////////////////

#include <nimble/resource/resourceloader.h>
#include <stdint.h>
#include <string>
#include <vector>
#include <map>

//////////////////////////////////////////////////////////////////////////

namespace nimble{
namespace core{
    
    //! A property tree holds a (name, value) pair and
    //! manages a list of children.
    class PropertyTree{
    public:
        
        typedef std::vector<PropertyTree>       List;
        typedef List::iterator                  iterator;
        typedef List::const_iterator            const_iterator;
        typedef std::vector<PropertyTree*>      PtrList;
        
    private:
        
        std::string     m_name;
        std::string     m_value;
        List            m_children;
        
    public:
        
        //! Loads property tree from xml file
        void loadFromXMLFile(const char *path);
        //! Loads property tree from json file
        void loadFromJSONFile(const char *path);
        
    public:
        
        //! Constructor
        PropertyTree();
        //! Constructor
        PropertyTree(PropertyTree const &tree);
        //! Constructor
        PropertyTree(std::string const &name, std::string const &value);
        //! Constructor
        PropertyTree(const char *name, const char *value);
        //! Destructor
        virtual ~PropertyTree();
        
    public:

        //! copy operator
        PropertyTree& operator=(PropertyTree const &tree);
        //! equality operator
        bool operator==(PropertyTree const &tree) const;
        //! inequality operator
        bool operator!=(PropertyTree const &tree) const;
        
    public:
        
        //! adds a property
        PropertyTree& add(const char *name, const char *value);
        //! adds a property
        PropertyTree& add(const char *name, int32_t value);
        //! removes a property
        void remove(iterator it);
        
        //! returns the first property
        iterator begin();
        //! returns the last property
        iterator end();
        //! returns the first property
        const_iterator begin() const;
        //! returns the last property
        const_iterator end() const;
        
        //! returns true if property with a name exists
        bool existsChildWithName(const char *name) const;
        //! filters for chidlren with name
        void filterChildrenWithName(const char *name, PtrList &list) const;
        
        //! returns list of children with name
        PtrList operator[](const char *name) const;
        
    public:
        
        //! sets our value
        void setValue(const char *value);
        
    public:
        
        //! returns the name
        const char* getName() const;
        //! returns the value
        const char* getValue() const;
        
        //! returns the value as a float
        float getFloatValue() const;
        //! returns the value as a integer
        int getIntValue() const;
        //! returns the value as a boolean
        bool getBoolValue() const;
        
    private:
        
        //! copies a propert tree
        PropertyTree& copy(PropertyTree const &tree);
    };
    
    //! Property tree loader
    class PropertyTreeXMLLoader
    : public resource::IResourceLoader{
    public:
        
        //! Constructor
        PropertyTreeXMLLoader();
        //! Destructor
        virtual ~PropertyTreeXMLLoader();
        
        //! loads a resource
        //! \param path the path of the file we want to load
        virtual resource::IResource* load(const char* path);
    };
    
    //! Property tree loader
    class PropertyTreeJSONLoader
    : public resource::IResourceLoader{
    public:
        
        //! Constructor
        PropertyTreeJSONLoader();
        //! Destructor
        virtual ~PropertyTreeJSONLoader();
        
        //! loads a resource
        //! \param path the path of the file we want to load
        virtual resource::IResource* load(const char* path);
    };
};};

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////