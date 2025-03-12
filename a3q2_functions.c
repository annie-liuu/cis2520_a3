#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "a3q2_header.h"

/*
 * The downHeap function performs the downheap algorithm.
 * The key at the passed position is swapped with the key of it's child with the smallest value.
 * If the key is smaller, than both of it's children's keys then no swap happens.
 * After swap, the downHeap is called again to the new position of the swapped key and it terminates when it's value is smaller than both children.
*/
void downHeap(int key[20], int pos, int array[20][10]){
    int childIndex = 2 * pos + 1; // left child index
    int curVal = key[pos]; // value that is currently being evaluated
    int maxValue, maxIndex;

    while (childIndex < 20){ // loop until end of heap
        maxValue = curVal; // sets current max value
        maxIndex = -1;
        for (int i = 0; i < 2; i++){ // chekcs both children and looks for a larger value child
            if (childIndex + 1 < 20){ // if the index is valid
                if (key[childIndex+i] > maxValue){ // if it is larger, change the maxValue and index
                    maxValue = key[childIndex+i];
                    maxIndex = childIndex + i;
                }
            }
        }
        if (maxValue == curVal){ // if the maxValue changed and is the current value, then heap is finished
            return;
        }
        else{ // if it is not, it swaps the two values
            swap(pos, maxIndex, key, array);
            pos = maxIndex;
            childIndex = 2 * pos + 1;
        }
    }
}

// The isParent function returns true if the passed position has a child or false if there's no child
bool isParent(int keyPos){
    return keyPos < 10;
}

// The swap function swaps 2 rows in the 2D array and the key array. It receives the position of the 2 rows to be swapped, the key array, and the 2D array in its arguements.
void swap(int key1Pos, int key2Pos, int key[20], int array[20][10]){
    int temp = key[key1Pos];
    key[key1Pos] = key[key2Pos];
    key[key2Pos] = temp;

    for (int i = 0; i < 10; i++){
        int temp = array[key2Pos][i];
        array[key1Pos][i] = array[key2Pos][i];
        array[key2Pos][i] = temp;
    }
}
