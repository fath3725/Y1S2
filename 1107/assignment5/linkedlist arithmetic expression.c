#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SIZE 80 //The size of the array

enum ExpType {OPT,OPERAND};

typedef struct _listnode
{
    int  item;
    enum ExpType type;
	struct _listnode *next;
} ListNode;

typedef struct _linkedlist{
   int size;
   ListNode *head;
} LinkedList;

void insertNode(LinkedList *llPtr, int item, enum ExpType type);
int deleteNode(LinkedList *llPtr);
void removeAllNodes(LinkedList *llPtr);
int isEmptyLinkedList (LinkedList ll);

void expressionLL(char* infix, LinkedList *inExpLL);

void printExpLL(LinkedList inExpQ, int seed);

int main()
{
    char infix[SIZE];

    //printf("Enter an infix expression:\n");
    gets(infix);

    LinkedList inExpLL;
    inExpLL.head = NULL;
    inExpLL.size = 0;

    expressionLL(infix, &inExpLL);

    int seed;
    //printf("Enter a seed: \n");
    scanf("%d",&seed);
    printExpLL(inExpLL,seed);

    removeAllNodes(&inExpLL);
    return 0;
}


void expressionLL(char* infix, LinkedList *inExpLL)
{ 
    if (infix[0] == '\0') return;

    int len = strlen(infix);// reverse string
    int k = len;
    for(int i = 0; i < len; i++) 
    {
        char temp = infix[k];
        infix[k] = infix[i];
        infix[i] = temp;
        k--;
        if(k == (len / 2))
        {
            break;
        }
    } // string reversed WORKS GOOD
    
    for(int i = 1; i <= len;)
    {
        if (isdigit(infix[i]) != 0)// if DIGIT
        { 
            int store = 0;
            int multiplier = 1;
            int j = i;
            while (isdigit(infix[j]) != 0)
            {
                int temp = infix[j]; //in ascii form
                temp = temp-'0';// convert from ascii to int
                store = store+multiplier*temp; // reverse order of numbers
                j++;
                multiplier *= 10;
                i++;
            }
            insertNode(inExpLL, store, OPERAND);
        }
        else if (infix[i] == " " || infix[i] == "\n" || infix[i] == '\t' || infix[i] == '\r' || infix[i] == '\x0b'){ //whitespace charas
            i++;
        }
        else //if NOT digit
        {  
            insertNode(inExpLL, infix[i], OPT);
            i++;            
        }
    }  
}

void printExpLL(LinkedList inExpLL, int seed)
{
    ListNode* temp = NULL;
    temp = inExpLL.head;
    while(temp!= NULL){
        if(temp->type == OPERAND)
            printf(" %d ",temp->item+ seed);
        else
            printf(" %c ",(char)(temp->item));
        temp = temp->next;
    }
    printf("\n");
}

void insertNode(LinkedList *LLPtr, int item, enum ExpType type) {
    ListNode *newNode;
    newNode = malloc(sizeof(ListNode));
    if(newNode==NULL) exit(0);

    newNode->item = item;
    newNode->type = type;
    newNode->next = LLPtr->head;
    LLPtr->head=newNode;
    LLPtr->size++;
}

int deleteNode(LinkedList *LLPtr) {
    if(LLPtr==NULL || LLPtr->size==0){ //Queue is empty or NULL pointer
        return 0;
    }
    else{
       ListNode *temp = LLPtr->head;
       LLPtr->head = LLPtr->head->next;

       free(temp);
       LLPtr->size--;
       return 1;
    }
}

int isEmptyLinkedList (LinkedList ll) {
    if(ll.size==0) return 1;
    else return 0;
}

void removeAllNodes(LinkedList *LLPtr)
{
	while(deleteNode(LLPtr));
}
