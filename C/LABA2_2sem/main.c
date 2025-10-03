#include <stdio.h>
#include <stdlib.h>
#include "windows.h"
#include "function.h"

int main(int argc, char *argv[]) {
    SetConsoleOutputCP(CP_UTF8);

    if (argc != 2) {
        printf("Ошибка: укажите имя файла в командной строке.\n");
        return 1;}

    char *filename = argv[1];
    FILE *file = fopen(filename, "w+");
    if (!file) {
        printf("Ошибка открытия файла\n");
        return 1;}
    writeTextFile(file);
    readTextFile(file);
    int target;
    printf("Введите число для поиска: ");
    target = inputInteger();
    printf("Число %d встречается %d раз(а) в файле.\n", target, countOccurrences(file, target));
    int k;
    printf("Введите значение k для циклического сдвига вправо: ");
    k = inputInteger();
    shiftByK(file, k);
    printf("Файл после сдвига:\n");
    readTextFile(file);
    fclose(file);
    system("pause");
    return 0;
}
