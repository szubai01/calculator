/*********************************************
Syed Usman Zubair        0921526      szubai01
Nov 04 2016              Assignment 3 Q1
*********************************************/

//Include files
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "q1.h"


/*
main
This program takes a commandline argument as input, and parses the expression
and strores it in a tree
IN: String (algebraic expression)
OUT: 0
*/
int main(int argc, char * argv[])
{
    if (argc!=2)
    {
        printf("Invalid number of arguments\n");
        return 0;
    }
    runProg(argv[1]);
    return 0;
}

/*
runProg
This runs the parse algorithm, and then the main menu
IN: String (algebraic expression)
OUT: None
*/
void runProg(char * toParse)
{
    treeNode * root;
    root = parseExpr(toParse);
    mainMenu(root);
    freeTree(root);
}

/*
mainMenu
This executes the main menu loop, until the user exits
IN: treeNode root
OUT: None
*/
void mainMenu(treeNode * root)
{
    int input = 25;
    while(input!=7)
    {
        //Display menu
        printf("\nSelect an option from below:\n");
        printf("1. Display\n");
        printf("2. Preorder\n");
        printf("3. Inorder\n");
        printf("4. Postorder\n");
        printf("5. Update\n");
        printf("6. Calculate\n");
        printf("7. Exit\n");
        scanf("%d", &input);

        //Options of input
        switch(input)
        {
            case 1:
                printTree(root);
                break;
            case 2:
                printPreorder(root);
                printf("\n");
                break;
            case 3:
                printInorder(root);
                printf("\n");
                break;
            case 4:
                printPostorder(root);
                printf("\n");
                break;
            case 5:
                updateVar(root);
                break;
            case 6:
                printf("The result is %.2lf\n", calcExpr(root));
                break;
            case 7:
                break;
            default:
                printf("Invalid entry\n");
                break;
        }
    }
}

/*
freeTree
This frees memory used by tree
IN: treeNode * head
OUT: None
*/
void freeTree(treeNode * head)
{
    treeNode * left, * right;
    left = head->left;
    right = head->right;
    free(head);
    if(left!=NULL)
    {
        freeTree(left);
    }
    if(right != NULL)
    {
        freeTree(right);
    }
}

/*
printTree
This prints a tree in a visual format
IN: treeNode of root
OUT: None
*/
void printTree(treeNode * head)
{
    int height = findHeight(head);
    char ** lines;

    lines = malloc(sizeof(char *) * height); //mallocs memory for each row
    if (lines==NULL)
    {
        printf("Unable to malloc memory\n");
        return;
    }

    for(int i=0; i<height; i++)
    {
        lines[i] = malloc(sizeof(char)*50);//mallocs memory for each char (column)
        if(lines[i]==NULL)
        {
            printf("Unable to malloc memory\n");
            return;
        }
        strcpy(lines[i], "\0");
    }

    displayTree(head, lines, 0);

    for(int i=0; i<height; i++)
    {
        printf("%s\n", lines[i]);
        free(lines[i]);
    }

    free(lines);
}

/*
displayTree
This recursively saves lines of the tree to the 2D character array
IN: treeNode of head, char ** to store lines, int level of current node
OUT: Data is stored in the 2D char array
*/
void displayTree(treeNode * head, char ** inLines, int level)
{
    if (head!=NULL)
    {
        char toAdd[25];

        strcpy(toAdd, "\0");
        for(int i=0; i < findHeight(head) * 6; i++)
        {
            strcat(toAdd, " ");
        }

        switch(head->name[0])
        {
            case '*':
            case '+':
            case '-':
            case '/':
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9'://If node is operator or value
                strcat(toAdd, " (");
                strcat(toAdd, head->name);
                strcat(toAdd, ") ");
                break;
            case 'x':
            case 'X'://if operator is variable
                sprintf(toAdd, " (%s=%.2lf) ", head->name, head->value);
                break;
            default:
                break;
        }
        strcat(inLines[level], toAdd);
        displayTree(head->left, inLines, level + 1);
        displayTree(head->right, inLines, level + 1);
    }
}

/*
printPreorder
Prints the expression in preorder form recursively
IN: treeNode current node
OUT: Expression is printed in pre order
*/
void printPreorder(treeNode * head)
{
    printf(" %s ", head->name);
    if (head->left != NULL)
    {
        printPreorder(head->left);
    }
    if(head->right!=NULL)
    {
        printPreorder(head->right);
    }
}

