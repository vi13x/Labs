#include <stdio.h>
#include <stdlib.h>
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

void writeFile(FILE *file) {
    int num;
    printf("Введите числа (0 для завершения ввода): \n");
    while ((num = inputInteger()) != 0) {
        fwrite(&num, sizeof(int), 1, file);
    }
    fflush(file);
}

void readFile(FILE *file) {
    rewind(file);
    int num;
    printf("Содержимое файла:\n");
    while (fread(&num, sizeof(int), 1, file)) {
        printf("%d ", num);
    }
    printf("\n");
    rewind(file);
}
int counter(FILE *file, int target) {
    rewind(file);
    int num, count = 0;
    while (fread(&num, sizeof(int), 1, file)) {
        if (num == target) count++;
    }
    rewind(file);
    return count;
}

void replaceMax(FILE *file, int target) {
    rewind(file);
    int num, max = INT_MIN;

    while (fread(&num, sizeof(int), 1, file)) {
        if (num > max) max = num;
    }
    printf("Найдено максимальное число %d\n", max);
    if (max == INT_MIN) {
        rewind(file);
        return;
    }

    rewind(file);
    while (fread(&num, sizeof(int), 1, file)) {
        if (num == target) {
            fseek(file, -sizeof(int), 1);
            fwrite(&max, sizeof(int), 1, file);
            fflush(file);
        }
    }
    rewind(file);
}


void oddBubbleSort(FILE *file) {
    rewind(file);

    int *numbers = NULL;
    int count = 0;
    int temp;

    while (1) {
        numbers = (int *)realloc(numbers, (count + 1) * sizeof(int));
        if (!numbers) {
            printf("Ошибка выделения памяти\n");
            return;
        }

        if (fread(&numbers[count], sizeof(int), 1, file) != 1) {
            break;
        }
        count++;
    }

    if (count == 0) {
        printf("Файл пуст, сортировка невозможна.\n");
        free(numbers);
        rewind(file);
        return;
    }

    printf("Прочитано %d чисел из файла.\n", count);

    int *odd_indices = (int *)malloc(count * sizeof(int));
    int *odd_values = (int *)malloc(count * sizeof(int));
    int odd_count = 0;

    if (!odd_indices || !odd_values) {
        printf("Ошибка выделения памяти\n");
        free(numbers);
        free(odd_indices);
        free(odd_values);
        return;
    }

    for (int i = 0; i < count; i++) {
        if (numbers[i] % 2 != 0) {
            odd_indices[odd_count] = i;
            odd_values[odd_count] = numbers[i];
            odd_count++;
        }
    }

    printf("Найдено %d нечетных чисел.\n", odd_count);

    for (int i = 0; i < odd_count - 1; i++) {
        for (int j = 0; j < odd_count - i - 1; j++) {
            if (odd_values[j] < odd_values[j + 1]) {
                temp = odd_values[j];
                odd_values[j] = odd_values[j + 1];
                odd_values[j + 1] = temp;
            }
        }
    }

    printf("Отсортированные нечетные числа: ");
    for (int i = 0; i < odd_count; i++) {
        printf("%d ", odd_values[i]);
    }
    printf("\n");

    for (int i = 0; i < odd_count; i++) {
        numbers[odd_indices[i]] = odd_values[i];
    }

    rewind(file);
    fwrite(numbers, sizeof(int), count, file);
    fflush(file);
    rewind(file);

    free(numbers);
    free(odd_indices);
    free(odd_values);
}
