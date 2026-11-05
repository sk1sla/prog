#include "DynamicArray.h"
#include <iostream>
#include <string>

int main() {
    // часть 1 базовые методы
    std::cout << "--- Part 1 ---\n";

    DynamicArray<int> a(3);
    a.set(0, 1); a.set(1, 2); a.set(2, 3);
    std::cout << "a = " << a << ", a.get(1) = " << a.get(1)
              << ", size = " << a.getSize() << "\n";

    a.add(4);
    std::cout << "a.add(4) -> " << a << "\n";

    DynamicArray<int> b(3);
    b.set(0, 10); b.set(1, 20); b.set(2, 30);
    a.add(b);
    std::cout << "a.add(b) -> " << a << "\n";

    a.subtract(b);
    std::cout << "a.subtract(b) -> " << a << "\n";

    DynamicArray<int> c(4), d(4);
    for (int i = 0; i < 4; ++i) { c.set(i, (i + 1) * 2); d.set(i, i + 1); }
    std::cout << "c = " << c << ", d = " << d << "\n";
    std::cout << "distance(c, d) = " << c.distance(d) << "\n";

    // часть 2 исключения
    std::cout << "\n--- Part 2 ---\n";

    try { a.get(100); }
    catch (const std::out_of_range& e) { std::cerr << "out_of_range: " << e.what() << "\n"; }

    try { a.set(0, 200); }
    catch (const std::invalid_argument& e) { std::cerr << "invalid_argument: " << e.what() << "\n"; }

    try {
        DynamicArray<int> x(2), y(1);
        x.set(0, 90); x.set(1, 90); y.set(0, 50);
        x.add(y);
    } catch (const std::invalid_argument& e) {
        std::cerr << "invalid_argument: " << e.what() << "\n";
    }

    try {
        DynamicArray<int> p(2), q(3);
        p.distance(q);
    } catch (const std::invalid_argument& e) {
        std::cerr << "invalid_argument: " << e.what() << "\n";
    }

    // часть 3 шаблоны
    std::cout << "\n--- Part 3 ---\n";

    DynamicArray<std::string> s(2);
    s[0] = "Hello"; s[1] = "World";
    std::cout << "string array: " << s << "\n";

    try {
        DynamicArray<std::string> s2(2);
        s.distance(s2);
    } catch (const std::bad_typeid& e) {
        std::cerr << "bad_typeid: " << e.what() << "\n";
    }

    // часть 4 операторы
    std::cout << "\n--- Part 4 ---\n";

    DynamicArray<int> e(3);
    e[0] = 10; e[1] = 20; e[2] = 30;
    std::cout << "e = " << e << ", e[1] = " << e[1] << "\n";

    DynamicArray<int> f(3);
    f[0] = 10; f[1] = 20; f[2] = 30;
    std::cout << "e == f: " << (e == f) << ", e != f: " << (e != f) << "\n";

    DynamicArray<int> g(2);
    g[0] = 5; g[1] = 5;
    e += g;  std::cout << "e += g: " << e << "\n";
    e -= g;  std::cout << "e -= g: " << e << "\n";
    e += 1;  std::cout << "e += 1: " << e << "\n";
    e -= 2;  std::cout << "e -= 2: " << e << "\n";

    std::cout << "range-for: ";
    for (const auto& v : e) std::cout << v << " ";
    std::cout << "\n";
    for (auto& v : e) v = 0;
    std::cout << "after zeroing: " << e << "\n";

    // часть 5 правило пяти
    std::cout << "\n--- Part 5 ---\n";

    DynamicArray<int> src(3);
    src[0] = 1; src[1] = 2; src[2] = 3;
    std::cout << "src = " << src << "\n";

    DynamicArray<int> copy1(src);
    std::cout << "copy1(src) = " << copy1 << "\n";

    DynamicArray<int> copy2;
    copy2 = src;
    std::cout << "copy2 = src: " << copy2 << "\n";

    DynamicArray<int> moved1(std::move(src));
    std::cout << "moved1(move src) = " << moved1
              << ", src.size = " << src.getSize() << "\n";

    DynamicArray<int> moved2;
    moved2 = std::move(moved1);
    std::cout << "moved2 = move moved1: " << moved2
              << ", moved1.size = " << moved1.getSize() << "\n";

    copy1 = copy1;
    std::cout << "copy1 after self-assign: " << copy1 << "\n";

    src.add(42);
    std::cout << "src after move + add(42): " << src << "\n";

    return 0;
}