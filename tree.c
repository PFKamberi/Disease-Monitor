/*File tree.c*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "record.h"
#include "tree.h"
#include "list.h"
#include "stack.h"
#include "heap.h"


/*********** avl tree manipulation functions ***********/

node* new_node(Record* r){ //creates new avl tree node

    node* n = (node*)malloc(sizeof(node));
    if(!n){
      perror("Malloc error while creating new tree node");
      exit(EXIT_FAILURE);
    }

    n->record = r;
    n->height = 1;
    n->left = NULL;
    n->right = NULL;
    return n;
}

int max(int a, int b){ return a > b ? a : b; }

int height(node* n){ return n ? n -> height : 0; }

void new_height(node* n){ n->height = 1 + max(height(n->left), height(n->right)); } //recalulates height after rotations

node* right_rotation(node* n){
    
    node* temp = n->left;

    n->left = temp->right;
    temp->right = n;

    new_height(n);
    new_height(temp);

    return temp;
}

node* left_rotation(node* n){

    node* temp = n->right;
    n->right = temp->left;
    temp->left = n;

    new_height(n);
    new_height(temp);

    return temp;
}

node* rebalance(node* n){
    
    new_height(n);

    if ( height(n->left) - height(n->right) == 2 ){
        if ( height(n->left->right) > height(n->left->left) )
            n->left = left_rotation(n->left);
        return right_rotation(n);
    }
    else if ( height(n->right) - height(n->left) == 2 ){
        if ( height(n->right->left) > height(n->right->right) )
            n->right = right_rotation(n->right);
        return left_rotation(n);
    }

    return n;
}


node* insert(node* n, Record* r){
    if (!n){ // create new tree root
        return new_node(r);
    }
    if ( datecmp(*r, *(n->record))  <= 0  ){ // insert left subtree
            n->left = insert(n->left, r);}
    else if ( datecmp(*r, *(n->record))  > 0   ) {// insert right subtree
            n->right = insert(n->right, r);}
    return rebalance(n);
}


void print_tree(node*root, int space) { 

    if (root == NULL) {
        //printf("%s\n", "NULL");
        return; 
    }
  
    space += 10; //COUNT = 10
  
    // Process right child first 
    print_tree(root->right, space); 

    printf("\n"); 
    for (int i = 10; i < space; i++) 
        printf(" "); 

    //print_record(root->record);
    printf("%s:%s:%s\n", root->record->entryDate ,root->record->exitDate, root->record->recordID);

    // Process left child 
    print_tree(root->left, space); 
} 

void free_tree(node* n){
    if ( !n )
        return;

    free_tree(n->left);
    free_tree(n->right);
    free(n);
}

/*********** functions used at queries ***********/


int count_tree_nodes(node *tree){
    int node_count =  1;             
    if (!tree)
        return 0;
    else{
        node_count += count_tree_nodes(tree->left);
        node_count += count_tree_nodes(tree->right);
        return node_count;
    }
}

int datecomp(char* date_1, char* date_2){


    /*if date_1 == date_2 return 0
      if date_1 > date_2 return >0
      if date_1 < date_2 return < 0
    */

    char* str1 = NULL;
    char* str2 = NULL;
    char* s1 = malloc((strlen(date_1) + 1 ) * sizeof(char));
    char* s2 = malloc((strlen(date_2) + 1 ) * sizeof(char));
    int  date1[3], date2[3];

    strcpy(s1,date_1);

    str1 = strtok(s1,"-");
    int i = 0;
    while(str1 != NULL){
        date1[i] = atoi(str1);
        str1 = strtok(NULL,"-");
        i++;
    }

    strcpy(s2,date_2);
   
    str2 = strtok(s2,"-");
    i = 0;
    while(str2 != NULL){
        date2[i] = atoi(str2);
        str2 = strtok(NULL,"-");
        i++;

    }

    free(s1);
    free(s2);

    if(date1[2] == date2[2]){
        if(date1[1] == date2[1]){
            return (date1[0] - date2[0]);
        }else{
            return (date1[1] - date2[1]);
        }        
    }
    else{
        return (date1[2] - date2[2]);
    }

}

