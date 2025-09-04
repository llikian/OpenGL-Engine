/***************************************************************************************************
 * @file  HeapArray.hpp
 * @brief Declaration of the HeapArray class
 **************************************************************************************************/

#pragma once

#include <initializer_list>
#include <iostream>

/**
 * @class HeapArray
 * @brief
 */
template <typename Type>
class HeapArray {
public:
    HeapArray() : size(0), data(nullptr) { }

    explicit HeapArray(size_t size)
        : size(size), data(new Type[size]) {
        for(unsigned int i = 0 ; i < size ; ++i) { data[i] = Type(); }
    }

    HeapArray(const std::initializer_list<Type>& values)
        : size(values.size()), data(new Type[size]) {
        for(unsigned int i = 0 ; i < size ; ++i) { data[i] = values[i]; }
    }

    ~HeapArray() {
        delete[] data;
    }

    Type& operator[](size_t index) { return data[index]; }

    const Type& operator[](size_t index) const { return data[index]; }

    size_t get_size() const { return size; }

    Type* get_data() const { return data; }

    void resize(size_t new_size) {
        if(new_size > 0) {
            Type* new_data = new Type[new_size];
            for(unsigned int i = 0 ; i < new_size ; ++i) { new_data[i] = (i < size) ? data[i] : Type(); }

            delete[] data;
            size = new_size;
            data = new_data;
        } else {
            size = 0;
            data = nullptr;
        }
    }

    bool empty() const { return size > 0; }

    Type* begin() { return data; }

    Type* end() { return data + size; }

    const Type* cbegin() const { return data; }

    const Type* cend() const { return data + size; }

    const Type* begin() const { return data; }

    const Type* end() const { return data + size; }

private:
    size_t size;
    Type* data;
};
