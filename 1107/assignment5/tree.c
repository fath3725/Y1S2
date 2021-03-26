#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SIZE 200 //The number digit limitation

typedef struct _btnode{
	int item;
	struct _btnode *left;
	struct _btnode *right;
} BTNode;   // You should not change the definition of BTNode

typedef struct _node{
     BTNode* item;
     struct _node *next;
}StackNode;

typedef struct _stack{
   int size;
   StackNode *head;
}Stack;

void deleteTree(BTNode **root);

void createExpTree(BTNode** root,char* prefix);
void printTree(BTNode *node);
void printTreePostfix(BTNode *node);
double computeTree(BTNode *node);

void push(Stack *sPtr,  BTNode* item);
int pop(Stack *sPtr);
BTNode *peek(Stack s);
int isEmptyStack(Stack s);

int main()
{
    char prefix[SIZE];
    BTNode* root=NULL;

    //printf("Enter an prefix expression:\n");
    gets(prefix);

    createExpTree(&root, prefix);

    // printf("The Infix Expression:\n");
    printTree(root);
    printf("\n");
    //printf("The Postfix (Reverse Polish) Expression:\n");
    printTreePostfix(root);
    printf("\n");
    //printf("Answer ");
    printf("%.2f\n", computeTree(root));
    deleteTree(&root);
    return 0;
}

void createExpTree(BTNode** root,char* prefix)
{
 //Write your code here
 //insert each operatore as an internal node and operand as a leaf node
    Stack *s;//operator stack
    s->head = NULL;
    s->size = 0;

    Stack *p;//operand stack
    p->head = 0;
    p->size = 0;

    BTNode node;
    BTNode *newnode;
    *newnode = node;
    *root = newnode;

    int len = strlen(prefix);
    int multiplier = 1;
    int store = 0; // store value of digits
    
    for (int j = 0; j <= len; j++)
    {
      if(isdigit(prefix[j])) // this will keep running until encounter OPERAND
      { // convert inifx[j] from ascii
        store = store*multiplier+(prefix[j] - '0'); 
        multiplier *= 10;
      }
      else //if NOT digit
      {
        if (prefix[j] == ' ') continue; // ignore whitespace

        if (prefix[j] == '\0') // if end of string
        {
          while(!isEmptyStack(*s)){
            node.item = pop(s);
            push(p,newnode);
          }
        }
      
        if (prefix[j] == '+' || prefix[j] == '-' ) // lowest precedence
        {
          while (!isEmptyStack(*s) && peek(*s)->item != '+' && peek(*s)->item != '-'  )
          {
            node.item = pop(s);
            push(p,newnode);
          }
          node.item = prefix[j];
          push(s,newnode);
        }
        
        if (prefix[j] == '*' || prefix[j] == '/' ) // 2nd most precedence
        {
          while (!isEmptyStack(*s) && peek(*s)->item != '^')
          {
            node.item = pop(s);
            push(p,newnode);
          }
          node.item = prefix[j];
          push(s,newnode);
        }

        if ( prefix[j] == '^')// highest precedence
        {
          node.item = prefix[j];
          push(s,newnode);
        }
        if (prefix[j] == '(') // open bracket
        {
          node.item = prefix[j];
          push(s,newnode);
        }
        if (prefix[j] == ')') // close bracket
        {
          while (!isEmptyStack(*s) && peek(*s)->item != '(')
          {
            node.item = pop(s);
            push(p,newnode);
          }
          pop(s);
        }

        if (store != 0) // value of digit
        { 
          node.item = store;
          push(p,newnode);
          store = 0;
          multiplier = 1; // reset values
          // next node
        }
      }
    }
}

void printTree(BTNode *node){
    //Write your code here
    // print in order, left,root,right\
    printTree(node->left);
    if (node == NULL)  return;
    else
    {
      if (isdigit(node->item) )
      { // if digit
      printf("%d", node->item);
      }
      else
      {
        printf("%c", node->item);
      }
    }
    printTree(node->right);
}


void printTreePostfix(BTNode *node){
   //Write your code here
   // print in post order, root left right
    if (node == NULL)  return;
    else
    {
      if (isdigit(node->item) )
      { // if digit
      printf("%d", node->item);
      }
      else
      {
        printf("%c", node->item);
      }
    }

    printTree(node->left);
    printTree(node->right);
}

double computeTree(BTNode *node){
//Write your code here

}

void push(Stack *sPtr, BTNode *item){
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

BTNode *peek(Stack s){
    return s.head->item;
}

int isEmptyStack(Stack s){
     if(s.size == 0) return 1;
     else return 0;
}

void deleteTree(BTNode **root){
    BTNode* temp;
    if(*root !=NULL)
    {
        temp = (*root)->right;
        deleteTree(&((*root)->left));
        free(*root);
        *root = NULL;
        deleteTree(&temp);
    }
}