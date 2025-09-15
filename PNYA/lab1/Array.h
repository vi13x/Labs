#pragma once
#include <iostream>
#include "windows.h"
using namespace std;

class Array {
private:
    int* data;
    int size;
public:
    Array();
    Array(int n);
    Array(const Array& other);
    ~Array();

    void input();
    void output() const;
    Array intersect(const Array& other) const;
};
