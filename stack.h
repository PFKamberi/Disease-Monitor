/*File: stack.h*/

#include "tree.h"

#ifndef _STACK
#define _STACK

typedef struct stack_node { 
  node* tree; 
  struct stack_node *next; 

} stack_node; 

void push(stack_node** , node* );
node* pop(stack_node** );
#endif