/*
printInorder
Prints the expression in inorder form recursively
IN: treeNode current node
OUT: Expression is printed in inorder
*/
void printInorder(treeNode * head)
{
    if (head->left != NULL)
    {
        printf("(");
        printInorder(head->left);
    }

    printf("%s", head->name);

    if(head->right!=NULL)
    {
        printInorder(head->right);
        printf(")");
    }
}

/*
printPostorder
Prints the expression in postorder form recursively
IN: treeNode current node
OUT: Expression is printed in post order
*/
void printPostorder(treeNode * head)
{
    if (head->left != NULL)
    {
        printPostorder(head->left);
    }
    if(head->right!=NULL)
    {
        printPostorder(head->right);
    }
    printf(" %s ", head->name);
}

/*
updateVar
Allows user to change value of a variable
IN: treeNode of root
OUT: None
*/
void updateVar(treeNode * root)
{
    char inLine[50], cleanIn[50], vName[3];
    int cleanL = 0;
    double value;
    treeNode * nodeLoc;

    printf("Enter a variable name followed by value\n");
    scanf("%*c");
    fgets(inLine, 48, stdin);
    for (int i=0; i<strlen(inLine); i++) //loop for each char in input
    {
        switch (inLine[i])
        {
            case 'x':
            case 'X':
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
            case '.': //valid characters
                cleanIn[cleanL] = inLine[i];
                cleanL++;
                break;
            default:
                break;
        }
    }
    cleanIn[cleanL]='\0';//terminates string
    sscanf(cleanIn, "%c%c%lf", &vName[0], &vName[1], &value);//gets desired values
    vName[2]='\0';

    nodeLoc = findNode(root, vName); //looks for variable
    if (nodeLoc!=NULL) //if var is found
    {
        nodeLoc->value = value;
        printf("Updated succesfully\n");
    }
    else //if var is not found
    {
        printf("Could not find variable\n");
    }

}

/*
createNode
Creates a new node, mallocing memory and initiallizing values
IN: String for variable name
OUT: treeNode pointer to newly allocated memory
*/
treeNode * createNode(char * varName)
{
    treeNode * newNode = malloc(sizeof(treeNode)); //mallocs space for new node
    if (newNode == NULL)
    {
        printf("Error: unable to malloc memory\n");
    }
    if (isDouble(varName)) //if var is double, assigns value
    {
        double newVal = toDouble(varName);
        newNode->value = newVal;
    }
    else
    {
        newNode->value = 0.0; //sets inital value to zero
    }
    strcpy(newNode->name, varName);
    newNode->left = NULL;
    newNode->right= NULL;

    return newNode;
}

/*
parseExpr
Parses string into math expression arranged in tree
IN: String to parse
OUT: treeNode pointer to root
*/
treeNode * parseExpr(char * toParse)
{
    int opBrac, clBrac, firstBrac, operatorLoc, vLength;
    char expr1[50], expr2[50], op[2], cleanParse[50];
    treeNode * curr;

    vLength = 0;
    for(int i=0; i<strlen(toParse); i++) //loop to go through string and remove invalid chars
    {
        if(isValidExp(toParse[i]))
        {
            cleanParse[vLength]=toParse[i];
            vLength++;
        }
    }

    cleanParse[vLength] = '\0'; //terminates strings

    if((isDouble(cleanParse)) || (isVar(cleanParse)))//if node is just var or double (simplest expression)
    {
        return createNode(cleanParse);
    }

    //To find operator.........
    opBrac = clBrac = 0;
    firstBrac = 1;
    for (int i=1; i<strlen(cleanParse) - 1; i++)
    {
        if(cleanParse[i]=='(')
        {
            opBrac++;
            if(!firstBrac)
            {
                firstBrac=i;
            }
        }
        else if(cleanParse[i]==')')
        {
            clBrac++;
        }

        if((clBrac-opBrac)==0)
        {
            operatorLoc = strpbrk(cleanParse + i, "*/+-") - cleanParse;
            break;
        }
    }

    strncpy(expr1, cleanParse + firstBrac, operatorLoc-1); //creates first part of sub expression
    expr1[operatorLoc - 1]='\0';

    strncpy(expr2, cleanParse + operatorLoc + 1, strlen(cleanParse) - operatorLoc - 2);
    expr2[strlen(cleanParse) - operatorLoc - 2] = '\0'; //second part of sub expression
    op[0] = cleanParse[operatorLoc]; //operator
    op[1] = '\0';
    curr = createNode(op); //makes node for operator
    curr->left = parseExpr(expr1); //parse left sub expression
    curr->right = parseExpr(expr2); //parse right sub expression
    return curr;
}


