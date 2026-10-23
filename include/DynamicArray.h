#pragma once

#include <cstddef>
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <type_traits>
#include <typeinfo>

template <typename T>
class DynamicArray {
private:
    T* data;
    std::size_t size;

    // Проверка индекса
    void checkIndex(std::size_t index) const {
        if (index >= size) {
            throw std::out_of_range("Error: index out of array bounds!");
        }
    }

    // Проверка значения (только для целочисленных типов)
    void checkValue(const T& value) const {
        if constexpr (std::is_integral_v<T>) {
            if (value < static_cast<T>(-100) || value > static_cast<T>(100)) {
                throw std::invalid_argument("Error: value must be in range [-100, 100]!");
            }
        }
    }

public:
    // Конструктор
    explicit DynamicArray(std::size_t sz = 0) : data(nullptr), size(sz) {
        if (size > 0) {
            data = new T[size]();
        }
    }

    // Деструктор
    ~DynamicArray() {
        delete[] data;
    }

    // Конструктор копирования
    DynamicArray(const DynamicArray& other) : data(nullptr), size(other.size) {
        if (size > 0) {
            data = new T[size];
            std::copy(other.data, other.data + size, data);
        }
    }

    // Сеттер
    void set(std::size_t index, const T& value) {
        checkIndex(index);
        checkValue(value);
        data[index] = value;
    }

    // Геттер
    T get(std::size_t index) const {
        checkIndex(index);
        return data[index];
    }

    // Добавление одного элемента в конец
    void add(const T& value) {
        checkValue(value);
        
        T* newData = new T[size + 1];
        if (size > 0) {
            std::copy(data, data + size, newData);
        }
        newData[size] = value;
        
        delete[] data;
        data = newData;
        ++size;
    }

    // Поэлементное сложение с другим массивом
    void add(const DynamicArray& other) {
        for (std::size_t i = 0; i < size; ++i) {
            T otherValue = T(); // Значение по умолчанию (0 для чисел, пустая строка для string)
            if (i < other.size) {
                otherValue = other.data[i];
            }
            
            T result = data[i] + otherValue;
            
            // Проверка диапазона результата только для целых чисел
            if constexpr (std::is_integral_v<T>) {
                if (result < static_cast<T>(-100) || result > static_cast<T>(100)) {
                    throw std::invalid_argument("Error: result of addition is out of range [-100, 100]!");
                }
            }
            data[i] = result;
        }
    }

    // Поэлементное вычитание другого массива
    void subtract(const DynamicArray& other) {
        for (std::size_t i = 0; i < size; ++i) {
            T otherValue = T();
            if (i < other.size) {
                otherValue = other.data[i];
            }
            
            T result = data[i] - otherValue;
            
            // Проверка диапазона результата только для целых чисел
            if constexpr (std::is_integral_v<T>) {
                if (result < static_cast<T>(-100) || result > static_cast<T>(100)) {
                    throw std::invalid_argument("Error: result of subtraction is out of range [-100, 100]!");
                }
            }
            data[i] = result;
        }
    }

    // Расстояние между массивами
    double distance(const DynamicArray& other) const {
        // Только для чисел
        if constexpr (std::is_arithmetic_v<T>) {
            // Размеры должны быть одинаковы
            if (size != other.size) {
                throw std::invalid_argument("Error: array sizes must be equal for distance calculation!");
            }

            double sum = 0.0;
            for (std::size_t i = 0; i < size; ++i) {
                double diff = static_cast<double>(data[i]) - static_cast<double>(other.data[i]);
                sum += diff * diff;
            }
            
            return std::sqrt(sum);
        } else {
            // Для всего кроме чисел
            throw std::bad_typeid();
        }
    }

    std::size_t getSize() const {
        return size;
    }

    // Дружественная функция для operator<<
    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const DynamicArray<U>& arr);
};

// Реализация operator<< вне класса
template <typename T>
std::ostream& operator<<(std::ostream& os, const DynamicArray<T>& arr) {
    os << "[ ";
    for (std::size_t i = 0; i < arr.size; ++i) {
        os << arr.data[i];
        if (i + 1 < arr.size) {
            os << ", ";
        }
    }
    os << " ]";
    return os;
}