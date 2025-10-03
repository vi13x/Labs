#include <stdio.h>
#include <stdlib.h>
#include "windows.h"
#include "function.h"

int inputInteger() {
    int var, c;
    while (1) {
        while (scanf("%d", &var) != 1) {
            printf("ОШИБКА...введите корректное значение: ");
            while ((c = getchar()) != '\n' && c != EOF);
        }
        if ((c = getchar()) != '\n' && c != EOF && c != ' ') {
            printf("ОШИБКА...введите корректное значение: ");
            while ((c = getchar()) != '\n' && c != EOF);
        } else
            return var;
    }
}

void writeTextFile(FILE *file) {
    int num;
    printf("Введите числа (0 для завершения ввода):\n");
    while (1) {
       num = inputInteger();
        if (num == 0) break;
        fprintf(file, "%d ", num);
    }
    fprintf(file, "\n");
    fflush(file);
}

void readTextFile(FILE *file) {
    rewind(file);
    int num;
    printf("Содержимое файла:\n");
    while (fscanf(file, "%d", &num) == 1) {
        printf("%d ", num);
    }
    printf("\n");
    rewind(file);
}

int countOccurrences(FILE *file, int target) {
    rewind(file);
    int num, count = 0;
    while (fscanf(file, "%d", &num) == 1) {
        if (num == target) {
            count++;
        }
    }
    rewind(file);
    return count;
}

void shiftByK(FILE *file, int k) {
    rewind(file);
    int *numbers = NULL;
    int count = 0;
    int num;

    while (fscanf(file, "%d", &num) == 1) {
        numbers = (int *)realloc(numbers, (count + 1) * sizeof(int));
        if (!numbers) {
            printf("Ошибка выделения памяти\n");
            return;
        }
        numbers[count] = num;
        count++;
    }

    if (count == 0) {
        printf("Файл пуст, сдвиг невозможен.\n");
        free(numbers);
        rewind(file);
        return;
    }
    k = (k % count + count) % count;
    int *shifted = (int *)malloc(count * sizeof(int));
    if (!shifted) {
        printf("Ошибка выделения памяти\n");
        free(numbers);
        return;
    }
    for (int i = 0; i < count; i++) {
        shifted[(i + k) % count] = numbers[i];
    }
    rewind(file);
    for (int i = 0; i < count; i++) {
        fprintf(file, "%d ", shifted[i]);
    }
    fprintf(file, "\n");
    fflush(file);
    rewind(file);
    free(numbers);
    free(shifted);
}
