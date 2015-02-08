//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_core_error_h__
#define __nimble_core_error_h__

//////////////////////////////////////////////////////////////////////////

#include <stdint.h>
#include <string>

//////////////////////////////////////////////////////////////////////////

#define ERRORS_TUPLESET \
ERRORS_TUPLE(kNotImplemented,   -1,     "",      "You have accessed something that has been unimplemented") \
ERRORS_TUPLE(kSuccess,          0,      "",      "") \
ERRORS_TUPLE(kFailure,          1,      "",      "Something went wrong")

//////////////////////////////////////////////////////////////////////////

namespace nimble{
namespace core{
    
    //! throwable error
    class Error{
    private:
        
        int32_t m_code;
        std::string m_category;
        std::string m_string;
        
    public:
        
        //! Constructor
        Error();
        //! Constructor
        Error(int32_t code, const char *category, const char *string = 0);
        //! copy constructor
        Error(Error const &error);
        //! Destructor
        virtual ~Error();
        
    public:
        
        //! returns the error code
        int32_t getCode();
        //! returns the category
        const char* getCategory();
        //! returns the error string
        const char* getString();
        
    public:
        
        //! equality operator
        bool operator==(int32_t code);
        //! inequality operator
        bool operator!=(int32_t code);
        //! equality operator
        bool operator==(Error const &error);
        //! inequality operator
        bool operator!=(Error const &error);
    };
    
#define ERRORS_TUPLE(VAR, CODE, CATEGORY, STRING) extern nimble::core::Error VAR;
    ERRORS_TUPLESET
#undef ERRORS_TUPLE
};};

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////