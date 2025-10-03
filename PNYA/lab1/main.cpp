#include "Array.h"
#include <iostream>

int main() {
    size_t k;
    std::cout << "Enter number of arrays: ";
    std::cin >> k;

    // Создаем массив объектов через конструктор с размером
    Array* arrays = new Array[k]; // можно оставить пустыми, а потом инициализировать через input()

    for (size_t i = 0; i < k; ++i) {
        std::cout << "Enter size and elements for Array " << i + 1 << ":\n";
        arrays[i].input(); // инициализация каждого массива через метод input()
    }

    std::cout << "\nYou entered:\n";
    for (size_t i = 0; i < k; ++i) {
        std::cout << "Array " << i + 1 << ": ";
        arrays[i].print();
    }

    if (k > 0) {
        Array result = arrays[0]; // вызов конструктора копирования
        for (size_t i = 1; i < k; ++i) {
            result = result.intersect (arrays[i]); // пересечение массивов через перегрузку &
        }

        std::cout << "\nIntersection of all arrays:\n";
        result.print();


        result.~Array();
    }

    // Освобождаем память под массив объектов
    delete[] arrays;

    return 0;
}
