//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_core_filesystem__
#define __nimble_core_filesystem__

//////////////////////////////////////////////////////////////////////////

#include <nimble/core/path.h>

//////////////////////////////////////////////////////////////////////////

namespace nimble{
namespace core{
    
    //! Returns true if the file exists
    bool fileExists(core::Path const path);
    //! Returns the file size located at path
    size_t fileSize(core::Path const path);
    
    //! Copies a file from the src to dest path
    void copyFile(core::Path const srcPath, Path const destPath);
    //! Creates a directory
    void createDirectory(core::Path const srcPath);
};};

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////