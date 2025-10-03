#include <iostream>
#include "MyString.h"
#include <windows.h>

int main() {
    SetConsoleOutputCP(CP_UTF8);

    //Создаем две строки
    MyString str1, str2;

    //Ввод первых двух строк
    std::cout << "Enter the first string: ";
    std::cin >> str1;
    std::cout << "Enter the second string: ";
    std::cin >> str2;

    //Вывод введенных строк
    std::cout << "\nFirst string: " << str1 << std::endl;
    std::cout << "Second string: " << str2 << std::endl;

    //Сравнение строк по длине
    std::cout << "\nComparing strings:" << std::endl;
    if (str1 > str2)
        std::cout << "The first string is longer." << std::endl;
    else if (str1 < str2)
        std::cout << "The second string is longer." << std::endl;
    else if (str1 == str2)
        std::cout << "The strings are equal." << std::endl;

    //Сложение строк
    std::cout << "\nConcatenating strings:" << std::endl;
    MyString str3 = str1 + str2;
    std::cout << "str3 = " << str3 << std::endl;

    //Создание строки по умолчанию
    std::cout << "\nCreating a default string (PNYAVU):" << std::endl;
    MyString str("PNYAVU");
    std::cout << str << std::endl;

    //Вычисление выражения с подстроками и отдельными символами
    std::cout << "\nComputing expression: result = str(1,4) + str3[1] + str1[0]" << std::endl;
    MyString result = str(1, 4) + str3[1] + str1[0];
    std::cout << "result = " << result << std::endl;

    //Инкремент и декремент строки
    std::cout << "\nIncrement and decrement string:" << std::endl;
    ++str;  // префиксный ++
    std::cout << "After ++str: " << str << std::endl;
    str--;  // постфиксный --
    std::cout << "After str--: " << str << std::endl;

    // Присвоение одной строки другой
    std::cout << "\nAssign str1 = str:" << std::endl;
    str1 = str;
    std::cout << str1 << std::endl;

    return 0;
}
