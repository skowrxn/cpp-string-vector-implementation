#include <functional>
#include <algorithm>
#include <string>
#include <cstring>
#include <stdexcept>
#include <utility> // std::exchange
#include "PtrCStringVector.h"
using namespace std;


PtrCStringVector::PtrCStringVector() : size_(0), capacity_(10) {
    data_ = new char *[capacity_]();
}

PtrCStringVector::PtrCStringVector(const PtrCStringVector &srcPtrCStringVector) {
    capacity_ = srcPtrCStringVector.capacity_;
    size_ = srcPtrCStringVector.size_;
    data_ = new char *[capacity_]();
    for (size_t i = 0; i < size_; ++i) {
        size_t len = std::strlen(srcPtrCStringVector.data_[i]) + 1;
        data_[i] = new char[len];
        std::strcpy(data_[i], srcPtrCStringVector.data_[i]);
    }
}

PtrCStringVector::~PtrCStringVector() {
    free();
}

PtrCStringVector &PtrCStringVector::operator=(const PtrCStringVector &source) {
    if (this != &source) {
        PtrCStringVector temp(source);
        std::swap(data_, temp.data_);
        std::swap(size_, temp.size_);
        std::swap(capacity_, temp.capacity_);
    }
    return *this;
}

PtrCStringVector &PtrCStringVector::operator=(PtrCStringVector &&source) {
    if (this != &source) {
        free();
        data_ = std::exchange(source.data_, nullptr);
        size_ = std::exchange(source.size_, 0);
        capacity_ = std::exchange(source.capacity_, 0);
    }
    return *this;
}

void PtrCStringVector::push_back(const char *text2Add) {
    if (!text2Add) {
        throw std::invalid_argument("Nullptr text");
    }
    if (size_ >= capacity_) {
        reserve(capacity_ * 2);
    }
    size_t len = strlen(text2Add) + 1;
    data_[size_] = new char[len];
    strcpy(data_[size_], text2Add);
    ++size_;
}

PtrCStringVector PtrCStringVector::operator+(const PtrCStringVector &anotherVector) const {
    PtrCStringVector result;
    result.reserve(size_ + anotherVector.size_);

    for (size_t i = 0; i < size_; ++i) {
        result.push_back(data_[i]);
    }
    for (size_t i = 0; i < anotherVector.size_; ++i) {
        result.push_back(anotherVector.data_[i]);
    }

    return result;
}

char *PtrCStringVector::operator[](std::size_t index) {
    if (index >= size_) {
        throw std::out_of_range("Index out of range");
    }
    return data_[index];
}

const char *PtrCStringVector::operator[](std::size_t index) const {
    if (index >= size_) {
        throw std::out_of_range("Index out of range");
    }
    return data_[index];
}

PtrCStringVector PtrCStringVector::operator&(const PtrCStringVector &rhs) const {
    PtrCStringVector result;
    const size_t min_size = std::min(size_, rhs.size_);
    const size_t max_size = std::max(size_, rhs.size_);

    result.reserve(max_size);

    for (size_t i = 0; i < min_size; ++i) {
        size_t len = std::strlen(data_[i]) + std::strlen(rhs.data_[i]) + 1;
        char *combined = new char[len];
        std::strcpy(combined, data_[i]);
        std::strcat(combined, rhs.data_[i]);
        result.push_back(combined);
        delete[] combined;
    }

    if (size_ > rhs.size_) {
        for (size_t i = min_size; i < max_size; ++i) {
            result.push_back(data_[i]);
        }
    } else if (rhs.size_ > size_) {
        for (size_t i = min_size; i < max_size; ++i) {
            result.push_back(rhs.data_[i]);
        }
    }

    return result;
}

void PtrCStringVector::free() {
    for (size_t i = 0; i < size_; ++i) {
        delete[] data_[i];
    }
    delete[] data_;
    data_ = nullptr;
    size_ = 0;
    capacity_ = 0;
}

void PtrCStringVector::reserve(std::size_t new_capacity) {
    if (new_capacity <= capacity_) return;

    char **newData = new char *[new_capacity]();
    for (size_t i = 0; i < size_; ++i) {
        newData[i] = new char[std::strlen(data_[i]) + 1];
        std::strcpy(newData[i], data_[i]);
    }

    for (size_t i = 0; i < size_; ++i) {
        delete[] data_[i];
    }
    delete[] data_;

    data_ = newData;
    capacity_ = new_capacity;
}
