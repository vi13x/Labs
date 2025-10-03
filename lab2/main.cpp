#include <iostream>
#include "MyString.h"

int main() {
    SetConsoleOutputCP(CP_UTF8);

    MyString str1, str2;

    std::cout << "Введите первую строку: ";
    std::cin >> str1;
    std::cout << "Введите вторую строку: ";
    std::cin >> str2;

    std::cout << "\nПервая строка: " << str1 << std::endl;
    std::cout << "Вторая строка: " << str2 << std::endl;

    std::cout << "\nСравнение строк:" << std::endl;
    if (str1 > str2)
        std::cout << "Первая строка длиннее." << std::endl;
    else if (str1 < str2)
        std::cout << "Вторая строка длиннее." << std::endl;
    else if (str1 == str2)
        std::cout << "Строки равны." << std::endl;

    std::cout << "\nОбъединим строки:" << std::endl;
    MyString str3 = str1 + str2;
    std::cout << "str3 = " << str3 << std::endl;

    std::cout << "\nСоздадим строку по умолчанию (Hello):" << std::endl;
    MyString str("Hello");
    std::cout << str << std::endl;

    std::cout << "\nВычислим выражение: result = str(1,4) + str3[1] + str1[0]" << std::endl;
    MyString result = str(1, 4) + str3[1] + str1[0];
    std::cout << "result = " << result << std::endl;

    std::cout << "\nИнкремент и декремент строки:" << std::endl;
    ++str;
    std::cout << "После ++str: " << str << std::endl;
    str--;
    std::cout << "После str--: " << str << std::endl;

    std::cout << "\nПрисвоим str1 = str:" << std::endl;
    str1 = str;
    std::cout << str1 << std::endl;

    return 0;
}
