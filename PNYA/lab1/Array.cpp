#include "Array.h"

Array::Array() : data() {}
Array::Array(size_t n) : data(n) {}
Array::Array(const Array& other) : data(other.data) {}
Array::~Array() {}

void Array::input() {
    size_t n;
    std::cin >> n;
    this->data.resize(n);
    for (size_t i = 0; i < n; ++i) {
        std::cin >> this->data[i];
    }
}

void Array::print() const {
    for (size_t i = 0; i < this->data.size(); ++i) {
        std::cout << this->data[i];
        if (i + 1 < this->data.size()) std::cout << ' ';
    }
    std::cout << '\n';
}

Array Array::intersect(const Array& other) const {
    Array result;
    for (size_t i = 0; i < this->data.size(); ++i) {
        int val = this->data[i];
        bool in_other = false;
        for (size_t j = 0; j < other.data.size(); ++j) {
            if (val == other.data[j]) {
                in_other = true;
                break;
            }
        }
        if (in_other) {
            bool already = false;
            for (int x : result.data) {
                if (x == val) {
                    already = true;
                    break;
                }
            }
            if (!already) result.data.push_back(val);
        }
    }
    return result;
}

Array Array::operator&(const Array& other) const {
    return this->intersect(other);
}
