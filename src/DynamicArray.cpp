#include "DynamicArray.h"

#include <algorithm>
#include <iostream>

// === Приватные вспомогательные методы ===

bool DynamicArray::isIndexValid(std::size_t index) const {
    if (index >= size) {
        std::cerr << "Error: index out of array bounds!\n";
        return false;
    }

    return true;
}

bool DynamicArray::isValueValid(int value) const {
    if (value < -100 || value > 100) {
        std::cerr << "Error: value must be in range [-100, 100]!\n";
        return false;
    }

    return true;
}

// === Задание 1: конструктор, деструктор, print, set, get ===

DynamicArray::DynamicArray(std::size_t sz) : data(nullptr), size(sz) {
    if (size > 0) {
        // new int[size]() выделяет память и инициализирует элементы нулями
        data = new int[size]();
    }
}

DynamicArray::~DynamicArray() {
    delete[] data;
}

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

void DynamicArray::set(std::size_t index, int value) {
    if (!isIndexValid(index)) {
        return;
    }

    if (!isValueValid(value)) {
        return;
    }

    data[index] = value;
}

int DynamicArray::get(std::size_t index) const {
    if (!isIndexValid(index)) {
        return 0;
    }

    return data[index];
}

// === Задание 2: конструктор копирования ===

DynamicArray::DynamicArray(const DynamicArray& other) : data(nullptr), size(other.size) {
    if (size > 0) {
        data = new int[size];
        std::copy(other.data, other.data + size, data);
    }
}

// === Задание 3: добавление значения в конец ===

void DynamicArray::add(int value) {
    if (!isValueValid(value)) {
        return;
    }

    int* newData = new int[size + 1];

    if (size > 0) {
        std::copy(data, data + size, newData);
    }

    newData[size] = value;

    delete[] data;
    data = newData;
    ++size;
}

// === Задание 4: сложение и вычитание массивов ===

void DynamicArray::add(const DynamicArray& other) {
    for (std::size_t i = 0; i < size; ++i) {
        int otherValue = 0;

        if (i < other.size) {
            otherValue = other.data[i];
        }

        data[i] += otherValue;
    }
}

void DynamicArray::subtract(const DynamicArray& other) {
    for (std::size_t i = 0; i < size; ++i) {
        int otherValue = 0;

        if (i < other.size) {
            otherValue = other.data[i];
        }

        data[i] -= otherValue;
    }
}

std::size_t DynamicArray::getSize() const {
    return size;
}