#ifndef FUNCTION_H
#define FUNCTION_H
#include "windows.h"
#include "structure.h"

void initCharQueue(CharQueue *q);
int isCharQueueEmpty(CharQueue *q);
void enqueueChar(CharQueue *q, char c);
void dequeueChar(CharQueue *q);
void displayCharQueue(CharQueue *q);
void freeCharQueue(CharQueue *q);
void createQueue();


void initCharDeque(CharDeque *dq);
int isCharDequeEmpty(CharDeque *dq);
void insertLeft(CharDeque *dq, char c);
void insertRight(CharDeque *dq, char c);
void displayCharDeque(CharDeque *dq);
void freeCharDeque(CharDeque *dq);
void createDeck();

#endif
