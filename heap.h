

#ifndef _HEAP
#define _HEAP

typedef struct hnode{
    char* key; //disease or country
    int count;
    struct hnode* left;//1
    struct hnode* right;//0
    struct hnode* parent;
}hnode;


typedef struct heap{
    struct hnode* root;
    struct hnode* last;

}heap;


heap*  heap_init(); 
void  move_up(heap* , hnode* );
void heap_remove(heap*,hnode* );
void heap_insert(heap* , char* , int );
void replace_node (heap*, hnode *, hnode *);
hnode* get_first(heap *);
void print_heap(hnode* , int );
void free_heap(hnode* );
#endif
