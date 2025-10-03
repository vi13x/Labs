#include <stdio.h>
#include <stdlib.h>
#include "windows.h"
#include "function.h"


int main(int argc, char *argv[]) {
    SetConsoleOutputCP(CP_UTF8);

    if (argc != 2) {
        printf("Ошибка: укажите имя файла в командной строке.\n");
        return 1;
    }

    char *filename = argv[1];
    FILE *file = fopen(filename, "w+b");
    if (!file) {
        printf("Ошибка открытия файла");
        return 1;
    }
    writeFile(file);
    readFile(file);
    int target;
    printf("Введите число для поиска: ");
    target = inputInteger();
    printf("Число %d встречается %d раз(а)\n", target, counter(file, target));
    printf("Введите число для замены на максимальный элемент: ");
    target = inputInteger();
    replaceMax(file, target);
    readFile(file);
    printf("Сортируем нечетные числа по убыванию...\n");
    oddBubbleSort(file);
    readFile(file);
    fclose(file);

    system("pause");
    return 0;
}
