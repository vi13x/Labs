#include "function.h"
int initStack(LinkedListStack* stack, int max_size) {
    if (max_size <= 0 || max_size > MAX_STACK_SIZE) {
        printf("Ошибка: размер стека должен быть от 1 до %d\n", MAX_STACK_SIZE);
        return 0;
    }
    stack->top = NULL;
    stack->size = 0;
    stack->max_size = max_size;
    return 1;
}

void freeStack(LinkedListStack* stack) {
    StackNode* current = stack->top;
    while (current != NULL) {
        StackNode* temp = current;
        current = current->next;
        free(temp);
    }
    stack->top = NULL;
    stack->size = 0;
}

int isEmpty(LinkedListStack* stack) {
    return stack->size == 0;
}

int isFull(LinkedListStack* stack) {
    return stack->size >= stack->max_size;
}

int push(LinkedListStack* stack, int value) {
    if (isFull(stack)) {
        printf("Стек переполнен!\n");
        return 0;
    }

    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    if (!newNode) {
        printf("Ошибка выделения памяти!\n");
        return 0;
    }

    newNode->data = value;
    newNode->next = stack->top;
    stack->top = newNode;
    stack->size++;
    return 1;
}

int pop(LinkedListStack* stack, int* value) {
    if (isEmpty(stack)) {
        return 0;
    }

    StackNode* temp = stack->top;
    *value = temp->data;
    stack->top = temp->next;
    free(temp);
    stack->size--;
    return 1;
}

void printStack(LinkedListStack* stack) {
    if (isEmpty(stack)) {
        printf("Стек пуст:\n");
        printf("|     |\n");
        printf("|_____|\n");
        return;
    }

    printf("Содержимое стека (%d/%d):\n", stack->size, stack->max_size);
    StackNode* current = stack->top;
    while (current != NULL) {
        printf("| %5d |\n", current->data);
        current = current->next;
    }
    printf("|_______|\n");
}

int inputInt(const char* prompt, int* value, int min, int max) {
    char buffer[100];
    while (1) {
        printf("%s", prompt);
        if (!fgets(buffer, sizeof(buffer), stdin)) {
            printf("Ошибка ввода!\n");
            continue;
        }

        char* endptr;
        *value = strtol(buffer, &endptr, 10);

        if (endptr == buffer || *endptr != '\n') {
            printf("Ошибка: введите целое число!\n");
            continue;
        }

        if (*value < min || *value > max) {
            printf("Ошибка: число должно быть от %d до %d!\n", min, max);
            continue;
        }

        return 1;
    }
}


void minStackel() {
    CLEAR_SCREEN();
    printf("=== Поиск минимального нечетного элемента ===\n");

    int max_size;
    if (!inputInt("Введите размер стека (1-1000): ", &max_size, 1, MAX_STACK_SIZE)) {
        return;
    }

    LinkedListStack stack;
    if (!initStack(&stack, max_size)) return;

    printf("Вводите элементы (0 для завершения):\n");
    while (!isFull(&stack)) {
        int val;
        char prompt[50];
        snprintf(prompt, sizeof(prompt), "Элемент #%d: ", stack.size + 1);

        if (!inputInt(prompt, &val, -10000, 10000)) continue;
        if (val == 0) break;
        if (!push(&stack, val)) break;
    }

    printStack(&stack);

    int min_odd = 0;
    int found = 0;
    StackNode* current = stack.top;

    while (current != NULL) {
        if (current->data % 2 != 0) {
            if (!found || current->data < min_odd) {
                min_odd = current->data;
                found = 1;
            }
        }
        current = current->next;
    }

    if (found) {
        printf("Минимальный нечетный элемент: %d\n", min_odd);
    } else {
        printf("Нечетные элементы отсутствуют\n");
    }

    freeStack(&stack);
}

void combinationStack() {
    CLEAR_SCREEN();
    printf("=== Объединение двух стеков ===\n");

    int max_size1, max_size2;
    if (!inputInt("Размер первого стека (1-1000): ", &max_size1, 1, MAX_STACK_SIZE)) return;
    if (!inputInt("Размер второго стека (1-1000): ", &max_size2, 1, MAX_STACK_SIZE)) return;

    LinkedListStack stack1, stack2;
    if (!initStack(&stack1, max_size1)) return;
    if (!initStack(&stack2, max_size2)) {
        freeStack(&stack1);
        return;
    }


    printf("\nПервый стек (по убыванию):\n");
    int prev_val = INT_MAX;
    while (!isFull(&stack1)) {
        int val;
        char prompt[50];
        snprintf(prompt, sizeof(prompt), "Элемент #%d (<= %d): ",
                 stack1.size + 1, stack1.size > 0 ? prev_val : INT_MAX);

        if (!inputInt(prompt, &val, INT_MIN, prev_val)) continue;
        if (val == 0) break;

        push(&stack1, val);
        prev_val = val;
    }

    printf("\nВторой стек (по возрастанию):\n");
    prev_val = INT_MIN;
    while (!isFull(&stack2)) {
        int val;
        char prompt[50];
        snprintf(prompt, sizeof(prompt), "Элемент #%d (>= %d): ",
                 stack2.size + 1, stack2.size > 0 ? prev_val : INT_MIN);

        if (!inputInt(prompt, &val, prev_val, INT_MAX)) continue;
        if (val == 0) break;

        push(&stack2, val);
        prev_val = val;
    }

    printf("\nПервый стек:\n");
    printStack(&stack1);
    printf("\nВторой стек:\n");
    printStack(&stack2);


    LinkedListStack stack3;
    if (!initStack(&stack3, stack1.size + stack2.size)) {
        freeStack(&stack1);
        freeStack(&stack2);
        return;
    }

    mergeStacks(&stack1, &stack2, &stack3);

    printf("\nРезультат объединения:\n");
    printStack(&stack3);

    freeStack(&stack1);
    freeStack(&stack2);
    freeStack(&stack3);
}

void mergeStacks(LinkedListStack* stack1, LinkedListStack* stack2, LinkedListStack* result) {
    int* elements = (int*)malloc((stack1->size + stack2->size) * sizeof(int));
    int index = 0;

    StackNode* current = stack1->top;
    while (current != NULL) {
        elements[index++] = current->data;
        current = current->next;
    }

    current = stack2->top;
    while (current != NULL) {
        elements[index++] = current->data;
        current = current->next;
    }

    for (int i = 0; i < index - 1; i++) {
        for (int j = i + 1; j < index; j++) {
            if (elements[i] > elements[j]) {
                int temp = elements[i];
                elements[i] = elements[j];
                elements[j] = temp;
            }
        }
    }


    for (int i = 0; i < index; i++) {
        push(result, elements[i]);
    }

    free(elements);
}