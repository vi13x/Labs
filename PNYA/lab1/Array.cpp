#include "Array.h"

// --- Конструкторы и деструктор ---
Array::Array() : data(nullptr), size(0) {}

Array::Array(size_t n) : size(n) {
    data = new int[size];
    for(size_t i = 0; i < size; ++i) data[i] = 0;
}

Array::Array(const Array& other) : size(other.size) {
    data = new int[size];
    for(size_t i = 0; i < size; ++i) data[i] = other.data[i];
}

Array::~Array() {
    delete[] data;
}

// --- Методы ---
void Array::input() {
    std::cin >> size;
    delete[] data;
    data = new int[size];
    for(size_t i = 0; i < size; ++i) std::cin >> data[i];
}

void Array::print() const {
    for(size_t i = 0; i < size; ++i) {
        std::cout << data[i];
        if(i + 1 < size) std::cout << ' ';
    }
    std::cout << '\n';
}

// --- Пересечение массивов ---
Array Array::intersect(const Array& other) const {
    size_t max_size = (size < other.size) ? size : other.size;
    Array result(max_size);
    size_t count = 0;

    for(size_t i = 0; i < size; ++i) {
        int val = data[i];
        bool in_other = false;
        for(size_t j = 0; j < other.size; ++j) {
            if(val == other.data[j]) {
                in_other = true;
                break;
            }
        }
        if(in_other) {
            bool already = false;
            for(size_t k = 0; k < count; ++k) {
                if(result.data[k] == val) {
                    already = true;
                    break;
                }
            }
            if(!already) result.data[count++] = val;
        }
    }

    Array final_result(count);
    for(size_t i = 0; i < count; ++i) final_result.data[i] = result.data[i];

    return final_result;
}

// --- Перегрузка оператора & ---
Array Array::operator&(const Array& other) const {
    return this->intersect(other);
}