#include <iostream>
#include <vector>

class Array {
private:
    std::vector<int> data;
public:
    Array();
    Array(size_t n);
    Array(const Array& other);
    ~Array();

    void input();
    void print() const;
    Array intersect(const Array& other) const;
    Array operator&(const Array& other) const;
};
