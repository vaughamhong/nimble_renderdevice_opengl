//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_core_searchpaths__
#define __nimble_core_searchpaths__

//////////////////////////////////////////////////////////////////////////

#include <string>
#include <vector>

//////////////////////////////////////////////////////////////////////////

namespace nimble{
namespace core{
    
    //! Tracks a set of search paths
    //! Able to check for file existence
    class SearchPaths{
    private:
        
        typedef std::vector<std::string> PathList;
        PathList m_searchPaths;

    public:
        
        //! Constructor
        SearchPaths();
        //! Destructor
        virtual ~SearchPaths();
        
    public:
        
        //! adds a search path
        virtual void addSearchPath(const char *path);
        //! removes a search path
        virtual void removeSearchPath(const char *path);
        
    public:
                
        //! returns full path
        //! \param path the file to look for
        //! \return the full file path
        virtual std::string findFullPath(const char *path);
    };
};};

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////