#include "MyString.h"
#include <cstring>

// --- Конструкторы ---
MyString::MyString() : data(nullptr), length(0) {
    data = new char[1];
    data[0] = '\0';
}

MyString::MyString(const char* str) {
    if (!str) {
        length = 0;
        data = new char[1];
        data[0] = '\0';
    } else {
        length = std::strlen(str);
        data = new char[length + 1];
        std::strcpy(data, str);
    }
}

MyString::MyString(const MyString& other) : length(other.length) {
    data = new char[length + 1];
    std::strcpy(data, other.data);
}

// --- Деструктор ---
MyString::~MyString() {
    delete[] data;
}

// --- Присваивание ---
MyString& MyString::operator=(const MyString& other) {
    if (this != &other) {
        delete[] data;
        length = other.length;
        data = new char[length + 1];
        std::strcpy(data, other.data);
    }
    return *this;
}

// --- Индексация ---
char& MyString::operator[](int index) { return data[index]; }
const char& MyString::operator[](int index) const { return data[index]; }

// --- Подстрока ---
MyString MyString::operator()(int start, int len) const {
    if (start < 0 || start >= length || len <= 0) return MyString("");

    if (start + len > length) len = length - start;

    char* buffer = new char[len + 1];
    std::strncpy(buffer, data + start, len);
    buffer[len] = '\0';
    MyString result(buffer);
    delete[] buffer;
    return result;
}

// --- Сравнения ---
bool MyString::operator>(const MyString& other) const {
    return length > other.length;
}
bool MyString::operator<(const MyString& other) const {
    return length < other.length;
}
bool MyString::operator==(const MyString& other) const {
    if (length != other.length) return false;
    return std::strcmp(data, other.data) == 0;
}

// --- Конкатенация ---
MyString MyString::operator+(const MyString& other) const {
    char* buffer = new char[length + other.length + 1];
    std::strcpy(buffer, data);
    std::strcat(buffer, other.data);
    MyString result(buffer);
    delete[] buffer;
    return result;
}

MyString MyString::operator+(const char* str) const {
    int addLen = std::strlen(str);
    char* buffer = new char[length + addLen + 1];
    std::strcpy(buffer, data);
    std::strcat(buffer, str);
    MyString result(buffer);
    delete[] buffer;
    return result;
}

MyString MyString::operator+(char c) const {
    char* buffer = new char[length + 2];
    std::strcpy(buffer, data);
    buffer[length] = c;
    buffer[length + 1] = '\0';
    MyString result(buffer);
    delete[] buffer;
    return result;
}

MyString operator+(const char* lhs, const MyString& rhs) {
    int lhsLen = std::strlen(lhs);
    char* buffer = new char[lhsLen + rhs.length + 1];
    std::strcpy(buffer, lhs);
    std::strcat(buffer, rhs.data);
    MyString result(buffer);
    delete[] buffer;
    return result;
}


MyString operator+(char lhs, const MyString& rhs) {
    char* buffer = new char[rhs.length + 2];
    buffer[0] = lhs;
    std::strcpy(buffer + 1, rhs.data);
    MyString result(buffer);
    delete[] buffer;
    return result;
}


// --- Оператор += ---
MyString& MyString::operator+=(const MyString& other) {
    *this = *this + other;
    return *this;
}

// --- ++ и -- ---
MyString& MyString::operator++() {
    for (int i = 0; i < length; i++) data[i]++;
    return *this;
}

MyString MyString::operator++(int) {
    MyString temp(*this);
    ++(*this);
    return temp;
}

MyString& MyString::operator--() {
    for (int i = 0; i < length; i++) data[i]--;
    return *this;
}

MyString MyString::operator--(int) {
    MyString temp(*this);
    --(*this);
    return temp;
}

// --- Ввод/вывод ---
std::ostream& operator<<(std::ostream& os, const MyString& str) {
    os << str.data;
    return os;
}

std::istream& operator>>(std::istream& is, MyString& str) {
    char buffer[80];
    is >> buffer;
    str = MyString(buffer);
    return is;
}
