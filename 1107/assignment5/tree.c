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
 //Write y
      
    //insert each operatore as an internal node and operand as a leaf node
    Stack s;
    s.head = NULL;
    s.size = 0;
    BTNode *node, *node_left, *node_right;
    
    int len = strlen(prefix);// reverse string
    int k = len;
    for(int i = 0; i < len; i++) 
    {
        char temp = prefix[k];
        prefix[k] = prefix[i];
        prefix[i] = temp;
        k--;
        if(k == (len / 2))
        {
            break;
        }
    } // string reversed WORKS GOOD
    int store = 0;
    int multiplier = 1;

    for (int i=1; i <= len;i++)
    {
        if (isdigit(prefix[i]))
        {
            while (isdigit(prefix[i]))
            {
                store = store + ((prefix[i]-'0')*multiplier);
                i++;    
                multiplier *= 10;
            }
            node = malloc(sizeof(BTNode));
            node->item = store;
            node->left = NULL;
            node->right = NULL;
            push(&s, node);
            store = 0; // reset for next digits
            multiplier=1;
        }

        else if (prefix[i]==' ') continue;
    
        else 
        {
            node = malloc(sizeof(BTNode));
            node->item = prefix[i];
 
            // Pop left node
            node_left = peek(s); 
            pop(&s);      
            
            // pop right node
            node_right = peek(s);
            pop(&s);
 
            //  make them children
            node->left = node_left;
            node->right = node_right;
 
            // put it back into the stack
            push(&s, node);
        }
    }
    node= peek(s);
    pop(&s);
    (*root) = node;

}

void printTree(BTNode *node){
    //Write your code here
    // print left rootright
    if (node == NULL) return;
    printTree(node->left); 
        
    if (node->left==NULL && node->right==NULL) 
    {
          printf("%d ", node->item);
    }
    else
    {
          printf("%c ", node->item);
    } 
    printTree(node->right); 
}


void printTreePostfix(BTNode *node){
   //Write your code here
   // print in post order, left right root
    if (node == NULL) return;
    
    printTreePostfix(node->left); 
    printTreePostfix(node->right); 
    if (node->left==NULL && node->right==NULL) //if digit
    {
          printf("%d ", node->item);
    }
    else 
    {
          printf("%c ", node->item);
    }
}

double computeTree(BTNode *node){
//Write your code here
    if (node->right == NULL && node->left == NULL) return node->item;
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
