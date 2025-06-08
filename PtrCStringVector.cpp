#include <functional>
#include <algorithm>
#include <string>
#include <cstring>
#include <stdexcept>
#include <utility> // std::exchange
#include "PtrCStringVector.h"
using namespace std;


PtrCStringVector::PtrCStringVector() : size_(0), capacity_(10)
{
    data_ = new char*[capacity_];
}

PtrCStringVector::PtrCStringVector(const PtrCStringVector &srcPtrCStringVector): PtrCStringVector()
{
    capacity_ = srcPtrCStringVector.capacity_;
    size_ = srcPtrCStringVector.size_;
    data_ = new char*[capacity_];
    for (size_t i = 0; i < size_; ++i) {
        size_t len = std::strlen(srcPtrCStringVector.data_[i]) + 1;
        data_[i] = new char[len];
        std::strcpy(data_[i], srcPtrCStringVector.data_[i]);
    }
}

PtrCStringVector::~PtrCStringVector()
{
    for (size_t i = 0; i < size_; i++) {
        delete data_[i];
    }
    delete[] data_;

}

PtrCStringVector &PtrCStringVector::operator=(const PtrCStringVector &source)
{
    if (data_ == source.data_ && size_ == source.size_ && capacity_ == source.capacity_)
        return *this;
    
    free();
    capacity_ = source.capacity_;
    size_ = source.size_;
    data_ = new char*[capacity_];
    for (size_t i = 0; i < size_; ++i) {
        size_t len = std::strlen(source.data_[i]) + 1;
        data_[i] = new char[len];
        std::strcpy(data_[i], source.data_[i]);
    }
    
    return *this;
}

PtrCStringVector& PtrCStringVector::operator=(PtrCStringVector&& source)
{
    if (this != &source) {
        free();
        capacity_ = source.capacity_;
        size_ = source.size_;
        data_ = source.data_;
        source.capacity_ = 0;
        source.size_ = 0;
        source.data_ = nullptr;
    }
    return *this;

}

void PtrCStringVector::push_back(const char *text2Add)
{
    if (size_ >= capacity_) {
        reserve(capacity_*2);
    }
    data_[size_] = new char[strlen(text2Add)+1];
    strcpy(data_[size_], text2Add);
    ++size_;

}

PtrCStringVector PtrCStringVector::operator+(const PtrCStringVector &anotherVector) const
{
    size_t new_size = size_ + anotherVector.size_;
    size_t new_capacity = capacity_ + anotherVector.capacity_;
    char** new_data = new char*[new_capacity];
    for (size_t i = 0; i < size_; ++i) {
        strcpy(new_data[i], data_[i]);
    }
    for (size_t i = 0; i < anotherVector.size(); ++i) {
        strcpy(new_data[size_+i], anotherVector[i]);
    }
    PtrCStringVector result;
    result.size_ = new_size;
    result.capacity_ = capacity_;
    result.data_ = new_data;
    return result;
}

char *PtrCStringVector::operator[](std::size_t index)
{
    if (index >= size_) {
        throw std::out_of_range("Index out of range");
    }
    return data_[index];
}
const char *PtrCStringVector::operator[](std::size_t index) const
{
    if (index >= size_) {
        throw std::out_of_range("Index out of range");
    }

    return const_cast<PtrCStringVector *>(this)->operator[](index);
}

PtrCStringVector PtrCStringVector::operator&(const PtrCStringVector &rhs) const {
    PtrCStringVector result;
    const size_t min_size = std::min(size_, rhs.size_);
    const size_t max_size = std::max(size_, rhs.size_);

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

void PtrCStringVector::free()
{
    for (size_t i = 0; i < size_; ++i) {
        delete data_[i];
    }
    delete[] data_;
    size_ = 0;
    capacity_ = 1;
}

void PtrCStringVector::reserve(std::size_t new_capacity)
{
    if (new_capacity <= capacity_)return;
    capacity_ = new_capacity;
    char** newData = new char*[capacity_];
    for (size_t i = 0; i < size_; ++i) {
        newData[i] = new char[strlen(data_[i])+1];
        strcpy(newData[i], data_[i]);
        delete data_[i];
    }
    delete[] data_;
    data_ = newData;
}
