/*File tree.h*/

#include "record.h"

#ifndef _TREE
#define _TREE

	struct node{
   		 
    	Record* record;    
    	int height;
    	
    	struct node* left;
    	struct node* right;
	};

	typedef struct node node;

	node* new_node(Record*);
	int max(int , int);
	int height(node* );
	void new_height(node* );
	node* right_rotation(node* );
	node* left_rotation(node* );
	node* rebalance(node* );
	node* insert(node* , Record* );
	void print_tree(node* , int );
	void free_tree(node* );
	int count_tree_nodes(node *);
	int count_in_range(node *, char* , char* );
	int datecomp(char* , char* );
	int disease_count_in_range(node* , char* , char* , char* );
	node* search_recordID(node* , char* );
	int stILL(node* );
	void topk(node* , int , int );
	void topk_dates(node* , int , int , char* , char* );

#endif


