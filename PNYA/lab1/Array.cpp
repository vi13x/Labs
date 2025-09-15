#include "Array.h"


Array::Array() {
    size = 0;
    data = nullptr;
}


Array::Array(int n) {
    size = n;
    data = new int[size];
    for (int i = 0; i < size; i++) data[i] = 0;
}


Array::Array(const Array& other) {
    size = other.size;
    data = new int[size];
    for (int i = 0; i < size; i++) data[i] = other.data[i];
}


Array::~Array() {
    delete[] data;
}


void Array::input() {
    cout << "Введите размер массива: ";
    cin >> size;
    delete[] data;
    data = new int[size];
    cout << "Введите элементы массива:\n";
    for (int i = 0; i < size; i++) cin >> data[i];
}


void Array::output() const {
    cout << "Массив: ";
    for (int i = 0; i < size; i++) cout << data[i] << " ";
    cout << endl;
}


Array Array::intersect(const Array& other) const {
    Array result;
    int maxSize = (size < other.size ? size : other.size);
    result.size = 0;
    result.data = new int[maxSize];

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < other.size; j++) {
            if (data[i] == other.data[j]) {
                bool exists = false;
                for (int k = 0; k < result.size; k++) {
                    if (result.data[k] == data[i]) {
                        exists = true;
                        break;
                    }
                }
                if (!exists) {
                    result.data[result.size] = data[i];
                    result.size++;
                }
            }
        }
    }
    return result;
}
