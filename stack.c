/*File: stack.c*/

#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "stack.h"

void push(stack_node** stack, node* tree) { 
 
  stack_node* new__stack_node = (stack_node*)malloc(sizeof(stack_node)); 
  
  if(!new__stack_node){ 
     perror("Stack Overflow"); 
     exit(EXIT_FAILURE); 
  }             
  
  new__stack_node->tree  = tree; 
  new__stack_node->next = *stack;    
  *stack = new__stack_node; 
} 

node* pop(stack_node** stack){
  node* n; 
  stack_node* top; 
  
  if(!stack){ 
    perror("Stack Underflow"); 
    exit(EXIT_FAILURE); 
  } 
  else{ 
    
    top = *stack; 
    n = top->tree; 
    *stack = top->next; 
    free(top); 
    return n; 
  
  } 

}



 
  

