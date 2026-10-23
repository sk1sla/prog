#include "DynamicArray.h"
#include <iostream>
#include <string>

int main() {
    std::cout << "=== Для чисел ===\n";
    
    try {
        DynamicArray<int> arr1(3);
        arr1.set(0, 10);
        arr1.set(1, 20);
        arr1.set(2, 30);
        std::cout << "arr1: " << arr1 << "\n";

        DynamicArray<int> arr2(3);
        arr2.set(0, 1);
        arr2.set(1, 2);
        arr2.set(2, 3);
        std::cout << "arr2: " << arr2 << "\n";

        // Демонстрация distance для чисел
        std::cout << "Distance between arr1 and arr2: " << arr1.distance(arr2) << "\n\n";

        // Демонстрация проверки значения
        std::cout << "Попытка установить значение 150 (вне диапазона):\n";
        try {
            arr1.set(0, 150);
        } catch (const std::invalid_argument& e) {
            std::cerr << "Перехвачено: " << e.what() << "\n";
        }

        // Демонстрация проверки индекса
        std::cout << "Попытка получить элемент по индексу 10(его нету):\n";
        try {
            arr1.get(10);
        } catch (const std::out_of_range& e) {
            std::cerr << "Перехвачено: " << e.what() << "\n";
        }

    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << "\n";
    }

    std::cout << "\n=== 2. Для строк ===\n";
    
    try {
        DynamicArray<std::string> strArr1(2);
        strArr1.set(0, "Hello");
        strArr1.set(1, "World");
        std::cout << "strArr1: " << strArr1 << "\n";

        DynamicArray<std::string> strArr2(2);
        strArr2.set(0, "C++");
        strArr2.set(1, "Templates");
        std::cout << "strArr2: " << strArr2 << "\n";

        // Сложение строк работает, и проверка диапазона не применяется (это же строки а не числа)
        strArr1.add(strArr2);
        std::cout << "strArr1 после сложения со strArr2: " << strArr1 << "\n";

        // Демонстрация distance для нечислового типа
        std::cout << "Попытка вычислить distance для строк:\n";
        try {
            strArr1.distance(strArr2);
        } catch (const std::bad_typeid&) {
            std::cerr << "Перехвачено: std::bad_typeid (distance только для арифметических типов)\n";
        }

        // Демонстрация distance для разных размеров
        std::cout << "Попытка вычислить distance для массивов разного размера:\n";
        DynamicArray<int> smallArr(2);
        DynamicArray<int> largeArr(3);
        try {
            smallArr.distance(largeArr);
        } catch (const std::invalid_argument& e) {
            std::cerr << "Перехвачено: " << e.what() << "\n";
        }

    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << "\n";
    }

    std::cout << "\n=== Нехватка памяти ===\n";
    try {
        // Роняем прогу (около 400ГБ оперативы)
        DynamicArray<int> hugeArr(100000000000000UL);
    } catch (const std::bad_alloc& e) {
        std::cerr << "Перехвачено: " << e.what() << "\n";
    }

    return 0;
}