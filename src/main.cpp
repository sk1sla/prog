#include "DynamicArray.h"
#include <iostream>
#include <string>

int main() {
    std::cout << "=== 1. Check operator[] ===\n";
    DynamicArray<int> arr1(3);
    arr1[0] = 10; // Вызывает Proxy::operator=, который внутри вызывает set() с проверкой
    arr1[1] = 20;
    arr1[2] = 30;
    std::cout << "arr1: " << arr1 << "\n";
    
    std::cout << "Reading through operator[]: arr1[1] = " << arr1[1] << "\n";

    try {
        std::cout << "Try write 150 in arr1[0] (out of range):\n";
        arr1[0] = 150; // Должно выбросить исключение благодаря проверке в set()
    } catch (const std::invalid_argument& e) {
        std::cerr << "Recaptured: " << e.what() << "\n";
    }

    try {
        std::cout << "Try request by index 10:\n";
        arr1[10] = 5;
    } catch (const std::out_of_range& e) {
        std::cerr << "Recaptured: " << e.what() << "\n";
    }

    std::cout << "\n=== 2. Try operator== и operator!= ===\n";
    DynamicArray<int> arr2(3);
    arr2[0] = 10; arr2[1] = 20; arr2[2] = 30;
    
    DynamicArray<int> arr3(2);
    arr3[0] = 10; arr3[1] = 20;

    std::cout << "arr1 == arr2: " << (arr1 == arr2 ? "true" : "false") << "\n";
    std::cout << "arr1 != arr3: " << (arr1 != arr3 ? "true" : "false") << "\n";

    std::cout << "\n=== 3. Try operator+= и operator-= ===\n";
    DynamicArray<int> arr4(3);
    arr4[0] = 10; arr4[1] = 20; arr4[2] = 30;
    
    DynamicArray<int> arr5(2);
    arr5[0] = 5; arr5[1] = 5;
    
    arr4 += arr5; // arr4 станет [15, 25, 30] (недостающий элемент arr5 считается 0)
    std::cout << "arr4 += arr5: " << arr4 << "\n";
    
    arr4 -= 5; // Вычитаем скаляр из всех элементов
    std::cout << "arr4 -= 5: " << arr4 << "\n";

    std::cout << "\n=== 4. Checking iterators (range-based for) ===\n";
    DynamicArray<std::string> strArr(3);
    strArr[0] = "Hello";
    strArr[1] = "World";
    strArr[2] = "C++";
    
    std::cout << "Elements strArr through range-based for (reading):\n";
    for (const auto& x : strArr) {
        std::cout << x << " ";
    }
    std::cout << "\n";

    // Изменение элементов через неконстантный итератор (ссылка)
    for (auto& x : strArr) {
        x = x + "!";
    }
    std::cout << "strArr after chenges: " << strArr << "\n";

    return 0;
}