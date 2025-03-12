# CIS2520-F24-A3 

## Student Information:
Name: Annie Liu
Student Number: 1266956

## Assignment Overview
a3q1

This takes an expression from the command line and creates a binary tree 
based off of it. It first converts the string into reverse polish notation,
then creates the tree from an array of the tokens. It displays a menu for
the user to see the tree in different orders (preorder, inorder, postorder)
and also evaluates the expression.

a3q2

This creates a max heap from a file "f.dat" with each node containing an
object where the key is the sum of the first 3 integers. "f.dat" contains 
200 2-digit integers, and the program represents the heap created as an array
where each row is an object. 

## Resources 
For a3q2, in downHeap(), the pseudocode posted in the notes for this class 
was followed to create the function. 

## Implementation
The assignment is complete, however there are some input validations not considered.
For example, in a3q1, if the expression is (-2+8), it will not run properly
as it will consider '-' as an operator and not a part of '-2' as a value. 

## Compiling
To Compile both a3q1 and a3q2:

$ make

To compile just a3q1:

$ make a3q1

To compile just a3q2:

$ make a3q2:

To clean:

$ make clean

## Executing a3q1
$ ./a3q1 "expression here"

Program will not run if there is not an expected number of arguments (1)
Ensure command-line argument is in quotations to avoid errors. 

## Executing a3q2
$ ./a3q2

If the file "f.dat" is not found, the program will end. 

## Files
a3q1_main.c
- Contains the main function of a3q1, where menu is displayed. 
a3q1_functions.c 
- Contains all the function definitions of a3q1.
a3q1_header.h 
- Header file for function declaration for a3q1_main.c

a3q2_main.c 
- Contains the main function of a3q2, where menu is displayed. 
a3q2_functions.c 
- Contains all the function defintions of a3q2.
a3q2_header.h 
- Header file for function declarations for a3q2_main.c