/*
findNode
Finds node of matching name
IN: treeNode head, string of name
OUT: treeNode pointer to matching result
*/
treeNode * findNode(treeNode * head, char * findName)
{
    treeNode * leftNode, * rightNode;
    if(head!=NULL)
    {
        if (!(strncmp(head->name, findName, 2))) //if match is found
        {
            return head;
        }
        if (head->left!=NULL) //if there is left subtree
        {
            leftNode = findNode(head->left, findName);
            if (leftNode!=NULL)
            {
                return leftNode;
            }
        }
        if (head->right!=NULL) //if there is right sub tree
        {
            rightNode = findNode(head->right, findName);
            if(rightNode!=NULL)
            {
                return rightNode;
            }
        }
    }
    return NULL;
}

/*
isDouble
Checks if input is double in form Y.YY
IN: string input
OUT: 1 if it is double, 0 otherwise
*/
int isDouble(char * input)
{
    if (strlen(input)!=4)
    {
        return 0;
    }
    if ( (isDig(input[0])) && (isDig(input[2])) && (isDig(input[3])) && (input[1]=='.') )
    {
        return 1;
    }
    return 0;
}

/*
isVar
checks if input is a variable
IN: string input
OUT: 1 if it is var, 0 otherwise
*/
int isVar(char * input)
{
    if(strlen(input)!=2)
    {
        return 0;
    }
    if(((input[0]=='x') || (input[0]=='X')) && (isDig(input[1])))
    {
        return 1;
    }
    return 0;
}

/*
isValidExp
checks if char is a valid option
IN: char
OUT: 1 if it is valid, 0 otherwise
*/
int isValidExp(char charVal)
{
    switch(charVal)
    {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case '+':
        case '-':
        case '/':
        case '*':
        case '(':
        case ')':
        case '.':
        case 'x':
        case 'X':
            return 1;
        default:
            return 0;
    }
    return 0;
}

/*
isDig
Checks if char is a digit
IN: Char
OUT: 1 if it is char, 0 otherwise
*/
int isDig(char charDig)
{
    switch (charDig)
    {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            return 1;
        default:
            return 0;
    }
    return 0;
}

/*
findHeight
Calculates height of tree
IN: treeNode head
OUT: int height
*/
int findHeight(treeNode * head)
{
    if (head==NULL)
    {
        return 0;
    }

    int maxLHeight, maxRHeight;
    maxLHeight = findHeight(head->left) + 1;
    maxRHeight = findHeight(head->right) + 1;

    if (maxLHeight>maxRHeight)
    {
        return maxLHeight;
    }
    return maxRHeight;
}

/*
toDouble
Converts string to double
IN: string
OUT: double
*/
double toDouble(char * convert)
{
    int intPart, tenths, hundredths;
    intPart = convert[0] - '0';
    tenths = convert[2] - '0';
    hundredths = convert[3] - '0';

    return (double)(intPart + tenths/10.0 + hundredths/100.0);
}

/*
calcExpr
Evaluates expression
IN: treeNode
OUT: double of calculated value
*/
double calcExpr(treeNode * head)
{
    if (head==NULL)
    {
        return 0.0;
    }
    switch(head->name[0])
    {
        case 'x':
        case 'X':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case '0':
            return head->value;
        case '+': //if adding
            return calcExpr(head->left) + calcExpr(head->right);
        case '-': //if subtracting
            return calcExpr(head->left) - calcExpr(head->right);
        case '*': //if multiplying
            return calcExpr(head->left) * calcExpr(head->right);
        case '/': //if dividing
            if(calcExpr(head->right) == 0.0)
            {
                printf("Divide by zero error, cannot find valid output\n");
                return 999999.999;
            }
            return calcExpr(head->left) / calcExpr(head->right);
        default:
            break;
    }
    return 0.0;
}
