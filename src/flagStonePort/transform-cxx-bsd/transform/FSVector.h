/*
 *  FSVector.h
 *  Transform SWF
 * 
 * Copyright (c) 2001-2004 Flagstone Software Ltd.. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, 
 * are permitted provided that the following conditions are met:
 *
 *  * Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright notice, 
 *    this list of conditions and the following disclaimer in the documentation 
 *    and/or other materials provided with the distribution.
 *  * Neither the name of Flagstone Software Ltd. nor the names of its contributors 
 *    may be used to endorse or promote products derived from this software 
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND 
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
 * IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, 
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, 
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE 
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED 
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __FSVECTOR_H__
#define __FSVECTOR_H__ 1

#include "FSException.h"
#include <new.h>

namespace transform
{
    /** The FSVector class is a simple implementation of the STL template class vector. It is included in the Transform library to ensure binary compatibility when using the library with different versions of a given compiler.

        @author Stuart MacKay
        */
    template <class T> class FSVector
    {
public:
        /** Defines the extra space allocated in the vector for additional elements. */ 
        enum { SPARE_CAPACITY=16 };

        /** Constructs a vector with the specified number of elements.

            @param size the number of elements to define in the vector.
            */
        FSVector(int size=0);

        FSVector(const FSVector& rhs) { operator=(rhs); }

        ~FSVector();

        const FSVector& operator= (const FSVector& rhs);

        /** Operator to set an element in the vector. If the index is outside the range supported by the vector then an FSArrayIndexOutofBoundsException will be thrown.

            @param index an index into the vector.
            */
        T& operator[] (int index);

        /** Operator to return an element in the vector. If the index is outside the range supported by the vector then an FSArrayIndexOutofBoundsException will be thrown.

            @param index an index into the vector.
            @return the element in the vector at the specified index.
            */
        const T& operator[] (int index) const;

        /** Is the vector empty. Returns true of the vector does not contain any elements, false otherwise.

            @return true if the vector is empty, false otherwise.
            */
        bool empty() const { return _size == 0; }

        /** Returns the number of elements in the vector.

            @return the number of elements in the vector.
            */
        int size() const { return _size; }

        /** Returns the total number of elements which the vector can currently store without dynamically allocating more memory.

            @return the number of elements that the vector currently has allocated space for.
            */
        int capacity() const { return _capacity; }

        /** Changes the size of the array so it contains the specified number of elements. If the number specified is greater than the current capacity then new memory is allocated.

            @param count the number of elements in the resized vector.
            */
        void resize(int count);

        /** Changes the capacity of the vector. If the number specified is greater than the current capacity then new memory is allocated.

            @param count the total number of elements that the vector has currently allocated space for.
            */
        void reserve(int count);

        /** Return a reference to the first element in the vector. If the vector does not contain any elements then an FSArrayIndexOutOfBoundsException is thrown.

            @return the first element in the array.
            */
        T& front();

        /** Return a reference to the last element in the vector. If the vector does not contain any elements then an FSArrayIndexOutOfBoundsException is thrown.

            @return the last element in the array.
            */
        T& back();

        /** Appends an element to the vector, allocating space if required.

            @param x the element to be added.
            */
        void push_back(const T& x);

        /** Pops the last element from the vector. The number of elements stored is decremented by one.

            @return the last element in the vector.
            */
        T& pop_back();

        typedef T* iterator;
        typedef const T* const_iterator;

        /** Returns and initializes an iterator pointing at the first element in the vector.

            @return an iterator that starts the beginning of the vector.
            */
        iterator begin() { return (size() == 0) ? 0 : &_table[0]; }

        /** Returns and initializes a constant iterator pointing at the first element in the vector.

            @return a constant iterator that starts the beginning of the vector.
            */
        const_iterator begin() const { return (size() == 0) ? 0 : &_table[0]; }

        /** Returns and initializes an iterator pointing at the first free space after the last element in the vector.

            @return an iterator pointing beyond the last element in the vector.
            */
        iterator end() { return (size() == 0) ? 0 : &_table[_size]; }

        /** Returns and initializes a constant iterator pointing at the first free space after the last element in the vector.

            @return a constant iterator pointing beyond the last element in the vector.
            */
        const_iterator end() const { return (size() == 0) ? 0 : &_table[_size]; }
        
private:
        int _size;
        int _capacity;
        T* _table;
    };

    template <class T> FSVector<T>::FSVector(int size)
    {
        _size = size;
        _capacity = size + SPARE_CAPACITY;
        
        _table = new T[_capacity];
        
        if (_table == 0)
            throw FSAllocationException();

        T* dst = _table;

        for (int i=0; i<_size; i++, dst++)
            new (dst) T();
    }

    template <class T> FSVector<T>::~FSVector()
    {
        if (_table)
        {
            delete [] _table;
            _table = 0;
            
            _size = _capacity = 0;
        }
    }
    
    template <class T> const FSVector<T>& FSVector<T>::operator= (const FSVector<T>& rhs)
    {
        if (this != &rhs)
        {
            _size = rhs._size;
            _capacity = rhs._capacity;

            _table = new T[_capacity];

            if (_table == 0)
                throw FSAllocationException();

            T* src = rhs._table;
            T* dst = _table;

            for (int i=0; i<_size; i++, src++, dst++)
                new (dst) T(*src);
        }
        return *this;
    }

    template <class T> T& FSVector<T>::operator[] (int index)
    {
        if (index < 0 || index >= size())
            throw FSArrayIndexOutOfBoundsException(index, size());

        return _table[index];
    }

    template <class T> const T& FSVector<T>::operator[] (int index) const
    {
        if (index < 0 || index >= size())
            throw FSArrayIndexOutOfBoundsException(index, size());

        return _table[index];
    }

    template <class T> void FSVector<T>::resize(int count)
    {
        _size = count;

        if (count > _capacity)
            reserve(count*2);
     }

    template <class T> void FSVector<T>::reserve(int count)
    {
        _capacity = count;

        T* newTable = new T[_capacity];

        if (newTable == 0)
            throw FSAllocationException();

        T* src = _table;
        T* dst = newTable;

        for (int i=0; i<_size; i++, src++, dst++)
            new (dst) T(*src);

        delete [] _table;
        _table = newTable;
    }

    template <class T>T& FSVector<T>::front()
    {
        if (empty())
            throw FSArrayIndexOutOfBoundsException(1, 0);

        return _table[0];
    }

    template <class T>T& FSVector<T>::back()
    {
        if (empty())
            throw FSArrayIndexOutOfBoundsException(1, 0);

        return _table[_size-1];
    }

    template <class T> void FSVector<T>::push_back(const T& x)
    {
        if (_size == _capacity)
            reserve(2*_capacity+1);

        T *dst = _table + _size++;

        new (dst) T(x);
    }

    template <class T> T& FSVector<T>::pop_back()
    {
        if (empty())
            throw FSArrayIndexOutOfBoundsException(_size-1, _size-1);

        _size--;
        
        return _table[_size];
    }
}

#endif


