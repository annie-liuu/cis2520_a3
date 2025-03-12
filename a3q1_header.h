#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#ifndef BINARY_TREE
#define BINARY_TREE

// Node structure representing a binary tree node containing string data.
typedef struct Node{ 
    struct Node *left;
    struct Node *right;
    char * data;
}Node;

// Structure that stores variable names and their associated values
typedef struct Stack{ 
    char * arr[25];
    int top;
}Stack;

// Structure that stores specifically nodes
typedef struct TreeStack{
    Node * items[25];
    int top;
}TreeStack;

typedef struct Variable{
    char * varName;
    float value;
}Variable;


Node * createNode(char * value);
Node * parseExpression (char *expr, char * tokens[25]);
void preorder(Node *root);
void inorder(Node *root);
void postorder(Node *root);
void promptVariables(Node *root);
float calculate(Node *root);

bool isOp (char c);
bool isOpenPar (char c);
bool isClosePar (char c);

void push(Stack * stack, char c[25]);
char * pop(Stack * stack);
bool isEmpty(Stack* stack);
int pedmas(char op);
char * peek (Stack * stack);
bool isValue(char *c);

void tPush(TreeStack * stack, Node * n);
Node * tPop(TreeStack * stack);
Node * tPeek(TreeStack * stack);

void freeTree(Node * stack);

#endif