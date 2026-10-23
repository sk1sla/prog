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

    void checkIndex(std::size_t index) const {
        if (index >= size) {
            throw std::out_of_range("Error: index out of array bounds!");
        }
    }

    void checkValue(const T& value) const {
        if constexpr (std::is_integral_v<T>) {
            if (value < static_cast<T>(-100) || value > static_cast<T>(100)) {
                throw std::invalid_argument("Error: value must be in range [-100, 100]!");
            }
        }
    }

public:
    // --- Прокси-класс для operator[] ---
    // Он позволяет чтению работать как обычно, а записи — проходить через set()
    class Proxy {
    private:
        DynamicArray& arr;
        std::size_t index;
    public:
        Proxy(DynamicArray& a, std::size_t i) : arr(a), index(i) {
            arr.checkIndex(index); // Проверяем индекс сразу при обращении
        }
        
        // При записи (arr[i] = value) вызываем set, чтобы сработала проверка значения
        Proxy& operator=(const T& value) {
            arr.set(index, value);
            return *this;
        }
        
        // При чтении (value = arr[i]) просто возвращаем значение через get
        operator T() const {
            return arr.get(index);
        }
    };

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

    // Поэлементное сложение с другим массивом (старый метод, оставлен для совместимости)
    void add(const DynamicArray& other) {
        for (std::size_t i = 0; i < size; ++i) {
            T otherValue = T();
            if (i < other.size) {
                otherValue = other.data[i];
            }
            T result = data[i] + otherValue;
            if constexpr (std::is_integral_v<T>) {
                if (result < static_cast<T>(-100) || result > static_cast<T>(100)) {
                    throw std::invalid_argument("Error: result of addition is out of range [-100, 100]!");
                }
            }
            data[i] = result;
        }
    }

    // Поэлементное вычитание другого массива (старый метод)
    void subtract(const DynamicArray& other) {
        for (std::size_t i = 0; i < size; ++i) {
            T otherValue = T();
            if (i < other.size) {
                otherValue = other.data[i];
            }
            T result = data[i] - otherValue;
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
        if constexpr (std::is_arithmetic_v<T>) {
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
            throw std::bad_typeid();
        }
    }

    std::size_t getSize() const {
        return size;
    }

    // ==========================================
    // НОВЫЕ ОПЕРАТОРЫ ПО ЗАДАНИЮ
    // ==========================================

    // 1. Оператор обращения по индексу
    Proxy operator[](std::size_t index) {
        return Proxy(*this, index);
    }

    const T& operator[](std::size_t index) const {
        checkIndex(index);
        return data[index];
    }

    // 2. Операторы сравнения
    bool operator==(const DynamicArray& other) const {
        if (size != other.size) return false;
        for (std::size_t i = 0; i < size; ++i) {
            if (data[i] != other.data[i]) return false;
        }
        return true;
    }

    bool operator!=(const DynamicArray& other) const {
        return !(*this == other);
    }

    // 3. Составные операторы с другим массивом
    DynamicArray& operator+=(const DynamicArray& other) {
        for (std::size_t i = 0; i < size; ++i) {
            T otherValue = T(); // 0 для чисел, "" для строк
            if (i < other.size) {
                otherValue = other.data[i];
            }
            T result = data[i] + otherValue;
            if constexpr (std::is_integral_v<T>) {
                if (result < static_cast<T>(-100) || result > static_cast<T>(100)) {
                    throw std::invalid_argument("Error: result of += is out of range [-100, 100]!");
                }
            }
            data[i] = result;
        }
        return *this;
    }

    DynamicArray& operator-=(const DynamicArray& other) {
        for (std::size_t i = 0; i < size; ++i) {
            T otherValue = T();
            if (i < other.size) {
                otherValue = other.data[i];
            }
            T result = data[i] - otherValue;
            if constexpr (std::is_integral_v<T>) {
                if (result < static_cast<T>(-100) || result > static_cast<T>(100)) {
                    throw std::invalid_argument("Error: result of -= is out of range [-100, 100]!");
                }
            }
            data[i] = result;
        }
        return *this;
    }

    // 3. Составные операторы со скаляром (одним значением)
    DynamicArray& operator+=(const T& scalar) {
        for (std::size_t i = 0; i < size; ++i) {
            T result = data[i] + scalar;
            if constexpr (std::is_integral_v<T>) {
                if (result < static_cast<T>(-100) || result > static_cast<T>(100)) {
                    throw std::invalid_argument("Error: result of += scalar is out of range [-100, 100]!");
                }
            }
            data[i] = result;
        }
        return *this;
    }

    DynamicArray& operator-=(const T& scalar) {
        for (std::size_t i = 0; i < size; ++i) {
            T result = data[i] - scalar;
            if constexpr (std::is_integral_v<T>) {
                if (result < static_cast<T>(-100) || result > static_cast<T>(100)) {
                    throw std::invalid_argument("Error: result of -= scalar is out of range [-100, 100]!");
                }
            }
            data[i] = result;
        }
        return *this;
    }

    // 4. Итераторы для range-based for loop
    // Указатели в C++ уже являются полноценными итераторами
    T* begin() { return data; }
    T* end() { return data + size; }

    const T* begin() const { return data; }
    const T* end() const { return data + size; }

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