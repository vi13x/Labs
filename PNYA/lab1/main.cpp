#include "Array.h"
#include <vector>

int main() {
    size_t k;
    std::cout << "How many arrays do you want to input? ";
    std::cin >> k;

    std::vector<Array> arrays(k);

    for (size_t i = 0; i < k; ++i) {
        std::cout << "Enter size and elements of array " << i + 1 << ":\n";
        arrays[i].input();
    }

    std::cout << "You entered:\n";
    for (size_t i = 0; i < k; ++i) {
        std::cout << "Array " << i + 1 << ": ";
        arrays[i].print();
    }

    if (k == 0) return 0;

    Array result = arrays[0];
    for (size_t i = 1; i < k; ++i) {
        result = result & arrays[i];
    }

    std::cout << "Intersection of all arrays:\n";
    result.print();

    return 0;
}
