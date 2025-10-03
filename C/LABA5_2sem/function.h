
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define MAX_STACK_SIZE 1000
#define CLEAR_SCREEN() system("cls")

typedef struct StackNode {
    int data;
    struct StackNode* next;
} StackNode;

typedef struct {
    StackNode* top;
    int size;
    int max_size;
} LinkedListStack;


int initStack(LinkedListStack* stack, int max_size);
void freeStack(LinkedListStack* stack);
int isEmpty(LinkedListStack* stack);
int isFull(LinkedListStack* stack);
int push(LinkedListStack* stack, int value);
int pop(LinkedListStack* stack, int* value);
void printStack(LinkedListStack* stack);
int inputInt(const char* prompt, int* value, int min, int max);
void minStackel();
void combinationStack();
void mergeStacks(LinkedListStack* stack1, LinkedListStack* stack2, LinkedListStack* stack3);