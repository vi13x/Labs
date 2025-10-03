#include <stdio.h>
#include "function.h"

int main() {
    SetConsoleOutputCP(CP_UTF8);
    int choice;
    do {
        printf("Меню:\n1 - Задание 1 (Очередь)\n2 - Задание 2 (Дек)\n0 - Выход\nВведите ваш выбор: ");
        if (scanf("%d", &choice) != 1) {
            printf("Ошибка ввода. Попробуйте снова.\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            continue;
        }
        while (getchar() != '\n');

        switch (choice) {
            case 1:
                createQueue();
                break;
            case 2:
                createDeck();
                break;
            case 0:
                printf("Выход.\n");
                break;
            default:
                printf("Неверный выбор.\n");
        }

        if (choice != 0) {
            printf("\nНажмите Enter для продолжения...");
            while (getchar() != '\n');
        }

    } while (choice != 0);

    return 0;
}
