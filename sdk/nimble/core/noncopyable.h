//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_core_noncopyable_h__
#define __nimble_core_noncopyable_h__

//////////////////////////////////////////////////////////////////////////

namespace nimble{
namespace core{
    
    //! Anything that inherits this can not be copied
    class NonCopyable{
    protected:
        
        //! Constructor
        NonCopyable(){}
        //! Destructor
        ~NonCopyable(){}
        
    private:
        
        //! Copy constructor
        NonCopyable(NonCopyable const &){}
        //! Assignment operator
        NonCopyable& operator(NonCopyable const &){}
    };
};};

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////