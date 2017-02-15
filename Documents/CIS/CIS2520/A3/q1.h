#ifndef __SZUBAI01_A3Q1__
#define __SZUBAI01_A3Q1__

struct treeStruct
{
    char name[10];
    double value;
    struct treeStruct * left, * right;
};

typedef struct treeStruct treeNode;

void runProg(char *);

void mainMenu(treeNode *);

void freeTree(treeNode *);

void printTree(treeNode *);

void displayTree(treeNode *, char **, int);

void printPreorder(treeNode *);

void printInorder(treeNode *);

void printPostorder(treeNode *);

void updateVar(treeNode *);

treeNode * createNode(char *);

treeNode * parseExpr(char *);

treeNode * findNode (treeNode *, char *);

int isDouble(char *);

int isVar(char *);

int isValidExp(char);

int isDig(char);

int findHeight(treeNode *);

double toDouble(char *);

double calcExpr(treeNode *);

#endif
