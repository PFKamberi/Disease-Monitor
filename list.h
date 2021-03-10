/*File: list.h*/

#include "record.h"

#ifndef _LIST
#define _LIST

typedef struct lnode {
    Record record;
    struct lnode* next;
}lnode;

#endif

void init_list(lnode**);

void print_list(lnode*);

lnode* add(lnode** , char* , char* , char* , char* , char* , char* , char* );

int check_dublicates(lnode* , Record );

void free_list(lnode* );