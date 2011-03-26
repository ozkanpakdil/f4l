/*
 *  FSTransform.cpp
 *  Transform SWF
 *
 *  Created by smackay on Mon Feb 10 2003.
 *  Copyright (c) 2001-2003 Flagstone Software Ltd. All rights reserved.
 *
 *  This file contains Original Code and/or Modifications of Original Code as defined in
 *  and that are subject to the Flagstone Software Source License Version 1.0 (the
 *  'License'). You may not use this file except in compliance with the License. Please
 *  obtain a copy of the License at http://www.flagstonesoftware.com/licenses/source.html
 *  and read it before using this file.
 *
 *  The Original Code and all software distributed under the License are distributed on an
 *  'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, AND Flagstone
 *  HEREBY DISCLAIMS ALL SUCH WARRANTIES, INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF
 *  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT OF THIRD PARTY
 *  RIGHTS. Please see the License for the specific language governing rights and limitations
 *  under the License.
 */

#include "FSTransform.h"

#include <stdlib.h>
#include <stdio.h>
#include <zlib.h>

#include "FSException.h"

using namespace transform;

#ifdef WIN32
#ifdef _WINDLL

#define WIN32_LEAN_AND_MEAN

#include <windows.h>

BOOL APIENTRY DllMain( Qt::HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

#endif // _WINDLL
#endif // WIN32

namespace transform
{
    byte* dataFromFile(const char* fileName, size_t& size)
    {
        FILE* input = 0;
        byte* buffer = 0;
        long length = 0;

        if ((input = fopen(fileName, "rb")) == 0)
            throw FSFileOpenException("Cannot open file");

        if (fseek(input, 0, SEEK_END) != 0)
            throw FSAccessException("Cannot read file");

        if ((length = ftell(input)) == -1L)
            throw FSAccessException("Cannot read file");

        rewind(input);

        buffer = new byte[length];

        if (length > 0 && buffer == NULL)
            throw FSAllocationException();

        if (fread(buffer, sizeof(byte), length, input) != length)
            throw FSAccessException("Cannot read file");

        if (fclose(input) != 0)
            throw FSAccessException("Cannot read file");

        size = length;
        return buffer;
    }
    
    byte* zip(const byte* bytes, size_t size, size_t offset, size_t& compressedSize)
    {
        unsigned long numberOfBytes = (unsigned long)(size * 1.1f);

        numberOfBytes = (numberOfBytes > 64) ? numberOfBytes : 64;
        
        Byte* dest = (Byte*)calloc(numberOfBytes, sizeof(Byte));

        if (dest == NULL)
            throw FSAllocationException();

        Byte* source = (Byte*)calloc(size, sizeof(byte));
        
        if (source == NULL)
            throw FSAllocationException();

        memcpy(source, bytes, size*sizeof(byte));

        if (compress(dest, &numberOfBytes, source+offset, size-offset) != Z_OK)
            throw FSFormatException("Cannot compress data");

        byte* data = new byte[numberOfBytes+offset];

        memcpy(data, bytes, offset);
        memcpy(data+offset, dest, numberOfBytes);
        compressedSize = numberOfBytes+offset;

        free(source);
        free(dest);

        return data;
    }
    
    byte* unzip(const byte* bytes, size_t size, size_t& uncompressedSize)
    {
        unsigned long numberOfBytes = uncompressedSize;
        
        Bytef* source = (Byte*)calloc(size, sizeof(Byte));

        if (source == NULL)
            throw FSAllocationException();

        memcpy(source, bytes, size);

        Bytef* dest = (Byte*)calloc(numberOfBytes, sizeof(Byte));
 
        if (dest == NULL)
            throw FSAllocationException();

        if (uncompress(dest, &numberOfBytes, source, size) != Z_OK)
            throw FSFormatException("Cannot uncompress movie");

        byte* data = new byte[numberOfBytes];

        memcpy(data, dest, numberOfBytes);
        uncompressedSize = numberOfBytes;

        free(source);
        free(dest);

        return data;
    }
}
