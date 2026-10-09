#pragma once

#include <cstddef>

class DynamicArray {
private:
    int* data;              // Указатель на динамический массив
    std::size_t size;       // Размер массива

    // Вспомогательные методы для проверок
    bool isIndexValid(std::size_t index) const;
    bool isValueValid(int value) const;

public:
    // === Задание 1 ===

    // Конструктор по размеру массива
    explicit DynamicArray(std::size_t sz);

    // Деструктор
    ~DynamicArray();

    void print() const;

    // Сеттер с проверками:
    // 1) индекс не выходит за границы
    // 2) значение входит в диапазон [-100, 100]
    void set(std::size_t index, int value);

    int get(std::size_t index) const;

    // === Задание 2 ===

    DynamicArray(const DynamicArray& other);

    // === Задание 3 ===

    void add(int value);

    // === Задание 4 ===

    void add(const DynamicArray& other);

    void subtract(const DynamicArray& other);

    std::size_t getSize() const;
};