int count_in_range(node *tree, char* date1, char* date2) { 
    
    if (!tree) return 0;
  
    // If current node->record->entryDate is in range [date1,date2] add it in count and recur for left and right child nodes
    if (datecomp(get_entryDate(tree->record),date2) <= 0 && datecomp(get_entryDate(tree->record),date1) >= 0) 
         return 1 + count_in_range(tree->left, date1, date2) + 
                    count_in_range(tree->right, date1, date2); 
  
    // If current node->record->entryDate  < date1, then recur for right child node
    else if (datecomp(get_entryDate(tree->record),date1) < 0) 
         return count_in_range(tree->right, date1, date2); 
  
    // Else recur for left child  node
    else return count_in_range(tree->left, date1, date2); 
} 



int disease_count_in_range(node* tree, char* disease, char* date1, char* date2) { 
  
    int count = 0;
    node *current = tree; 
    stack_node *s = NULL;  
    int done = 0; 
  
    while (!done) { 

        if(current !=  NULL) { // reach leftmost node of current node

        push(&s, current); // push pointer to the stack                                             
        current = current->left; // traverse the node's left subtree 
    
        } 
        else{ 
      
            if (s){ // backtrack from the empty subtree and pop a tree node from the stack

                current = pop(&s); 
        
                if (datecomp(get_entryDate(current->record),date2) <= 0 && datecomp(get_entryDate(current->record),date1) >= 0 && !strcmp(disease,get_diseaseID(current->record))) 
                    count++; // If current node->record->entryDate is in range [date1,date2] increment count 

                current = current->right; // after we have visited the node and its left subtree, visit right subtree
      
            } 
            else // the stack is empty, leave loop
                done = 1;  
        } 

    } 

    return count;
}    

int disease_count(node* tree, char* disease) { 
  
    int count = 0;
    node *current = tree; 
    stack_node *s = NULL;  
    int done = 0; 
  
    while (!done) { 

        if(current !=  NULL) { // reach leftmost node of current node

        push(&s, current); // push pointer to the stack                                             
        current = current->left; // traverse the node's left subtree 
    
        } 
        else{ 
      
            if (s){ // backtrack from the empty subtree and pop a tree node from the stack

                current = pop(&s); 
        
                if (!strcmp(disease,get_diseaseID(current->record))) 
                    count++; // If current node->record->entryDate is in range [date1,date2] increment count 

                current = current->right; // after we have visited the node and its left subtree, visit right subtree
      
            } 
            else // the stack is empty, leave loop
                done = 1;  
        } 

    } 

    return count;
}   


int country_count_in_range(node* tree, char* country, char* date1, char* date2) { 
  
    int count = 0;
    node *current = tree; 
    stack_node *s = NULL;  
    int done = 0; 
  
    while (!done) { 

        if(current !=  NULL) { // reach leftmost node of current node

        push(&s, current); // push pointer to the stack                                             
        current = current->left; // traverse the node's left subtree 
    
        } 
        else{ 
      
            if (s){ // backtrack from the empty subtree and pop a tree node from the stack

                current = pop(&s); 
        
                if (datecomp(get_entryDate(current->record),date2) <= 0 && datecomp(get_entryDate(current->record),date1) >= 0 && !strcmp(country,get_country(current->record))) 
                    count++; // If current node->record->entryDate is in range [date1,date2] increment count 

                current = current->right; // after we have visited the node and its left subtree, visit right subtree
      
            } 
            else // the stack is empty, leave loop
                done = 1;  
        } 

    } 

    return count;
}    

int country_count(node* tree, char* country) { 
  
    int count = 0;
    node *current = tree; 
    stack_node *s = NULL;  
    int done = 0; 
  
    while (!done) { 

        if(current !=  NULL) { // reach leftmost node of current node

        push(&s, current); // push pointer to the stack                                             
        current = current->left; // traverse the node's left subtree 
    
        } 
        else{ 
      
            if (s){ // backtrack from the empty subtree and pop a tree node from the stack

                current = pop(&s); 
        
                if (!strcmp(country,get_country(current->record))) 
                    count++; // If current node->record->entryDate is in range [date1,date2] increment count 

                current = current->right; // after we have visited the node and its left subtree, visit right subtree
      
            } 
            else // the stack is empty, leave loop
                done = 1;  
        } 

    } 

    return count;
}   





