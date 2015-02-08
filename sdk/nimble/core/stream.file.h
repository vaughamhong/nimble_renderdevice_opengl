//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_core_Stream_file__
#define __nimble_core_Stream_file__

//////////////////////////////////////////////////////////////////////////

#include <nimble/core/stream.h>
#include <nimble/core/smartptr.h>
#include <fstream>

//////////////////////////////////////////////////////////////////////////

namespace nimble{
namespace core{
    
    //! file based Stream
    class FileStream
    : public Stream{
    public:
        
        enum eOffsetReference{
            kSeekBeginning,
            kSeekCurrent,
            kSeekEnd
        };
        
    private:
        
        std::string             m_filePath;
        mutable std::fstream    m_fileStream;
        
    public:
        
        //! Constructor
        FileStream(const char *filePath, bool createMissingPath = false);
        //! Destructor
        virtual ~FileStream();
        
    public:
        
        //! returns the size of our Stream
        virtual size_t size() const;
        //! returns true if this buffer is empty
        virtual bool isEmpty() const;
        
    public:
        
        //! Writes to this stream
        virtual void write(char const *pBuffer, size_t size);
        //! Reads from this stream
        virtual void read(char *pBuffer, size_t size);
        //! Reads line from this stream
        virtual void readLine(char *pBuffer, size_t size);
        //! seeks
        virtual void seek(uint32_t location, eOffsetReference ref = kSeekBeginning);
    };
    typedef core::SmartPtr<FileStream> FileStreamPtr;
};};

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////