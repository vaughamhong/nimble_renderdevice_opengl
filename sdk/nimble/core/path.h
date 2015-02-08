//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_core_path__
#define __nimble_core_path__

//////////////////////////////////////////////////////////////////////////

#include <string>

//////////////////////////////////////////////////////////////////////////

// TODO: handle unicode strings

//////////////////////////////////////////////////////////////////////////

namespace nimble{
namespace core{
    
    //! Helper class for managing paths
    class Path{
    private:
        
        std::string m_path;
        
    public:
        
        //! Constructor
        Path();
        //! Constructor
        Path(const char *path);
        //! Constructor
        Path(std::string const &path);
        //! Constructor
        Path(Path const &path);
        //! Destructor
        ~Path();
        
    public:
        
        //! Sets a path
        Path& operator=(Path const &path);
        
        //! Checks for equality
        bool operator==(Path const &path);
        //! Checks for equality
        bool operator==(const char *path);
        
        //! Checks for inequality
        bool operator!=(Path const &path);
        //! Checks for inequality
        bool operator!=(const char *path);
        
    public:
        
        //! Returns the full path
        std::string getFullPath() const;
        //! Returns the extension
        std::string getExtension() const;
        //! Returns the basename
        std::string getBasename() const;
        //! Returns the filename
        std::string getFilename() const;
        //! Returns the directory
        std::string getDirectory() const;
        
    public:
        
        //! returns the directory of the path up one level
        Path popDirectory() const;
    };
};};

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////