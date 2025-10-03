#include <stdio.h>
#include <stdlib.h>
#include "function.h"


void initCharQueue(CharQueue *q) {
    q->front = q->rear = NULL;
}

int isCharQueueEmpty(CharQueue *q) {
    return q->front == NULL;
}

void enqueueChar(CharQueue *q, char c) {
    CharNode *newNode = (CharNode *)malloc(sizeof(CharNode));
    newNode->data = c;
    newNode->next = NULL;
    if (q->rear == NULL) {
        q->front = q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

void dequeueChar(CharQueue *q) {
    if (isCharQueueEmpty(q)) return;
    CharNode *temp = q->front;
    q->front = q->front->next;
    if (q->front == NULL) q->rear = NULL;
    free(temp);
}

void displayCharQueue(CharQueue *q) {
    CharNode *curr = q->front;
    if (curr == NULL) {
        printf("Очередь пуста.\n");
        return;
    }
    while (curr != NULL) {
        printf("%c ", curr->data);
        curr = curr->next;
    }
    printf("\n");
}

void freeCharQueue(CharQueue *q) {
    while (!isCharQueueEmpty(q)) {
        dequeueChar(q);
    }
}

void createQueue() {
    CharQueue q;
    initCharQueue(&q);
    char ch;

    while (1) {
        printf("Введите символ (0 для выхода): ");
        ch = getchar();
        while (getchar() != '\n');

        if (ch == '0') break;

        if (!isCharQueueEmpty(&q) && q.rear->data == ch) {
            dequeueChar(&q);
            printf("Удален первый элемент.\n");
        } else {
            enqueueChar(&q, ch);
        }

        printf("Состояние очереди: ");
        displayCharQueue(&q);
    }
    freeCharQueue(&q);
}


void initCharDeque(CharDeque *dq) {
    dq->front = dq->rear = NULL;
}

int isCharDequeEmpty(CharDeque *dq) {
    return dq->front == NULL;
}

void insertLeft(CharDeque *dq, char c) {
    CharDequeNode *newNode = (CharDequeNode *)malloc(sizeof(CharDequeNode));
    newNode->data = c;
    newNode->next = dq->front;
    dq->front = newNode;
    if (dq->rear == NULL) dq->rear = newNode;
}

void insertRight(CharDeque *dq, char c) {
    CharDequeNode *newNode = (CharDequeNode *)malloc(sizeof(CharDequeNode));
    newNode->data = c;
    newNode->next = NULL;
    if (dq->rear == NULL) {
        dq->front = dq->rear = newNode;
    } else {
        dq->rear->next = newNode;
        dq->rear = newNode;
    }
}

void displayCharDeque(CharDeque *dq) {
    CharDequeNode *curr = dq->front;
    if (curr == NULL) {
        printf("Дек пуст.\n");
        return;
    }
    while (curr != NULL) {
        printf("%c ", curr->data);
        curr = curr->next;
    }
    printf("\n");
}

void freeCharDeque(CharDeque *dq) {
    CharDequeNode *curr = dq->front;
    while (curr != NULL) {
        CharDequeNode *temp = curr;
        curr = curr->next;
        free(temp);
    }
    dq->front = dq->rear = NULL;
}

void createDeck() {
    CharDeque dq;
    initCharDeque(&dq);
    char ch;
    int flag = 1;

    while (1) {
        printf("Введите символ (0 для выхода): ");
        ch = getchar();
        while (getchar() != '\n');

        if (ch == '0') break;

        if (flag) {
            if (!isCharDequeEmpty(&dq) && dq.front->data == ch) {
                printf("Символ совпадает с левым концом.\n");
            } else {
                insertLeft(&dq, ch);
            }
        } else {
            if (!isCharDequeEmpty(&dq) && dq.rear->data == ch) {
                printf("Символ совпадает с правым концом.\n");
            } else {
                insertRight(&dq, ch);
            }
        }
        flag = !flag;

        printf("Состояние дека: ");
        displayCharDeque(&dq);
    }
    freeCharDeque(&dq);
}
