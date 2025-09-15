#include "Array.h"

int main() {
    SetConsoleOutputCP(CP_UTF8);
    Array a, b, c;
    int choice;

    do {
        cout << "\n===== МЕНЮ =====\n";
        cout << "1. Ввод первого массива\n";
        cout << "2. Ввод второго массива\n";
        cout << "3. Вывод первого массива\n";
        cout << "4. Вывод второго массива\n";
        cout << "5. Пересечение массивов\n";
        cout << "0. Выход\n";
        cout << "Ваш выбор: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Первый массив:\n";
                a.input();
                break;
            case 2:
                cout << "Второй массив:\n";
                b.input();
                break;
            case 3:
                cout << "Первый ";
                a.output();
                break;
            case 4:
                cout << "Второй ";
                b.output();
                break;
            case 5:
                c = a.intersect(b);
                cout << "Пересечение ";
                c.output();
                break;
            case 0:
                cout << "Выход...\n";
                break;
            default:
                cout << "Неверный выбор!\n";
        }
    } while (choice != 0);

    return 0;
}
