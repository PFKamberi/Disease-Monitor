/*File: hash_table.c*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tree.h"
#include "list.h"
#include "record.h"
#include "hash_table.h"


/********** helper functions **********/

int hash_function(char* str, int size){
    int result = 0;
    int length = strlen(str);
    for(int i = 0; i < length; i++) result += str[i] - '0';
    
    return result%size;
}

int search_key(char* key, void* bucket, int count){

    
    Entry entry;
    char* str;

    for(int i = 0; i < count; i++){
        memmove(&entry, bucket + sizeof(ht_bucket*) + sizeof(Entry)*i, sizeof(Entry));
        if(!strcmp(*(entry.key),key))
            return i;
    }

    return -1;

}

/********** hash table manipulation functions **********/

ht_bucket** ht_init(int size){
    ht_bucket** hash_table = malloc(size*sizeof(ht_bucket*));
    for(int i = 0; i < size; i++){
        hash_table[i] = malloc(sizeof(ht_bucket));
        hash_table[i]->count = 0;
        hash_table[i]->bucket = NULL;
    }

    return hash_table;
}

ht_bucket** ht_insert(ht_bucket** hash_table, int size, Record* record, char* key, int buckets){//to record to pairnw apo tin lista

    Entry entry;
    void* bucket;
    int entries_per_bucket = (size - sizeof(ht_bucket*))/sizeof(Entry);
    int hash_value = hash_function(key,buckets);
    int index;

    if(hash_table[hash_value]->count == 0){ // no entry yet in the bucket

        hash_table[hash_value]->bucket = malloc(size);

        entry.key = (char**)malloc(sizeof(char*)); 
        if(!entry.key){
            perror("Malloc error while allocating memory for entry's key");
            exit(EXIT_FAILURE);
        }
        *(entry.key) = key;
        entry.tree = NULL;
        entry.tree = insert(entry.tree,record); //insert record in the enrty's tree

        //insert new entry in the first available spot ( = 0)
        ht_bucket* next = NULL;
        memmove(hash_table[hash_value]->bucket,&next, sizeof(ht_bucket*));
        memmove(hash_table[hash_value]->bucket + sizeof(ht_bucket*), &entry, sizeof(Entry));

        //increase count
        hash_table[hash_value]->count += 1;

    }else{ //at least one entry found in the bucket
        
        if(hash_table[hash_value]->count < entries_per_bucket){ // there's enough space available to store a new entry
       
            index = search_key(key,hash_table[hash_value]->bucket,hash_table[hash_value]->count);
            
            if(index == -1){ // key not in the bucket
      
                //create new entry with the given key and insert record in the enrty's tree
                entry.key = (char**)malloc(sizeof(char*)); 
                if(!entry.key){
                    perror("Malloc error while allocating memory for entry's key\n");
                    exit(EXIT_FAILURE);
                }
                *(entry.key) = key;
                entry.tree = NULL;
                entry.tree = insert(entry.tree,record);
                
                //insert new entry in the first available spot ( = count)
                memmove(hash_table[hash_value]->bucket + sizeof(ht_bucket*) + hash_table[hash_value]->count*sizeof(Entry), &entry, sizeof(Entry));
                //increase count of entries in the bucket
                hash_table[hash_value]->count += 1;

            }else{ // key found in the bucket

                memmove(&entry,hash_table[hash_value]->bucket + sizeof(ht_bucket*) + index*sizeof(Entry),sizeof(Entry)); // retrieve entry
                entry.tree = insert(entry.tree,record); //insert record in the enrty's tree
                
                memmove(hash_table[hash_value]->bucket + sizeof(ht_bucket*) + index*sizeof(Entry),&entry,sizeof(Entry)); //update entry
            }
        
        }else{ // there isn't enough space available to store a new entry
            
            ht_bucket* temp = hash_table[hash_value];
            index = search_key(key, temp->bucket, temp->count);
            if(index == -1){ //key not found in the first bucket


                //look throughout the bucket list
                ht_bucket* next = NULL;
                ht_bucket* b = NULL;
                memmove(&next,hash_table[hash_value]->bucket,sizeof(ht_bucket*));

                while(next){

                    // and search for the given key
                    index = search_key(key, next->bucket, next->count);
                    if(index == -1){

                        b = next;
                        memmove(&next,b->bucket,sizeof(ht_bucket*));

                        temp = b;
                        
                    }
                    else break; // key found

                }

            }

            if(index != -1){ // key found in the bucket list

                memmove(&entry,temp->bucket + sizeof(ht_bucket*) + index*sizeof(Entry),sizeof(Entry)); // retrieve entry
                entry.tree = insert(entry.tree,record); //insert record in the enrty's tree

                memmove(temp->bucket + sizeof(ht_bucket*) + index*sizeof(Entry),&entry, sizeof(Entry)); //update entry

            }else{ // key not found in the bucket list

                if(temp->count == entries_per_bucket){ //if the last bucket is full

                    //create new entry with the given key and insert record in the enrty's tree
                    entry.key = (char**)malloc(sizeof(char*)); 
                    if(!entry.key){
                        perror("Malloc error while allocating memory for entry's key");
                        exit(EXIT_FAILURE);
                    }
                    *(entry.key) = key;
                    entry.tree = NULL;
                    entry.tree = insert(entry.tree,record);

                    //create a new bucket
                    ht_bucket* new_bucket = malloc(sizeof(ht_bucket));
                    
                    new_bucket->count = 1;
                    new_bucket->bucket = malloc(size);//////
                    //insert new entry in the first available spot ( = 0)
                    ht_bucket* next = NULL;
                    memmove(new_bucket->bucket,&next, sizeof(ht_bucket*));
                    memmove(new_bucket->bucket + sizeof(ht_bucket*), &entry, sizeof(Entry));
                    memmove(temp->bucket,&new_bucket,sizeof(ht_bucket*));
                    //insert new bucket at the end of the bucket list

                }else { // there is available space in the last bucket
                    
                    //create new entry with the given key and insert record in the enrty's tree
                    entry.key = (char**)malloc(sizeof(char*)); 
                    if(!entry.key){
                        perror("Malloc error while allocating memory for entry's key");
                        exit(EXIT_FAILURE);
                    }
                    *(entry.key) = key;
                    entry.tree = NULL;
                    entry.tree = insert(entry.tree,record); 

                    //insert new entry in the first available spot ( = count)
                    memmove(temp->bucket + sizeof(ht_bucket*) + temp->count*sizeof(Entry), &entry, sizeof(Entry));
                    //increase count of entries in the bucket
                    temp->count += 1; 
                    
                }

            }


        }


    }

    return hash_table;
}




