//
// Created by marius on 1/26/26.
//

// Supported by GCC, Clang, MSVC

// DynamicArray<T>
// ----------------
// A simple resizable array implementation.
// Implemented as a template so it can store elements of any type T.
// Used to demonstrate memory allocation, resizing, and basic container design.
// This is an educational implementation (not a replacement for std::vector).

#pragma once
#include <cstddef>
#include <stdexcept>

namespace dsa {

template <class T>
class DynamicArray {
public:
    DynamicArray()
        : data_(nullptr), size_(0), capacity_(0) {}

    ~DynamicArray() {
        delete[] data_;
    }

    std::size_t size() const {
        return size_;
    }

    std::size_t capacity() const {
        return capacity_;
    }

    T& operator[](std::size_t index) {
        return data_[index];
    }

    const T& operator[](std::size_t index) const {
        return data_[index];
    }

    // Safe access
    T& at(std::size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data_[index];
    }

    const T& at(std::size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data_[index];
    }

    void reserve(std::size_t newCapacity) {
        if (newCapacity <= capacity_)
            return;

        T* newData = new T[newCapacity];

        for (std::size_t i = 0; i < size_; ++i) {
            newData[i] = data_[i];
        }

        delete[] data_;
        data_ = newData;
        capacity_ = newCapacity;
    }

    void push_back(const T& value) {
        if (size_ == capacity_) {
            std::size_t newCapacity = (capacity_ == 0) ? 1 : capacity_ * 2;
            reserve(newCapacity);
        }

        data_[size_] = value;
        ++size_;
    }

    void pop_back() {
        if (size_ == 0) {
            throw std::out_of_range("Pop from empty array");
        }
        --size_;
    }

    // Part B (lab / homework)
    void insert(std::size_t index, const T& value) {
        if (index > size_) {
            throw std::out_of_range("Insert index out of range");
        }

        if (size_ == capacity_) {
            std::size_t newCapacity = (capacity_ == 0) ? 1 : capacity_ * 2;
            reserve(newCapacity);
        }

        for (std::size_t i = size_; i > index; --i) {
            data_[i] = data_[i - 1];
        }

        data_[index] = value;
        ++size_;
    }

    void erase(std::size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Erase index out of range");
        }

        for (std::size_t i = index; i < size_ - 1; ++i) {
            data_[i] = data_[i + 1];
        }

        --size_;
    }

private:
    T* data_;
    std::size_t size_;
    std::size_t capacity_;
};

} // namespace dsa
