#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heap.h"

heap* heap_init(){
    heap* h;
    h = malloc(sizeof(heap));
    h->root = NULL;
    h->last = NULL;
}



void heap_insert(heap* h, char* key, int count){
    
     hnode* node = malloc(sizeof(hnode));
     node->key = malloc((strlen(key) + 1) *sizeof(char));
     strcpy(node->key, key);
     node->count = count;
    
    if (!h->root) {  // insert to root
        h->root = node;
        h->last = node;
        node->parent = NULL;
        node->left = NULL;
        node->right = NULL;
        return;
    }
    
    // find the node to insert to
    
    hnode* current = h->last; 
    // go as left as possible while parent exists and current is parent's right child
    while (current->parent && current == current->parent->right) { 
        current = current->parent;
    }
    
    if (current->parent) {
        if (current->parent->right) {
            //Attach the new node to the leftmost node of the parent's right subtree.
            current = current->parent->right;
            while (current->left) {
                current = current->left;
            }
        } else {
            // parent has no right child. This can only happen when the last node is a right child. So attach the new node to its parent.
            current = current->parent;
        }
    } else {
        // have no parent, attach the new node to a new level. Go left to get the node where we'll attach the new node.
        while (current->left) {
            current = current->left;
        }
    }
  
    
    // attach new node
    // the new node becomes the new last node
    h->last = node;
    if(!current->left){
        current->left = node;
    }else{
        current->right = node;
    }
    node->parent = current;
    node->right = NULL;
    node->left = NULL;
    
    // restore heap property
    while (node->parent && node->parent->count <= node->count) {
        move_up(h, node);
    }
    
    
}


void  move_up(heap *h, hnode *n){
    
    hnode *p = n->parent;
    
    if (p->parent) {

        if(p == p->parent->right)
            p->parent->right = n;
        else
            p->parent->left = n;

    } else {
        h->root = n;
    }
    n->parent = p->parent;
    
    hnode* c = NULL;
    if(n == p->right){
        
        c = p->left;

        p->left = n->left;
        if (p->left) {
            p->left->parent = p;
        }
    
        p->right = n->right;
        if (p->right) {
            p->right->parent = p;
        }

        n->right = p;
        p->parent = n;
    
        n->left = c;
        if (c) {
            c->parent = n;
        }
    
        if (n == h->last) {
            h->last = p;
        }


    }
    else{

        c = p->right;

        p->left = n->left;
        if (p->left) {
            p->left->parent = p;
        }
    
        p->right = n->right;
        if (p->right) {
            p->right->parent = p;
        }

        n->left = p;
        p->parent = n;
    
        n->right = c;
        if (c) {
            c->parent = n;
        }
    
        if (n == h->last) {
            h->last = p;
        }   

    }
      
}





void replace_node (heap *h, hnode *d, hnode *s){
    if (d->parent) { //d is not root
        if(d = d->parent->right){ //d is right child
            d->parent->right = s; 
        }
        else{ //d is left child
            d->parent->left = s;
        }

    } else { //d is root
        h->root = s;
    }
    s->parent = d->parent;
    
    s->left = d->left;
    if (s->left) {
        s->left->parent = s;
    }
    
    s->right = d->right;
    if (s->right) {
        s->right->parent = s;
    }

}


void heap_remove(heap* h, hnode *node){
    
    if (!node->parent && !node->left && !node->right) {        
        return;
    }
    
    // find the node before the last node
    hnode* current = h->last;
    while (current->parent && current == current->parent->left) { // current has a parent and current is the left child of its parent
        current = current->parent; //move to parent(move up as left as possible)
    }
    if (current->parent) { //we've not reached the root
     
        current = current->parent->left; //current is parent's right child. Move to the left child of parent
        while (current->right) { //after moving up as left as possible move down as right as possible
            current = current->right;
        }
    } else { //we've reached the root
        while (current->right) { //after moving up as left as possible move down as right as possible
            current = current->right;
        }
    }
    
    // disconnect last
    if(h->last == h->last->parent->right) //last is a right child
        h->last->parent->right = NULL;
    else
        h->last->parent->left = NULL; //last is a left child
    
    if (node == h->last) {
        // delete last set new last
        h->last = current;
        free(current);
    } else {
        // don't delete last, but move last to node's place
        hnode* temp = h->last;
        replace_node(h, node, temp);

        if (node != current) {
            h->last = current; 
        }
        
        // restore heap property
        if(temp->parent &&  temp->count >= temp->parent->count) {
        
            do {
                               move_up(h, temp);

            } while(temp->parent && temp->count >= temp->parent->count);
        
        }else {

            while (temp->left || temp->right) {

                //int side = (temp->right && (temp->left->count < temp->right->count));

                if(temp->right && (temp->left->count < temp->right->count)){

                    if (temp->count <= temp->right->count) {
                        move_up(h, temp->right);
                    } else {
                        break;
                    }

                }else{

                    if (temp->count <= temp->left->count) {
                        move_up(h, temp->left);
                    } else {
                        break;
                    }


                }


                
            }
        }

        free(node->key);
        free(node);
    }

   
}


void print_heap(hnode* h, int space) { 

    if (h == NULL) {
        return; 
    }
  
    space += 10; 

    print_heap(h->right, space); 


    printf("\n"); 
    for (int i = 10; i < space; i++) 
        printf(" "); 
    printf("%s : %d\n", h->key, h->count);
  
      print_heap(h->left, space); 
    
} 

void free_heap(hnode* h){
    if ( !h ){
        return;
    }

    free_heap(h->left);
    free_heap(h->right);
    free(h->key);
    free(h);
}


hnode * get_first(heap *h){ return h->root; }

/*int main(){
    
    heap* h  = heap_init();
    heap_insert(h,"a",8);
    heap_insert(h,"b",7);
    heap_insert(h,"c",6);
    heap_insert(h,"d",4);
    heap_insert(h,"e",5);
    heap_insert(h,"f",3);
    heap_insert(h,"g",0);
    heap_insert(h,"h",1);
    print_heap(h->root,0);

    for(int i = 0; i < 8; i++){
        printf("%s\n", "********");
        printf("%s %d\n", h->root->key, h->root->count );
        print_heap(h->root,0);
        heap_remove(h,h->root);
        
        printf("%s\n", "********");
    }



    printf("%s\n", "**********");
    free_heap(h->root);
    free(h);


    return 0;
}
*/