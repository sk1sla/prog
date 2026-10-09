#include "DynamicArray.h"

#include <iostream>

int main() {
    std::cout << "=== Part 1, Task 1: constructor, set, get, print ===\n";

    DynamicArray arr1(5);

    arr1.set(0, 10);
    arr1.set(1, -50);
    arr1.set(2, 100);

    std::cout << "arr1: ";
    arr1.print();

    std::cout << "arr1.get(1) = " << arr1.get(1) << "\n\n";

    std::cout << "--- Checking invalid index ---\n";
    std::cout << "Trying arr1.get(10):\n";
    int invalidValue = arr1.get(10);
    std::cout << "Returned value: " << invalidValue << "\n\n";

    std::cout << "--- Checking invalid value ---\n";
    std::cout << "Trying arr1.set(0, 150):\n";
    arr1.set(0, 150);
    std::cout << "arr1 after invalid set: ";
    arr1.print();
    std::cout << "\n";

    std::cout << "=== Part 1, Task 2: copy constructor ===\n";

    DynamicArray arr2(arr1);

    arr2.set(0, 99);

    std::cout << "arr1 original: ";
    arr1.print();

    std::cout << "arr2 copy:     ";
    arr2.print();
    std::cout << "\n";

    std::cout << "=== Part 1, Task 3: add value to the end ===\n";

    arr1.add(42);

    std::cout << "arr1 after add(42): ";
    arr1.print();

    std::cout << "arr1 size: " << arr1.getSize() << "\n\n";

    std::cout << "=== Part 1, Task 4: array addition and subtraction ===\n";

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

    return 0;
}