node* search_recordID(node* tree, char* recordID) {


    node *current = tree;
    node *a = NULL;
    stack_node *s = NULL;
    int done = 0;

    while (!done){
    
        if(current !=  NULL){ // reach leftmost node of current node

        push(&s, current); // push pointer to the stack 
        current = current->left; // traverse the node's left subtree
    
        }
        else{
      
            if (s){ // backtrack from the empty subtree and pop a tree node from the stack

                current = pop(&s);
                if (!strcmp(recordID,(current->record)->recordID)){
                   // a =  current; //record found
                    return current;
                }

                current = current->right; // after we have visited the node and its left subtree, visit right subtree
            }
        
            else // the stack is empty, leave loop
                done = 1;
        }

    } 

    return a; // record not found
}

int stILL(node* tree){ // still ill 

    int count = 0;
    node *current = tree; 
    stack_node *s = NULL;  
    int done = 0; 
  
    while (!done){ 

        if(current !=  NULL){ // reach leftmost node of current node

            push(&s, current); // push pointer to the stack                                                     
            current = current->left;   // traverse the node's left subtree 
        
        }
        else{ 

            if (s){ // backtrack from the empty subtree and pop a tree node from the stack

                current = pop(&s); 
                if ((current->record)->exitDate[0] == '-'){
                    count++; // If current node->record->exitDate == '-'  increment count 
                }
  
                current = current->right; // after we have visited the node and its left subtree, visit right subtree
            } 
            else // the stack is empty, leave loop
                done = 1;  
        } 
    }

    return count;

}



void topk(node* tree, int key_type, int k){ // 1 = disease, 0 = country 

    lnode* head;
    init_list(&head);
    int count = 0;
    node *current = tree; 
    stack_node *s = NULL;  
    int done = 0; 
  
    while (!done){ 

        if(current !=  NULL){ // reach leftmost node of current node

            push(&s, current); // push pointer to the stack                                                     
            current = current->left;   // traverse the node's left subtree 
        
        }
        else{ 

            if (s){ // backtrack from the empty subtree and pop a tree node from the stack

                current = pop(&s); 
                if(key_type){

                    lnode * temp;
                    temp = head;
                    int found = 0;

                    while(temp){
                        if(strcmp(current->record->diseaseID,temp->record.diseaseID) == 0){
                            found =  1; 
                            break;
                        } 
                        temp = temp->next;
                    }
                    
                    if(!found){
                        add(&head,current->record->recordID,current->record->patientFirstName,current->record->patientLastName, current->record->diseaseID,current->record->country,current->record->entryDate,current->record->exitDate);
                        count++;
                    }
                }else{
                    lnode * temp;
                    temp = head;
                    int found = 0;
                    while(temp){
                        if(strcmp(current->record->country,temp->record.country) == 0){
                            found =  1; 
                            break;
                        } 
                        temp = temp->next;
                    }

                    if(!found){
                        add(&head,current->record->recordID,current->record->patientFirstName,current->record->patientLastName, current->record->diseaseID,current->record->country,current->record->entryDate,current->record->exitDate);    
                        count++;
                    }
                }
  
                current = current->right; // after we have visited the node and its left subtree, visit right subtree
            } 
            else // the stack is empty, leave loop
                done = 1;  
        } 
    }


    heap* h  = heap_init();

    if(key_type){//disease

        lnode*  temp;
        temp = head;
        heap_insert(h,temp->record.diseaseID,disease_count(tree,temp->record.diseaseID));
        temp = temp->next;
    
    
        while(temp){
            heap_insert(h,temp->record.diseaseID,disease_count(tree,temp->record.diseaseID));
            temp = temp->next;
        }

        //print_heap(h->root,0);
        if(k <= count ){

            for(int i = 0; i < k; i++){

                hnode* n = get_first(h);
                printf("%s : %d\n", n->key, n->count);
                heap_remove(h,h->root);

            }
         

        }else{
           
             for(int i = 0; i < count; i++){

                hnode* n = get_first(h);
                printf("%s : %d\n", n->key, n->count);
                heap_remove(h,h->root);

            }


        }


    }else{


        lnode * temp;
        temp = head;
        heap_insert(h,temp->record.country,country_count(tree,temp->record.country));
        temp = temp->next;
    
    
        while(temp){
            heap_insert(h,temp->record.country,country_count(tree,temp->record.country));
            temp = temp->next;
        }


        if(k <= count ){

            for(int i = 0; i < k; i++){

                hnode* n = get_first(h);
                printf("%s : %d\n", n->key, n->count);
                heap_remove(h,h->root);

            }
         

        }else{
           
             for(int i = 0; i < count; i++){

                hnode* n = get_first(h);
                printf("%s : %d\n", n->key, n->count);
                heap_remove(h,h->root);

            }


        }



    }


    free_list(head);
    free_heap(h->root);
    free(h);

}

