#include "DynamicArray.h"

#include <iostream>
#include <stdexcept>

int main() {
    std::cout << "Constructor, set, get, print ===\n";

    try {
        DynamicArray arr1(5);

        arr1.set(0, 10);
        arr1.set(1, -50);
        arr1.set(2, 100);

        std::cout << "arr1: ";
        arr1.print();

        std::cout << "arr1.get(1) = " << arr1.get(1) << "\n\n";

        std::cout << "--- Checking invalid index ---\n";
        std::cout << "Trying arr1.get(10):\n";
        try {
            int invalidValue = arr1.get(10);
            std::cout << "Returned value: " << invalidValue << "\n";
        } catch (const std::out_of_range& e) {
            std::cerr << "Caught exception: " << e.what() << "\n";
        }
        std::cout << "\n";

        std::cout << "--- Checking invalid value ---\n";
        std::cout << "Trying arr1.set(0, 150):\n";
        try {
            arr1.set(0, 150);
        } catch (const std::invalid_argument& e) {
            std::cerr << "Caught exception: " << e.what() << "\n";
        }
        std::cout << "arr1 after invalid set: ";
        arr1.print();
        std::cout << "\n";

        std::cout << "=== Copy constructor ===\n";

        DynamicArray arr2(arr1);

        arr2.set(0, 99);

        std::cout << "arr1 original: ";
        arr1.print();

        std::cout << "arr2 copy:     ";
        arr2.print();
        std::cout << "\n";

        std::cout << "=== Add value to the end ===\n";

        arr1.add(42);

        std::cout << "arr1 after add(42): ";
        arr1.print();

        std::cout << "arr1 size: " << arr1.getSize() << "\n\n";

        std::cout << "=== Array addition and subtraction ===\n";

        DynamicArray arrA(4);
        arrA.set(0, 10);
        arrA.set(1, 20);
        arrA.set(2, 30);
        arrA.set(3, 40);

        DynamicArray arrB(2);
        arrB.set(0, 5);
        arrB.set(1, 5);

        std::cout << "arrA: ";
        arrA.print();

        std::cout << "arrB: ";
        arrB.print();

        arrA.add(arrB);

        std::cout << "arrA after arrA.add(arrB): ";
        arrA.print();

        arrA.subtract(arrB);

        std::cout << "arrA after arrA.subtract(arrB): ";
        arrA.print();
        
    } catch (const std::bad_alloc& e) {
        std::cerr << "Memory allocation error: " << e.what() << "\n";
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "Unexpected error: " << e.what() << "\n";
        return 1;
    }

    // Демонстрация всех трех типов исключений
    std::cout << "\n=== Demonstrating all three exception types ===\n";
    
    // 1. std::out_of_range
    std::cout << "\n1. Testing std::out_of_range:\n";
    try {
        DynamicArray arr(3);
        arr.set(0, 10);
        int val = arr.get(5);  // Выход за границы
    } catch (const std::out_of_range& e) {
        std::cerr << "Caught std::out_of_range: " << e.what() << "\n";
    }
    
    // 2. std::invalid_argument
    std::cout << "\n2. Testing std::invalid_argument:\n";
    try {
        DynamicArray arr(3);
        arr.set(0, 200);  // Значение вне диапазона
    } catch (const std::invalid_argument& e) {
        std::cerr << "Caught std::invalid_argument: " << e.what() << "\n";
    }
    
    // 3. std::bad_alloc
    std::cout << "\n3. Testing std::bad_alloc structure:\n";
    try {
        DynamicArray arr(100000000000000UL);  // Падаем при попытке выделения 400ТБ оперативы на гнилом ноуте
    } catch (const std::bad_alloc& e) {
        std::cerr << "Caught std::bad_alloc: " << e.what() << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Other exception: " << e.what() << "\n";
    }

    return 0;
}