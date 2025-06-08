#include <functional>
#include <algorithm>
#include <string>
#include <cstring>
#include <stdexcept>
#include <utility> // std::exchange
#include "PtrCStringVector.h"
using namespace std;


PtrCStringVector::PtrCStringVector() : size_(0), capacity_(1)
{
    data_ = new char*[0];
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
    delete data_;

}

PtrCStringVector &PtrCStringVector::operator=(const PtrCStringVector &source)
{
    /// @todo zaimplementuj, szczegoly w pliku naglowkowym

    return *this;
}

PtrCStringVector& PtrCStringVector::operator=(PtrCStringVector&& source)
{
    /// @todo zaimplementuj, szczegoly w pliku naglowkowym

    return *this;
}

void PtrCStringVector::push_back(const char *text2Add)
{
    /// @todo zaimplementuj, szczegoly w pliku naglowkowym

}

PtrCStringVector PtrCStringVector::operator+(const PtrCStringVector &anotherVector) const
{
    /// @todo zaimplementuj, szczegoly w pliku naglowkowym
    return {};
}

char *PtrCStringVector::operator[](std::size_t index)
{
    /// @todo zaimplementuj, szczegoly w pliku naglowkowym
    return new char[1]{};
}
const char *PtrCStringVector::operator[](std::size_t index) const
{
    /// @todo zaimplementuj, szczegoly w pliku naglowkowym
    return "";
}

PtrCStringVector PtrCStringVector::operator&(const PtrCStringVector &rhs) const
{
    /// @todo zaimplementuj, szczegoly w pliku naglowkowym
    return {};
}

void PtrCStringVector::free()
{
    /// @todo sugeruje zaimplementowac, szczegoly w pliku naglowkowym
}

void PtrCStringVector::reserve(std::size_t new_capacity)
{
    /// @todo sugeruje zaimplementowac, szczegoly w pliku naglowkowym
}
