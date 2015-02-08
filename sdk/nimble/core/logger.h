//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_core_logger_h__
#define __nimble_core_logger_h__

//////////////////////////////////////////////////////////////////////////

#include <stdint.h>
#include <string>
#include <map>
#include <nimble/core/thread.mutex.h>

//////////////////////////////////////////////////////////////////////////

namespace nimble{
namespace core{
    class Stream;
    
    //////////////////////////////////////////////////////////////////////////
    
    //! creates a log category
    void logger_createCategory(const char *category, bool enabled = true, core::Stream *pStream = 0);
    //! destroys a log category
    void logger_destroyCategory(const char *category);
    
    //! enables a log category
    void logger_enable(const char *category);
    //! disables a log category
    void logger_disable(const char *category);
    //! sets a category stream
    void logger_setCategoryStream(const char *category, core::Stream *pStream);
    
    //! prints to a category
    void logger_info(const char *category, const char *format, ...);
    //! prints warning to a category
    void logger_warning(const char *category, const char *format, ...);
    //! prints error to a category
    void logger_error(const char *category, const char *format, ...);
    
    //////////////////////////////////////////////////////////////////////////
    
    //! Logs strings to output streams (console, file, ...etc.)
    class Logger{
    private:
        
        struct categoryInfo_t{
            core::Stream *pStream;
            bool isEnabled;
        };
        
        typedef std::map<std::string, categoryInfo_t> CategoryToInfoIndex;
        CategoryToInfoIndex m_categoryToInfoIndex;
        
        mutable core::Mutex m_lock;
        
        char *m_pBodyBuffer;
        int32_t m_bodyBufferSize;
        char *m_pOutputBuffer;
        int32_t m_outputBufferSize;
        
    public:
        
        //! Returns the default logger
        static Logger* get();
        
    public:
        
        //! Constructor
        Logger();
        //! Destructor
        virtual ~Logger();
        
    public:

        //! creates a category
        //! \param category the category we are checking
        void createCategory(const char *category, bool enabled = true, core::Stream *pStream = 0);
        //! destroys a category
        //! \param category the category we are checking
        void destroyCategory(const char *category);
        //! returns true if category exists
        //! \param category the category we are checking
        //! \return true if the category exists
        bool categoryExists(const char *category);
        
        //! set category stream
        void setCategoryStream(const char *category, core::Stream *pStream);
        //! gets category stream
        core::Stream* getCategoryStream(const char *category) const;
        
        //! enables category
        //! \param category the category of this message
        void enableCategory(const char *category);
        //! disables category
        //! \param category the category of this message
        void disableCategory(const char *category);
        //! checks if a log category is enabled
        //! \param category the category of this message
        //! \return true if the category is enabled
        bool isCategoryEnabled(const char *category);
        
    public:
        
        //! logs a message
        //! \param format the message format
        //! \param ... variable argument list
        void print(const char *category, const char *format, ...);
        //! logs a warning
        //! \param format the message format
        //! \param ... variable argument list
        void warn(const char *category, const char *format, ...);
        //! logs a error
        //! \param format the message format
        //! \param ... variable argument list
        void error(const char *category, const char *format, ...);
        
    public:
        
        //! logs a message
        //! \param format the message format
        //! \param ... variable argument list
        void print(const char *category, const char *format, va_list va);
        //! logs a warning
        //! \param format the message format
        //! \param ... variable argument list
        void warn(const char *category, const char *format, va_list va);
        //! logs a error
        //! \param format the message format
        //! \param ... variable argument list
        void error(const char *category, const char *format, va_list va);        
    };
};};

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////