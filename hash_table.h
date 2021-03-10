/*File: hash_table.h*/

#include "record.h"
#include "tree.h"

#ifndef _HASH
#define _HASH


struct ht_bucket{
    int count; // numberof bucket entries
    void* bucket; //bucket memory for storing entries
    //struct ht_bucket* next;
};

typedef struct ht_bucket ht_bucket;

typedef struct {
    char** key; //country  or disease
    node*  tree; // tree of records
}Entry;

int hash_function(char* , int);

ht_bucket** ht_init(int );

int search_key(char* , void* , int );

ht_bucket** ht_insert(ht_bucket** , int , Record* , char* , int);

void free_ht(ht_bucket** , int );

void ht_print(ht_bucket** , int );

#endif