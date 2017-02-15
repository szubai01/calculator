#ifndef __SZUBAI01_Q2__
#define __SZUBAI01_Q2__

struct rowStruct
{
    int items[10];
    int key;
};

typedef struct rowStruct row;

void startProg();

void sortHeap(row *, int);

void downHeap(row *, int, int);

int findMinI(row *, int, int);

void swapRow(row *, int, int);

#endif
