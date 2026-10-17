#include "DynamicArray.h"

#include <algorithm>
#include <iostream>
#include <new>

// === Проверки на индекс и значение

void DynamicArray::checkIndex(std::size_t index) const {
    if (index >= size) {
        throw std::out_of_range("Error: index out of array bounds!");
    }
}

void DynamicArray::checkValue(int value) const {
    if (value < -100 || value > 100) {
        throw std::invalid_argument("Error: value must be in range [-100, 100]!");
    }
}

// === Задание 1: конструктор, деструктор, print, set, get
//Конструктор
DynamicArray::DynamicArray(std::size_t sz) : data(nullptr), size(sz) {
    if (size > 0) {
        try {
            //Выделение памяти
            data = new int[size]();
        } catch (const std::bad_alloc&) {
            throw;
        }
    }
}
//Деструктор
DynamicArray::~DynamicArray() {
    delete[] data;
}
//Print
void DynamicArray::print() const {
    std::cout << "[ ";

    for (std::size_t i = 0; i < size; ++i) {
        std::cout << data[i];

        if (i + 1 < size) {
            std::cout << ", ";
        }
    }

    std::cout << " ]\n";
}
//Set
void DynamicArray::set(std::size_t index, int value) {
    checkIndex(index);
    checkValue(value);
    
    data[index] = value;
}
//Get
int DynamicArray::get(std::size_t index) const {
    checkIndex(index);
    
    return data[index];
}

// === Задание 2: конструктор копирования

DynamicArray::DynamicArray(const DynamicArray& other) : data(nullptr), size(other.size) {
    if (size > 0) {
        try {
            data = new int[size];
            std::copy(other.data, other.data + size, data);
        } catch (const std::bad_alloc&) {
            throw;
        }
    }
}

// === Задание 3: добавление значения в конец

void DynamicArray::add(int value) {
    checkValue(value);
    
    try {
        int* newData = new int[size + 1];
        
        if (size > 0) {
            std::copy(data, data + size, newData);
        }
        
        newData[size] = value;
        
        delete[] data;
        data = newData;
        ++size;
    } catch (const std::bad_alloc&) {
        throw;
    }
}

// === Задание 4: сложение и вычитание массивов ===
//Сложение
void DynamicArray::add(const DynamicArray& other) {
    for (std::size_t i = 0; i < size; ++i) {
        int otherValue = 0;
        
        if (i < other.size) {
            otherValue = other.data[i];
        }
        
        // Проверяем результат операции на выход из диапазона
        int result = data[i] + otherValue;
        if (result < -100 || result > 100) {
            throw std::invalid_argument("Error: result of addition is out of range [-100, 100]!");
        }
        
        data[i] = result;
    }
}
//Вычитание
void DynamicArray::subtract(const DynamicArray& other) {
    for (std::size_t i = 0; i < size; ++i) {
        int otherValue = 0;
        
        if (i < other.size) {
            otherValue = other.data[i];
        }
        
        // Проверяем результат операции на выход из диапазона
        int result = data[i] - otherValue;
        if (result < -100 || result > 100) {
            throw std::invalid_argument("Error: result of subtraction is out of range [-100, 100]!");
        }
        
        data[i] = result;
    }
}

std::size_t DynamicArray::getSize() const {
    return size;
}