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
    Stack *p;// stack
    p->head = 0;
    p->size = 0;

    int multiplier = 1;
    int store = 0; // store value of digits
    int k = strlen(prefix);

    for ( int j = k; j != -1; j--)//traverse from back instead of reversing string faster
    {
     if (prefix[j] == ' ') continue; // if whitespace ignore

     if(isdigit(prefix[j])){
      store = store + multiplier*(prefix[j] - '0'); 
      multiplier *=10;      
     } 
     else{
        BTNode *newnode = malloc(sizeof(BTNode));
        newnode->left = NULL; newnode->right = NULL;  // initialise nodes
        if (store != 0){ //if digit
         newnode->item= store;
         push(p,newnode);
        }
        else // if operator
        {
          newnode->item = prefix[j];
          newnode->left = peek(*p);
          pop(p);
          newnode->right = peek(*p);
          pop(p);
          push(p, newnode);
        }
        *root = peek(*p);
     }
    }

}

void printTree(BTNode *node){
    //Write your code here
    // print left rootrigh
   if (node == NULL) { 
        return; 
    } 
    else { 
        printTree(node->left); 
        
        if (node->left==NULL && node->right==NULL) {
          printf("%d ", node->item);
        }
        else{
          printf("%c ", node->item);
        } 
        printTree(node->right); 
    }
}


void printTreePostfix(BTNode *node){
   //Write your code here
   // print in post order, left right root
   if (node == NULL) { 
        return; 
    } 
    else { 
        printTreePostfix(node->left); 
        printTreePostfix(node->right); 
        if (node->left==NULL && node->right==NULL) //if digit
        {
          printf("%d ", node->item);
        }
        else {
          printf("%c ", node->item);
        }
    } 
}

double computeTree(BTNode *node){
//Write your code here
  if (node->right == NULL && node->left == NULL){
    return node->item;
  }
  double l = computeTree(node->left);
  double r = computeTree(node->right);

  if (node->item == '+') return l+r;
  if (node->item == '-') return l-r;
  if (node->item == '/') return l/r;
  if (node->item == '*') return l*r;
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
