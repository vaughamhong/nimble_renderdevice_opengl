//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#ifndef __nimble_core_stream_h__
#define __nimble_core_stream_h__

//////////////////////////////////////////////////////////////////////////

#include <stdint.h>
#include <nimble/core/buffer.h>
#include <nimble/core/functor.h>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>

//////////////////////////////////////////////////////////////////////////

namespace nimble{
namespace core{
    
    //! generic data stream
    class Stream{
    public:
        
        //! Constructor
        Stream();
        //! Destructor
        virtual ~Stream();
    
    public:
        
        //! returns the size of our Stream
        virtual size_t size() const = 0;
        //! returns true if this buffer is empty
        virtual bool isEmpty() const = 0;
        
    public:
        
        //! writes to this data stream
        virtual void write(char const *pBuffer, size_t size) = 0;
        //! reads from this data stream
        virtual void read(char *pBuffer, size_t size) = 0;
        
    public:
        
        //! reads from our buffer
        template <typename T> Stream& operator >> (T& value){this->read((char *)&value, sizeof(T)); return *this;}
        //! writes to our buffer
        template <typename T> Stream& operator << (const T& value){this->write((char *)&value, sizeof(T)); return *this;}
        
    public:
        
        //! drains this data stream
        template <typename Allocator>
        Stream& operator >>= (core::Buffer<Allocator> &buffer){
            buffer.resize(size());
            char *pBuffer = &buffer[0];
            this->read(pBuffer, size());
            return *this;
        }
        //! drains this data stream
        Stream& operator >>= (std::stringstream &stream){
            size_t size = this->size();
            char *buffer = new /*( temp volatile )*/ char[size];
            this->read(buffer, size);
            stream.write(buffer, size);
            delete [] buffer;
            return *this;
        }
        
    public:
        
        //! std::fstream write specialization
        Stream& operator << (std::ifstream& stream){
            std::filebuf *pbuf = stream.rdbuf();
            unsigned int bufferSize = (unsigned int)pbuf->pubseekoff(0, std::ios::end, std::ios::in);
            char *buffer = new /*( temp volatile )*/ char[bufferSize];
            stream.seekg(0, std::ios::beg);
            stream.read(buffer, bufferSize);
            this->write(buffer, bufferSize);
            delete [] buffer;
            return *this;
        }
        
    public:
        
        //! std::string write specialization
        Stream& operator << (const std::string& value){
            size_t stringLength = value.length();
            *this << stringLength;
            this->write(value.c_str(), stringLength);
            return *this;
        }
        //! std::string read specialization
        Stream& operator >> (std::string &value){
            size_t stringLength;
            *this >> stringLength;
            char *c_string = new /*( temp volatile )*/ char[stringLength + 1];
            memset(c_string, 0, stringLength + 1);
            this->read(c_string, stringLength);
            value = std::string(c_string);
            delete [] c_string;
            return *this;
        }
        
    public:
        
        //! functor write specialization
        template <typename Func>
        Stream& operator << (const BindAllFunctor<Func>& value){
            BindAllFunctor<Func> *pClone = value.clone();
            *this << pClone;
            return *this;
        }
        //! std::string read specialization
        template <typename Func>
        Stream& operator >> (BindAllFunctor<Func>& value){
            BindAllFunctor<Func> *pClone = 0;
            *this >> pClone;
            value = *pClone;
            delete pClone;
            return *this;
        }
        
    public:
        
        //! std::vector write specialization
        template <typename T>
        Stream& operator << (const std::vector<T> &list){
            int numItems = list.size();
            *this << numItems;
            for(typename std::vector<T>::const_iterator it = list.begin(); it != list.end(); it++){
                *this << *it;
            }
            return *this;
        }
        //! std::vector read specialization
        template <typename T>
        Stream& operator >> (std::vector<T> &list){
            int numItems = 0;
            *this >> numItems;
            T value;
            for(int i = 0; i < numItems; i++){
                *this >> value;
                list.push_back(value);
            }
            return *this;
        }
        
    public:
        
        //! std::map write specialization
        template <typename K, typename T>
        Stream& operator << (const std::map<K, T> &dict){
            int numItems = dict.size();
            *this << numItems;
            for(typename std::map<K, T>::const_iterator it = dict.begin(); it != dict.end(); it++){
                *this << it->first;
                *this << it->second;
            }
            return *this;
        }
        //! std::map read specialization
        template <typename K, typename T>
        Stream& operator >> (std::map<K, T> &dict){
            int numItems = 0;
            *this >> numItems;
            K key; T value;
            for(int i = 0; i < numItems; i++){
                *this >> key;
                *this >> value;
                dict[key] = value;
            }
            return *this;
        }
    };
};};

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////