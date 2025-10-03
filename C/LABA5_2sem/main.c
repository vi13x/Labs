#include "function.h"
int main() {
    SetConsoleOutputCP(CP_UTF8);
    int choice;

    while (1) {
        printf("\nВыберите задание:\n");
        printf("0 - Выход\n");
        printf("1 - Найти минимальный нечетный элемент стека\n");
        printf("2 - Объединение двух стеков в отсортированный\n");
        printf("Выбор: ");

        if (!inputInt("", &choice, 0, 2)) {
            printf("Ошибка ввода!\n");
            continue;
        }

        switch (choice) {
            case 0: return 0;
            case 1: minStackel(); break;
            case 2: combinationStack(); break;
            default: printf("Неверный выбор!\n");
        }
    }
}
