/*
Лабораторная работа №3. Поля бит. Структуры.
Иванов И.И., 18.03.2025

Задание:
1. Найти остаток от деления на 4 используя битовые поля
2. Работа с динамическим массивом структур животных:
   - Поиск по названию
   - Удаление по количеству особей
   - Меню управления
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "windows.h"

// Битовая структура для задачи 1
typedef struct {
    unsigned int last_two_bits : 2;
} BitField;

// Структура даты для задачи 2
typedef struct {
    char date_str[11]; // DD.MM.YYYY
} Date;

// Структура животного для задачи 2
typedef struct {
    int quantity;
    char* name;
    Date arrival_date;
    float lifespan;
} Animal;

// Прототипы функций
int get_remainder(int num);
void input_animal(Animal *a);
void print_animal(Animal *a);
Animal* find_animals(Animal *arr, int size, const char *name);
int remove_animals(Animal **arr, int size, int quantit);
void flush_input_buffer();

int main() {
    SetConsoleOutputCP(CP_UTF8);
    // Задача 1
    int number;
    printf("Введите целое число: ");
    scanf("%d", &number);
    printf("Остаток от деления на 4: %d\n\n", get_remainder(number));

    // Задача 2
    Animal *zoo = NULL;
    int zoo_size = 0;
    int choice;

    while(1) {
        printf("\nМеню управления зоопарком:\n");
        printf("1. Добавить животное\n");
        printf("2. Показать всех животных\n");
        printf("3. Найти животных по названию\n");
        printf("4. Удалить животных по количеству\n");
        printf("5. Выход\n");
        printf("Выберите действие: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: {
                Animal *temp = realloc(zoo, (zoo_size + 1) * sizeof(Animal));
                if(!temp) {
                    printf("Ошибка выделения памяти!\n");
                    exit(1);
                }
                zoo = temp;
                input_animal(&zoo[zoo_size]);
                zoo_size++;
                break;
            }
            case 2: {
                for(int i = 0; i < zoo_size; i++) {
                    printf("\nЖивотное #%d:\n", i+1);
                    print_animal(&zoo[i]);
                }
                break;
            }
            case 3: {
                char search_name[100];
                printf("Введите название для поиска: ");
                scanf("%99s", search_name);
                Animal *found = find_animals(zoo, zoo_size, search_name);
                if(found) {
                    printf("Найдены животные:\n");
                    while(found < zoo + zoo_size &&
                          strcmp(found->name, search_name) == 0) {
                        print_animal(found);
                        found++;
                    }
                } else {
                    printf("Животные не найдены.\n");
                }
                break;
            }
            case 4: {
                int qty;
                printf("Введите количество для удаления: ");
                scanf("%d", &qty);
                int new_size = remove_animals(&zoo, zoo_size, qty);
                if(new_size != zoo_size) {
                    zoo_size = new_size;
                    printf("Удаление завершено.\n");
                } else {
                    printf("Животные не найдены.\n");
                }
                break;
            }
            case 5: {
                // Очистка памяти
                for(int i = 0; i < zoo_size; i++) {
                    free(zoo[i].name);
                }
                free(zoo);
                return 0;
            }
            default:
                printf("Неверный выбор!\n");
        }
    }
}

// Реализация функций

// Задача 1: Получение остатка через битовые поля
int get_remainder(int num) {
    BitField bf;
    memcpy(&bf, &num, sizeof(int));
    return bf.last_two_bits;
}

// Ввод данных животного
void input_animal(Animal *a) {
    printf("Введите количество особей: ");
    while(scanf("%d", &a->quantity) != 1 || a->quantity <= 0) {
        printf("Некорректный ввод! Введите положительное число: ");
        flush_input_buffer();
    }

    printf("Введите название: ");
    char buffer[100];
    scanf("%99s", buffer);
    a->name = malloc(strlen(buffer) + 1);
    strcpy(a->name, buffer);
}

// Вывод данных животного
void print_animal(Animal *a) {
    printf("Название: %s\n", a->name);
    printf("Количество: %d\n", a->quantity);
}

// Поиск животных по названию
Animal* find_animals(Animal *arr, int size, const char *name) {
    for(int i = 0; i < size; i++) {
        if(strcmp(arr[i].name, name) == 0) {
            return &arr[i];
        }
    }
    return NULL;
}

// Удаление животных по количеству
int remove_animals(Animal **arr, int size, int quantity) {
    int new_size = 0;
    Animal *new_arr = malloc(size * sizeof(Animal));
    if(!new_arr) exit(1);

    for(int i = 0; i < size; i++) {
        if((*arr)[i].quantity != quantity) {
            new_arr[new_size++] = (*arr)[i];
        } else {
            free((*arr)[i].name);
        }
    }

    free(*arr);
    *arr = realloc(new_arr, new_size * sizeof(Animal));
    return new_size;
}

// Очистка буфера ввода
void flush_input_buffer() {
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}
