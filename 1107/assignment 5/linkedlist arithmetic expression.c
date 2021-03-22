#include <stdio.h>
#include <stdlib.h>
#include <string.h>
           

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
  LinkedList store;
  store.head = NULL;
  store.size = 0;
  int p = strlen(infix); 
  while( p != 0)
  { // iterate over string   
    int x = abs(atoi(infix));
    if (x != 0)// if operand
    {
      insertNode(&store, x , OPERAND); 
      while ( x != 0) // for no of digits in X
      {
        x = x/10;
        for (int i = 0; i <= p; i++) // remove index from string
        {
          infix[i] = infix[i + 1];
        }
      } 
    }
    char temp = infix[0];
    if ((temp == '*') || ( temp == '/') || ( temp == '+')  || ( temp == '-') || ( temp == '(') || ( temp == ')') ) // if operator
    {
      insertNode(&store, temp, OPT);
      for (int i = 0; i <= p; i++) // remove from string
      {
        infix[i] = infix[i + 1];
      }
    }
  }

  while (isEmptyLinkedList(store) != 1)
  {
    if (store.head->type == OPERAND){
      int x = deleteNode(&store);
      insertNode(inExpLL, x,OPERAND);
    }
    else{
      int x = deleteNode(&store);
      insertNode(inExpLL, x,OPT);
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