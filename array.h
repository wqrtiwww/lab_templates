#pragma once

#include <cstddef>
#include <algorithm>

template <typename T>
class Array {
public:
    Array();
    explicit Array(std::size_t size);
    Array(std::size_t size, const T& value);

    Array(const Array& other);
    Array(Array&& other) noexcept;
    Array& operator=(const Array& other);
    Array& operator=(Array&& other) noexcept;

    ~Array();

    T& operator[](std::size_t index);
    const T& operator[](std::size_t index) const;

    T& front();
    const T& front() const;

    T& back();
    const T& back() const;

    T* data() noexcept;
    const T* data() const noexcept;

    std::size_t size() const noexcept;
    bool empty() const noexcept;

    void fill(const T& value);
    void swap(Array& other) noexcept;

    bool operator==(const Array& rhs) const;
    bool operator!=(const Array& rhs) const;

private:
    T* data_ = nullptr;
    std::size_t size_ = 0;
};

template <typename T>
Array<T>::Array() : data_(nullptr), size_(0) {}

template <typename T>
Array<T>::Array(std::size_t size) : data_(new T[size]()), size_(size) {}

template <typename T>
Array<T>::Array(std::size_t size, const T& value) : data_(new T[size]), size_(size) {
    std::fill(data_, data_ + size_, value);
}

template <typename T>
Array<T>::Array(const Array& other) : data_(new T[other.size_]), size_(other.size_) {
    std::copy(other.data_, other.data_ + other.size_, data_);
}

template <typename T>
Array<T>::Array(Array&& other) noexcept : data_(other.data_), size_(other.size_) {
    other.data_ = nullptr;
    other.size_ = 0;
}

template <typename T>
Array<T>& Array<T>::operator=(const Array& other) {
    if (this != &other) {
        Array temp(other);
        swap(temp);
    }
    return *this;
}

template <typename T>
Array<T>& Array<T>::operator=(Array&& other) noexcept {
    if (this != &other) {
        delete[] data_;
        data_ = other.data_;
        size_ = other.size_;
        other.data_ = nullptr;
        other.size_ = 0;
    }
    return *this;
}

template <typename T>
Array<T>::~Array() {
    delete[] data_;
}

template <typename T>
T& Array<T>::operator[](std::size_t index) {
    return data_[index];
}

template <typename T>
const T& Array<T>::operator[](std::size_t index) const {
    return data_[index];
}

template <typename T>
T& Array<T>::front() {
    return data_[0];
}

template <typename T>
const T& Array<T>::front() const {
    return data_[0];
}

template <typename T>
T& Array<T>::back() {
    return data_[size_ - 1];
}

template <typename T>
const T& Array<T>::back() const {
    return data_[size_ - 1];
}

template <typename T>
T* Array<T>::data() noexcept {
    return data_;
}

template <typename T>
const T* Array<T>::data() const noexcept {
    return data_;
}

template <typename T>
std::size_t Array<T>::size() const noexcept {
    return size_;
}

template <typename T>
bool Array<T>::empty() const noexcept {
    return size_ == 0;
}

template <typename T>
void Array<T>::fill(const T& value) {
    std::fill(data_, data_ + size_, value);
}

template <typename T>
void Array<T>::swap(Array& other) noexcept {
    using std::swap;
    swap(data_, other.data_);
    swap(size_, other.size_);
}

template <typename T>
bool Array<T>::operator==(const Array& rhs) const {
    if (size_ != rhs.size_) return false;
    for (std::size_t i = 0; i < size_; ++i) {
        if (data_[i] != rhs.data_[i]) return false;
    }
    return true;
}

template <typename T>
bool Array<T>::operator!=(const Array& rhs) const {
    return !(*this == rhs);
}