void free_ht(ht_bucket** hash_table, int size){
    
    Entry entry;
    ht_bucket* temp;
    ht_bucket* follow;
    
    for(int i = 0; i < size; i++){


        if(hash_table[i]->bucket){
            for(int j = 0 ; j < hash_table[i]->count ; j++){
                memmove(&entry, hash_table[i]->bucket +j*sizeof(Entry) + sizeof(ht_bucket*) ,sizeof(Entry));
                free(entry.key);
                free_tree(entry.tree);
            }

            ht_bucket* next ; 
            ht_bucket* temp;
            ht_bucket* b ;
            temp = hash_table[i];
            memmove(&next,temp->bucket,sizeof(ht_bucket*));

            while(next){ //if there are collisions

                //for each bucket in the bucket list


                for(int j = 0; j < next->count; j++){ //for each entry in the bucket

                    memmove(&entry, next->bucket + sizeof(ht_bucket*) + j*sizeof(Entry), sizeof(Entry));
                    free(entry.key);
                    free_tree(entry.tree);


                }
                free(next->bucket);
                memmove(&b,temp->bucket,sizeof(ht_bucket*));
                free(temp->bucket);
                memmove(&next,b->bucket,sizeof(ht_bucket*));
                temp = b;
                
            }

            free(hash_table[i]->bucket);
        } 
        free(hash_table[i]);
        

    }

    free(hash_table);

}

void ht_print(ht_bucket** hash_table, int size){

    Entry entry;
    
    for(int i = 0; i < size; i++){

        printf("hash_value = %d\n", i);
        printf("%s\n", "********************************");
        
        if(hash_table[i]->bucket){ // if non empty bucket

            printf("bucket = 1\n");
            
            //printf("%s\n", "--------------------------------");
            for(int j = 0; j < hash_table[i]->count; j++){// for each  entry in the first bucket

                memmove(&entry, hash_table[i]->bucket +sizeof(ht_bucket*) + j*sizeof(Entry), sizeof(Entry));
                printf("%s\n", *(entry.key));
                print_tree(entry.tree,0);
            
            }
            printf("%s\n", "--------------------------------");

            int k = 2;
            ht_bucket* next ; 
            ht_bucket* temp;
            ht_bucket* b ;
            temp = hash_table[i];

            memmove(&next,temp->bucket,sizeof(ht_bucket*));

            while(next){ //if there are collisions

                //for each bucket in the bucket list

                printf("bucket = %d\n",k++);
                //printf("%s\n", "--------------------------------");

                for(int j = 0; j < next->count; j++){ //for each entry in the bucket

                    memmove(&entry, next->bucket +sizeof(ht_bucket*) + j*sizeof(Entry), sizeof(Entry));
                    printf("%s\n", *(entry.key));
                    print_tree(entry.tree,0);


                }
                 printf("%s\n", "--------------------------------");
                memmove(&b,temp->bucket,sizeof(ht_bucket*));
                memmove(&next,b->bucket,sizeof(ht_bucket*));
                temp = b;
                
            }

            

        }

       

    }

}