void topk_dates(node* tree, int key_type, int k, char* date1, char* date2){ // 1 = disease, 0 = country 

    lnode* head;
    init_list(&head);
    int count = 0;
    node *current = tree; 
    stack_node *s = NULL;  
    int done = 0; 
  
    while (!done){ 

        if(current !=  NULL){ // reach leftmost node of current node

            push(&s, current); // push pointer to the stack                                                     
            current = current->left;   // traverse the node's left subtree 
        
        }
        else{ 

            if (s){ // backtrack from the empty subtree and pop a tree node from the stack

                current = pop(&s); 
                if(key_type){

                    lnode * temp;
                    temp = head;
                    int found = 0;

                    while(temp){
                        if(strcmp(current->record->diseaseID,temp->record.diseaseID) == 0){
                            found =  1; 
                            break;
                        } 
                        temp = temp->next;
                    }
                    
                    if(!found){
                        add(&head,current->record->recordID,current->record->patientFirstName,current->record->patientLastName, current->record->diseaseID,current->record->country,current->record->entryDate,current->record->exitDate);
                        count++;
                    }
                }else{
                    lnode * temp;
                    temp = head;
                    int found = 0;
                    while(temp){
                        if(strcmp(current->record->country,temp->record.country) == 0){
                            found =  1; 
                            break;
                        } 
                        temp = temp->next;
                    }

                    if(!found){
                        add(&head,current->record->recordID,current->record->patientFirstName,current->record->patientLastName, current->record->diseaseID,current->record->country,current->record->entryDate,current->record->exitDate);    
                        count++;
                    }
                }
  
                current = current->right; // after we have visited the node and its left subtree, visit right subtree
            } 
            else // the stack is empty, leave loop
                done = 1;  
        } 
    }


    heap* h  = heap_init();

    if(key_type){//disease

        lnode*  temp;
        temp = head;
        heap_insert(h,temp->record.diseaseID,disease_count_in_range(tree,temp->record.diseaseID,date1,date2));
        temp = temp->next;
    
    
        while(temp){
            heap_insert(h,temp->record.diseaseID,disease_count_in_range(tree,temp->record.diseaseID,date1,date2));
            temp = temp->next;
        }

        //print_heap(h->root,0);
        if(k <= count ){

            for(int i = 0; i < k; i++){

                hnode* n = get_first(h);
                printf("%s : %d\n", n->key, n->count);
                heap_remove(h,h->root);

            }
         

        }else{
           
             for(int i = 0; i < count; i++){

                hnode* n = get_first(h);
                printf("%s : %d\n", n->key, n->count);
                heap_remove(h,h->root);

            }


        }


    }else{


        lnode * temp;
        temp = head;
        heap_insert(h,temp->record.country,country_count_in_range(tree,temp->record.country,date1,date2));
        temp = temp->next;
    
    
        while(temp){
            heap_insert(h,temp->record.country,country_count_in_range(tree,temp->record.country,date1,date2));
            temp = temp->next;
        }


        if(k <= count ){

            for(int i = 0; i < k; i++){

                hnode* n = get_first(h);
                printf("%s : %d\n", n->key, n->count);
                heap_remove(h,h->root);

            }
         

        }else{
           
             for(int i = 0; i < count; i++){

                hnode* n = get_first(h);
                printf("%s : %d\n", n->key, n->count);
                heap_remove(h,h->root);

            }


        }



    }

    
    free_list(head);
    free_heap(h->root);
    free(h);
}

