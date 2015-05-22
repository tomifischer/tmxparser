//-----------------------------------------------------------------------------
// TmxUtil.cpp
//
// Copyright (c) 2010-2014, Tamir Atias
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//  * Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL TAMIR ATIAS BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Author: Tamir Atias
//-----------------------------------------------------------------------------
#include <stdlib.h>
#include <boost/algorithm/string.hpp>
#include <sstream>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filter/zlib.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/iostreams/filtering_stream.hpp>

#ifdef USE_MINIZ
#define MINIZ_HEADER_FILE_ONLY
#include "miniz.c"
#else
#include <zlib.h>
#endif

#include <stdio.h>

#include "TmxUtil.h"
#include "base64/base64.h"

namespace Tmx {

    std::string &Util::Trim(std::string &str)
    {
        boost::algorithm::trim( str );
        return str;
    }

    std::string Util::DecodeBase64(const std::string &str) 
    {
        return base64_decode(str);
    }

    Util::ByteArray Util::DecompressZLIB(const std::string& data, unsigned int expectedSize)
    {
        Util::ByteArray decompressed;
        decompressed.reserve( expectedSize );

        boost::iostreams::filtering_ostream os;
        os.push(boost::iostreams::zlib_decompressor());
        os.push(boost::iostreams::back_inserter(decompressed));

        os << data;

        return decompressed;
    }

    Util::ByteArray Util::DecompressGZIP(const std::string& data, unsigned int expectedSize)
    {
        Util::ByteArray decompressed;
        decompressed.reserve( expectedSize );

        boost::iostreams::filtering_ostream os;
        os.push(boost::iostreams::gzip_decompressor());
        os.push(boost::iostreams::back_inserter(decompressed));

        os << data;

        return decompressed;
    }
}
