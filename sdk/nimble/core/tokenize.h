//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_core_tokenize_h__
#define __nimble_core_tokenize_h__

//////////////////////////////////////////////////////////////////////////

#include <string>
#include <vector>

//////////////////////////////////////////////////////////////////////////

namespace nimble{
namespace core{

    //! tokenizes a string relative to a separation delimeter
    //! \param tokens the resulting tokens
    //! \param pString the string to tokenize
    //! \param delimeter the separation delimeter
    void tokenize(std::vector<std::string> &tokens, const char *pString, const char delimeter);
};};

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////