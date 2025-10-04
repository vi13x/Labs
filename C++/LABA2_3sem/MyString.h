#include <iostream>
#include "windows.h"
class MyString {
private:
    char* data;
    int length;

public:
    // Конструкторы
    MyString();                     // по умолчанию
    MyString(const char* str);
    MyString(const MyString& other);// копирование

    // Деструктор
    ~MyString();

    // Оператор присваивания
    MyString& operator=(const MyString& other);

    // Доступ к символу
    char& operator[](int index);
    const char& operator[](int index) const;

    // Подстрока
    MyString operator()(int start, int len) const;

    // Сравнения
    bool operator>(const MyString& other) const;
    bool operator<(const MyString& other) const;
    bool operator==(const MyString& other) const;

    // Конкатенация
    MyString operator+(const MyString& other) const;
    MyString operator+(const char* str) const;
    MyString operator+(char c) const;

    // Друзья для обратного порядка
    friend MyString operator+(const char* lhs, const MyString& rhs);
    friend MyString operator+(char lhs, const MyString& rhs);

    // Оператор +=
    MyString& operator+=(const MyString& other);

    // Префиксные и постфиксные ++/--
    MyString& operator++();   // ++obj
    MyString operator++(int); // obj++
    MyString& operator--();   // --obj
    MyString operator--(int); // obj--

    // Потоковый ввод/вывод
    friend std::ostream& operator<<(std::ostream& os, const MyString& str);
    friend std::istream& operator>>(std::istream& is, MyString& str);

    // Вспомогательное
    int size() const { return length; }
};
