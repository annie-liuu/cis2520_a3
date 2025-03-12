#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "a3q1_header.h"

Variable variables[10];
int varCount = 0;

// The createNode function allocates memory to the tree and creates a new node using the given data before returning the node.
Node * createNode (char * value){
    Node * newNode = malloc(sizeof(Node));
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->data = malloc(strlen(value)+1);
    strcpy(newNode->data,value);
    return newNode;
}

// The parseExpression function parses the expression string passed in from command line, stores the information in a new node, and returns the root node of the tree.
Node* parseExpression(char *expr, char * tokens[25]){
    int numChar = strlen(expr);
    char * input = expr;
    int i = 0, tokCount = 0;
    char buffer[25];

    while (input[i]!='\0' && i < numChar){ // iterates through chars of the input, ensures i is less than length of input (removes "\bin" and "\bash")
        if (isValue(&input[i])){ // if the input is a variable/constant
            int k = 0;
            while (isValue(&input[i]) && k < 24){ // allows multiple characters (ex. x1)
                buffer[k++] = input[i++];
            }
            buffer[k]='\0';
            tokens[tokCount] = malloc(strlen(buffer)+1); // memory for buffer and null char
            strcpy(tokens[tokCount++],buffer);
        }
        else{ // input is an operator or parenthesis
            buffer[0] = input[i++];
            buffer[1] = '\0';
            tokens[tokCount] = malloc(strlen(buffer)+1); // memory for buffer and null char
            strcpy(tokens[tokCount++],buffer);
        }
    }


    // converting into reverse polish notation
    char * rpn[tokCount];
    Stack stack; // stack containing operators
    stack.top = -1; // setting top to -1
    int index = 0; // index of array in rpn

    for (int i = 0; i < tokCount; i++){
        char * token = tokens[i];

        if (isValue(&token[0])){
            //for checking if token is a variable or a double
            char * dubCheck;
            strtod(token, &dubCheck);
            if (*dubCheck != '\0'){
                variables[varCount].varName = token;
                varCount++;
            }

            rpn[index] = token;
            index++;
        }
        else if(isOp(*token)){
            while(stack.top != -1 && isOp(*peek(&stack)) && (pedmas(*peek(&stack)) >= pedmas(*token))){
                rpn[index] = pop(&stack);
                index++;
            }
            push(&stack, token);
        }
        else if(isOpenPar(*token)){
            push(&stack, token);
        }
        else if (isClosePar(*token)){
            while(!isEmpty(&stack) && !isOpenPar(*peek(&stack))){
                rpn[index] = pop(&stack);
                index++;
            }
            pop(&stack); // pop '('
        }else{
            printf("Invalid token: %s\n", token);
            return NULL;
        }
    }
    if (!isEmpty(&stack)){ // this pops remaining operators from the stack
        rpn[index] = pop(&stack);
        index++;
    }

    // creating binary tree from rpn[]
    TreeStack tree;
    tree.top = -1;
    for (int i = 0; i < index; i++){
        char * leaf = rpn[i];
        if (isOp(*leaf)){
            Node * node = createNode(leaf);
            node->right = tPop(&tree);
            node->left = tPop(&tree);
            tPush(&tree, node);
        }
        else{
            Node * node = createNode(leaf);
            tPush(&tree, node);
        }
        
    }
    return tPop(&tree); // this is the root of the tree
}

// The preOrder function prints tree nodes in preorder traversal.
void preorder(Node *root){
    // base casw
    if (root == NULL){
        return;
    }

    printf("%s ", root->data);
    preorder(root->left); // traverses left first
    preorder(root->right); // traverses right afterwards
}

// The inOrder function prints tree nodes in inorder traversal fully parenthesized.
void inorder(Node *root){
    // base case
    if (root == NULL){
        return;
    }
    inorder(root->left); // prints left side first
    printf("%s ", root->data);
    inorder(root->right); // deals with right side afterwards
}

// The postOrder function prints tree nodes in postorder traversal.
void postorder(Node *root){
    // base case 
    if (root == NULL){
        return;
    }
    postorder(root->left);
    postorder(root->right);
    printf("%s ", root->data);
}

// The promptVariables function prompts the user to assign values to each variable found in the expression tree. The values should be stored in the Variables struct.
void promptVariables(Node *root){
    for (int i = 0; i < varCount; i++){
        printf("What is the value of %s? ", variables[i].varName);
        scanf("%f", &variables[i].value);
    }
}

// The calculate function calculates the expression and returns its result. Division by 0 and/or other error scenarios should be checked.
float calculate(Node *root){
    // base case
    if (root == NULL){
        return 0;
    }
    if (isValue(root->data)){
        for (int i = 0; i < varCount; i++){
            if (strcmp(root->data, variables[i].varName)==0){
                return variables[i].value;
            }
        }
        return atof(root->data);
    }
    float left = calculate(root->left);
    float right = calculate(root->right);

    if (strcmp(&root->data[0],"+") == 0) return left + right;
    else if (strcmp(&root->data[0],"-")==0) return left - right;
    else if (strcmp(&root->data[0],"*")==0) return left * right;
    else if (strcmp(&root->data[0],"/")==0){
        if (right == 0){
            printf("Division by zero detected. Terminating program.\n");
            exit(1);
        }
        return left / right;
    } 
	return 0;
}


// The following are all helper functions
bool isOp (char c){
    return (c == '+' || c == '-' || c == '/' || c == '*');
}

bool isOpenPar (char c){
    return (c == '(');
}

bool isClosePar(char c){
    return (c == ')');
}

void push(Stack * stack, char c[25]){
    stack->arr[++(stack->top)] = c;
}

char * pop (Stack * stack){
    if (stack->top != -1){
        return stack->arr[(stack->top)--];
    }
    else return NULL;
}

bool isEmpty(Stack* stack){
    return stack->top ==- 1;
}

char * peek (Stack * stack){
    if (stack->top!= -1){
        return stack->arr[stack->top];
    }
    else return NULL;
}

int pedmas(char op){
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

bool isValue(char *c){
    return *c != '(' && *c != ')' && !isOp(*c);
}

void tPush(TreeStack * stack, Node * n){
    if (stack->top < 24){
        stack->items[++(stack->top)] = n;
    } 
}

Node * tPop(TreeStack * stack){
    if (stack->top != -1){
        return stack->items[(stack->top)--];
    }
    else return NULL;
}

Node * tPeek(TreeStack * stack){
    if (stack->top!= -1){
        return stack->items[stack->top];
    }
    else return NULL;
}

void freeTree(Node * root){
    if (root == NULL){
        return;
    }
    freeTree(root->left);
    freeTree(root->right);
    free(root->data);
    free(root);
}