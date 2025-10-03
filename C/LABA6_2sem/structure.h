#ifndef STRUCTURE_H
#define STRUCTURE_H

typedef struct CharNode {
    char data;
    struct CharNode *next;
} CharNode;

typedef struct {
    CharNode *front;
    CharNode *rear;
} CharQueue;



typedef struct CharDequeNode {
    char data;
    struct CharDequeNode *next;
} CharDequeNode;

typedef struct {
    CharDequeNode *front;
    CharDequeNode *rear;
} CharDeque;


#endif
