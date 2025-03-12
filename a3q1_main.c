/*
Student Name: Annie Liu
Student ID: 1266956
Due Date: November 15th, 2024
Course: CIS*2520

I have exclusive control over this submissino via my password. 
By including this header comment, I certify that:
  1) I have read and understood the policy on academic integrity.
  2) I have completed Moodle's module on academic integrity. 
  3) I have achieved at least 80% on the academic integrity quiz. 
I assert that this work is my own. I have appropriately acknowledged
any and all material that I have used, be it directly quoted or
paraphrased. Furthermore, I certify that this assignment was written 
by me in its entirety. 
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "a3q1_header.h"


int main(int argc, char * argv[]){
    if (argc != 2){
        printf("The expected number of arguments was not given.\n");
        return 1;
    }
    char * tokens [25];
    Node * root = parseExpression(argv[1], tokens);
    if (root == NULL){
        printf("Something went wrong.\n");
        return 1;
    }

    int choice;
    do {
        printf("\nMenu:\n");
        printf("1. Preorder\n");
        printf("2. Inorder\n");
        printf("3. Postorder\n");
        printf("4. Calculate\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: preorder(root); printf("\n"); break;
            case 2: inorder(root); printf("\n"); break;
            case 3: postorder(root); printf("\n"); break;
            case 4: 
                // varCount = 0; // resetting for each loop
                promptVariables(root);
                printf("Result: %.2f\n", calculate(root));
                break;
            case 5: {
                freeTree(root); 
                for (int i = 0; i < 25; i++) {
                    if (tokens[i]!=NULL)free(tokens[i]);
                }
                break;
            }
            default: printf("Please enter a valid choice.\n");
        }
    } while (choice != 5);

    return 0;
}