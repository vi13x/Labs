#include "structure.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <windows.h>
#define COL_WARNING 12
#define COL_MENU 10
#define COL_RESET 7


void set_color(int color);

void printMenu();
void printAddMenu();
void printDeleteMenu();
void printTreeHeader();

Node* createNode(int data);
Node* insert(Node* root, int data);
Node* minValueNode(Node* node);
Node* deleteNode(Node* root, int key);
int height(Node* node);
void findUnbalancedNodes(Node* root);
void printTree(Node* root, int space);
void freeTree(Node* root);
void binaryTree();

int readInt(int *value);
void clearBuffer();
void addNodes(Node** root);
void createNewTree(Node** root);
