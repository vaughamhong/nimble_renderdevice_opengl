//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_core_assert_h__
#define __nimble_core_assert_h__

//////////////////////////////////////////////////////////////////////////

#include <stdint.h>

//////////////////////////////////////////////////////////////////////////

namespace nimble{
namespace core{
    
    //! asserts on expresssion and halts
    //! \param expression the expression to assert on
    void assert_error(bool expression);
    //! asserts on expresssion and halts
    //! \param expression the expression to assert on
    //! \param format the message format
    //! \param ... variable argument list
    void assert_error(bool expression, const char *format, ...);
    //! asserts on expresssion and warns
    //! \param expression the expression to assert on
    //! \param format the message format
    //! \param ... variable argument list
    void assert_warn(bool expression, const char *format, ...);
};};

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////