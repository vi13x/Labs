#include <iostream>

class Array {
private:
    int* data;
    size_t size;

public:
    // Конструкторы и деструктор
    Array();                    // по умолчанию
    Array(size_t n);            // с размером
    Array(const Array& other);  // копирования
    ~Array();                   // деструктор

    // Методы
    void input();               // ввод массива
    void print() const;         // вывод массива
    Array intersect(const Array& other) const;  // пересечение массивов

    // Перегрузка оператора &
    Array operator&(const Array& other) const;
};