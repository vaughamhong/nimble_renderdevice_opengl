//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_iserializable_h__
#define __nimble_iserializable_h__

//////////////////////////////////////////////////////////////////////////

namespace nimble{
namespace core{
    class Stream;

    //! An abstract interface for encoding / decoding from a stream of data
    class ISerializable{
    public:
        //! Writes to this stream
        //! \param pStream the stream to decode to
        virtual void encode(core::Stream *pStream) const = 0;
        //! Reads from this stream
        //! \param pStream the stream to decode from
        virtual void decode(core::Stream *pStream) = 0;
    };
};};

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////