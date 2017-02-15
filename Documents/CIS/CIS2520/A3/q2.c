/********************************************
Syed Usman Zubair	0921526	     szubai01
Nov 6 2016		Assignment 3 Q2
********************************************/


//Include files
#include <stdio.h>
#include "q2.h"

/*
main
Program reads f.dat, stores in a heap, then displays the heap.
IN: None
OUT: 0
*/
int main()
{
    startProg();
    return 0;
}

/*
startProg
Reads f.dat file, then creates a heao
IN: None
OUT: None
*/
void startProg()
{
    //Declare variables
    FILE * inFile;
    int len = 20;
    row arrRows[len + 1];

    inFile = fopen("f.dat", "r"); //opens file
    if (inFile == NULL)
    {
        printf("Could not open f.dat\n");
        return;
    }

    for(int rowNum = 1; rowNum <= len; rowNum++) //loop to go through length of array
    {
        for(int i=0; i<10; i++) //loop for each line
        {
            fscanf(inFile, "%2d", &arrRows[rowNum].items[i]); //scans integer
        }
        arrRows[rowNum].key = arrRows[rowNum].items[0] + arrRows[rowNum].items[1] + arrRows[rowNum].items[2]; //calculates key
    }

    fclose(inFile);

    sortHeap(arrRows, len); //heapifies heap

    for(int rowNum = 1; rowNum <= len; rowNum++)
    {
        for(int i=0; i<10; i++)
        {
            printf("%2d ", arrRows[rowNum].items[i]);//prints heap
        }
        printf("\n");
    }
}

/*
sortHeap
Applies downheap on all parent nodes
IN: array of rows, length of array
OUT: None
*/
void sortHeap(row * arrRows, int len)
{
    for(int i=len/2; i >= 1; i--) //for each parent, starting from bottom
    {
        downHeap(arrRows, i, len);
    }
}

/*
downHeap
Downheaps the parent node, recursively, as required
IN: array of rows, int index of parent, int max element
OUT: None
*/
void downHeap(row * arrRow, int parent, int max)
{
    int nChildren, parNewLoc;

    parNewLoc = parent; //variable to track if parent was moved

    if(parent * 2 + 1<= max) //to calculate number of children
    {
        nChildren = 2;
    }
    else if(parent * 2 == max)
    {
        nChildren = 1;
    }
    else
    {
        nChildren = 0;
    }

    switch(nChildren)
    {
        case 2: //if there are two children
            if((arrRow[parent].key > arrRow[parent * 2].key) && (arrRow[parent].key > arrRow[parent * 2 + 1].key))
            { //if parent is bigger than both children
                int minIndex;
                minIndex = findMinI(arrRow, parent * 2, parent * 2 + 1); //finds min index
                swapRow(arrRow, parent, minIndex); //swaps rows
                parNewLoc = minIndex; //stores parents new location
                break;
            }
            else if(arrRow[parent].key > arrRow[parent * 2 + 1].key) // if second child is smaller
            {
                swapRow(arrRow, parent, parent * 2 + 1); //swaps rows
                parNewLoc = parent * 2 + 1;
                break;
            } //deliberate fall-through
        case 1:
            if(arrRow[parent].key > arrRow[parent * 2].key) //if first child is smaller
            {
                swapRow(arrRow, parent, parent * 2);
                parNewLoc = parent * 2;
                break;
            }
        default:
            break;
    }

    if(parent!=parNewLoc) //if parent location was changed
    {
        downHeap(arrRow, parNewLoc, max); //downheaps from new location
    }
}

/*
findMinI
finds the minimum index of the two indexes provided
IN: array of rows, int index1, int index2
OUT: index of minimum number
*/
int findMinI(row * rowsList, int ind1, int ind2)
{
    if(rowsList[ind1].key <= rowsList[ind2].key)
    {
        return ind1; //if the first index is smaller or equal, it is returned
    }
    return ind2; //if second index is smaller, it is returned
}

/*
swapRow
Swaps two rows
IN: array of rows, index of parent, index of child to swap with
OUT: None
*/
void swapRow(row * rowsL, int par, int child)
{
    row temp = rowsL[child]; //temp var to store one row
    rowsL[child] = rowsL[par]; //puts parent in child's place
    rowsL[par] = temp; //puts child in parent's place
}
