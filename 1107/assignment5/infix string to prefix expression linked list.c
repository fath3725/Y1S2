#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SIZE 80 //The size of the array

enum ExpType {OPT,OPERAND};

typedef struct _stackNode{
    char item;
    struct _stackNode *next;
}StackNode;

typedef struct _stack{
   int size;
   StackNode *head;
}Stack;

void push(Stack *sPtr, char item);
int pop(Stack *sPtr);
char peek(Stack s);
int isEmptyStack(Stack s);

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

void insertNode(LinkedList *llPtr, int item,enum ExpType type);
int deleteNode(LinkedList *llPtr);
void removeAllNodes(LinkedList *llPtr);
int isEmptyLinkedList (LinkedList ll);


void in2PreLL(char* infix, LinkedList *inExpLL);

void printExpLL(LinkedList inExp);

int main()
{
    char infix[SIZE];

    //printf("Enter an infix expression:\n");
    gets(infix);

    LinkedList inExpLL;
    inExpLL.head = NULL;
    inExpLL.size = 0;

    in2PreLL(infix, &inExpLL);

    printExpLL(inExpLL);

    removeAllNodes(&inExpLL);
    return 0;
}

void in2PreLL(char* infix, LinkedList *inExpLL)
{
  //Write your code here
    // infix is left root right
    // prefix is root left right
    if (infix[0] == '\0') return;

    int len = strlen(infix);
    // reverse string 92+(86-71)*(64/(53-48)+39)
    for(int i = 0; i < len/2; i++) 
    {
        char temp = infix[i];
        infix[i] = infix[len-i-1];
        infix[len-i-1] = temp;
        
    } // string reversed WORKS GOOD becomes )93+)84-35(/46(*)17-68(+29
    // must reverse string cos associativity l 2 r

    Stack s;
    s.head = NULL;
    s.size = 0;
    int length = strlen(infix);

    int multiplier = 1;
    int store = 0; // store value of digits

    for (int j = 0; j <= length; j++)
    {
      if(isdigit(infix[j])) // this will keep running until encounter OPERAND
      { // IF digit must reverse digits
        // convert inifx[j] from ascii
        store = store+multiplier*(infix[j] - '0'); 
        multiplier *= 10;
      }
      else { // IF NOT digit, possible: + - / * ) ( \0 ^ , if operand put in stack

        // print numbers
        if (store != 0)
        {
          insertNode(inExpLL,store,OPERAND);
          multiplier = 1;
          store = 0; // store value of digits
        }
        
        if (infix[j] == '\0' ){ // if end of string, pop everything in stack then quit
          while(!isEmptyStack(s))
          {
            insertNode(inExpLL,peek(s),OPT);
            pop(&s);
          }
        }

        if (infix[j] == '+' || infix[j] == '-' ) // check precedance
        {
          while(!isEmptyStack(s) && peek(s)!= '+' && peek(s)!= '-' && peek(s) != ')') 
          {
            insertNode(inExpLL,peek(s),OPT);
            pop(&s);
          }
          push(&s,infix[j]);
        }

        if (infix[j] == '/' || infix[j] == '*' ) // need check precedance
        {
            while(!isEmptyStack(s) && peek(s) == ')' &&peek(s) == '^')
            {
                insertNode(inExpLL,peek(s),OPT);
                pop(&s);
            }
          push(&s,infix[j]);
        }
    
        if (infix[j] == ')') // close bracket just add to stack
        {
          push(&s, infix[j]);
        }

        if (infix[j] == '(') // open bracket check for close bracket
        {
          while(!isEmptyStack(s) && peek(s) != ')'){
            insertNode(inExpLL,peek(s),OPT);
            pop(&s);
          }
          pop(&s); // remove close bracket too
        }
      }
    }
}


void printExpLL(LinkedList inExpLL)
{
    ListNode* temp = NULL;
    temp = inExpLL.head;
    while(temp!= NULL){
        if(temp->type == OPERAND)
            printf(" %d ",temp->item);
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
    if(LLPtr==NULL || LLPtr->size==0){
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

void push(Stack *sPtr, char item){
    StackNode *newNode;
    newNode = malloc(sizeof(StackNode));
    newNode->item = item;
    newNode->next = sPtr->head;
    sPtr->head = newNode;
    sPtr->size++;
}

int pop(Stack *sPtr){
    if(sPtr == NULL || sPtr->head == NULL){
        return 0;
    }
    else{
       StackNode *temp = sPtr->head;
       sPtr->head = sPtr->head->next;
       free(temp);
       sPtr->size--;
       return 1;
    }
}

char peek(Stack s){
    return s.head->item;
}

int isEmptyStack(Stack s){
     if(s.size == 0) return 1;
     else return 0;
}