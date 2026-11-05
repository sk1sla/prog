#pragma once

#include <cstddef>
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <type_traits>
#include <typeinfo>
#include <utility>

template <typename T>
class DynamicArray {
private:
    T* data;
    std::size_t size;

    void checkIndex(std::size_t index) const {
        if (index >= size)
            throw std::out_of_range("Error: index out of array bounds!");
    }

    void checkValue(const T& value) const {
        if constexpr (std::is_integral_v<T>) {
            if (value < static_cast<T>(-100) || value > static_cast<T>(100))
                throw std::invalid_argument("Error: value must be in range [-100, 100]!");
        }
    }

public:
    class Proxy {
    private:
        DynamicArray& arr;
        std::size_t index;
    public:
        Proxy(DynamicArray& a, std::size_t i) : arr(a), index(i) {
            arr.checkIndex(index);
        }
        Proxy& operator=(const T& value) { arr.set(index, value); return *this; }
        operator T() const { return arr.get(index); }
    };

    explicit DynamicArray(std::size_t sz = 0) : data(nullptr), size(sz) {
        if (size > 0) data = new T[size]();
    }

    ~DynamicArray() { delete[] data; }

    DynamicArray(const DynamicArray& other) : data(nullptr), size(other.size) {
        if (size > 0) {
            data = new T[size];
            std::copy(other.data, other.data + size, data);
        }
    }

    // copy-and-swap
    DynamicArray& operator=(const DynamicArray& other) {
        if (this == &other) return *this;
        DynamicArray tmp(other);
        std::swap(data, tmp.data);
        std::swap(size, tmp.size);
        return *this;
    }

    DynamicArray(DynamicArray&& other) noexcept
        : data(std::exchange(other.data, nullptr)),
          size(std::exchange(other.size, 0)) {}

    DynamicArray& operator=(DynamicArray&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = std::exchange(other.data, nullptr);
            size = std::exchange(other.size, 0);
        }
        return *this;
    }

    void set(std::size_t index, const T& value) {
        checkIndex(index);
        checkValue(value);
        data[index] = value;
    }

    T get(std::size_t index) const {
        checkIndex(index);
        return data[index];
    }

    void add(const T& value) {
        checkValue(value);
        T* newData = new T[size + 1];
        if (size > 0) std::copy(data, data + size, newData);
        newData[size] = value;
        delete[] data;
        data = newData;
        ++size;
    }

    void add(const DynamicArray& other) {
        for (std::size_t i = 0; i < size; ++i) {
            T otherValue = T();
            if (i < other.size) otherValue = other.data[i];
            T result = data[i] + otherValue;
            if constexpr (std::is_integral_v<T>) {
                if (result < static_cast<T>(-100) || result > static_cast<T>(100))
                    throw std::invalid_argument("Error: result of addition is out of range [-100, 100]!");
            }
            data[i] = result;
        }
    }

    void subtract(const DynamicArray& other) {
        for (std::size_t i = 0; i < size; ++i) {
            T otherValue = T();
            if (i < other.size) otherValue = other.data[i];
            T result = data[i] - otherValue;
            if constexpr (std::is_integral_v<T>) {
                if (result < static_cast<T>(-100) || result > static_cast<T>(100))
                    throw std::invalid_argument("Error: result of subtraction is out of range [-100, 100]!");
            }
            data[i] = result;
        }
    }

    double distance(const DynamicArray& other) const {
        if constexpr (std::is_arithmetic_v<T>) {
            if (size != other.size)
                throw std::invalid_argument("Error: array sizes must be equal for distance calculation!");
            double sum = 0.0;
            for (std::size_t i = 0; i < size; ++i) {
                double diff = static_cast<double>(data[i]) - static_cast<double>(other.data[i]);
                sum += diff * diff;
            }
            return std::sqrt(sum);
        } else {
            throw std::bad_typeid();
        }
    }

    std::size_t getSize() const { return size; }

    Proxy operator[](std::size_t index) { return Proxy(*this, index); }
    const T& operator[](std::size_t index) const {
        checkIndex(index);
        return data[index];
    }

    bool operator==(const DynamicArray& other) const {
        if (size != other.size) return false;
        for (std::size_t i = 0; i < size; ++i)
            if (data[i] != other.data[i]) return false;
        return true;
    }
    bool operator!=(const DynamicArray& other) const { return !(*this == other); }

    DynamicArray& operator+=(const DynamicArray& other) {
        for (std::size_t i = 0; i < size; ++i) {
            T otherValue = T();
            if (i < other.size) otherValue = other.data[i];
            T result = data[i] + otherValue;
            if constexpr (std::is_integral_v<T>) {
                if (result < static_cast<T>(-100) || result > static_cast<T>(100))
                    throw std::invalid_argument("Error: result of += is out of range [-100, 100]!");
            }
            data[i] = result;
        }
        return *this;
    }
    DynamicArray& operator-=(const DynamicArray& other) {
        for (std::size_t i = 0; i < size; ++i) {
            T otherValue = T();
            if (i < other.size) otherValue = other.data[i];
            T result = data[i] - otherValue;
            if constexpr (std::is_integral_v<T>) {
                if (result < static_cast<T>(-100) || result > static_cast<T>(100))
                    throw std::invalid_argument("Error: result of -= is out of range [-100, 100]!");
            }
            data[i] = result;
        }
        return *this;
    }
    DynamicArray& operator+=(const T& scalar) {
        for (std::size_t i = 0; i < size; ++i) {
            T result = data[i] + scalar;
            if constexpr (std::is_integral_v<T>) {
                if (result < static_cast<T>(-100) || result > static_cast<T>(100))
                    throw std::invalid_argument("Error: result of += scalar is out of range [-100, 100]!");
            }
            data[i] = result;
        }
        return *this;
    }
    DynamicArray& operator-=(const T& scalar) {
        for (std::size_t i = 0; i < size; ++i) {
            T result = data[i] - scalar;
            if constexpr (std::is_integral_v<T>) {
                if (result < static_cast<T>(-100) || result > static_cast<T>(100))
                    throw std::invalid_argument("Error: result of -= scalar is out of range [-100, 100]!");
            }
            data[i] = result;
        }
        return *this;
    }

    T* begin() { return data; }
    T* end()   { return data + size; }
    const T* begin() const { return data; }
    const T* end()   const { return data + size; }

    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const DynamicArray<U>& arr);
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const DynamicArray<T>& arr) {
    os << "[ ";
    for (std::size_t i = 0; i < arr.size; ++i) {
        os << arr.data[i];
        if (i + 1 < arr.size) os << ", ";
    }
    os << " ]";
    return os;
}