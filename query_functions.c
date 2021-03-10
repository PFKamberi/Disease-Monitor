/*File: query_functions.c*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "record.h"
#include "tree.h"
#include "list.h"
#include "hash_table.h"
#include "auxilary_functions.h"
#include "query_functions.h"
#include "heap.h"


void globalDiseaseStats(ht_bucket** hash_table, int entries){
	ht_bucket* tmp;
	ht_bucket* next ; 
	ht_bucket* b ;
	Entry entry;

	for(int i = 0; i < entries; i++){

		if(hash_table[i]->bucket){
			for(int j = 0; j < hash_table[i]->count; j++){// for each  entry in the first bucket

                memmove(&entry, hash_table[i]->bucket + sizeof(ht_bucket*) + j*sizeof(Entry), sizeof(Entry));
                //printf("%s\n", "*************************************************************************************************");
                printf("%s ", *(entry.key));
                printf("%d\n", count_tree_nodes(entry.tree));
                //printf("%s\n", "*************************************************************************************************");
                //print_tree(entry.tree,0);
                //printf("%s\n", "*************************************************************************************************");
            
            }
            tmp = hash_table[i];
            memmove(&next,tmp->bucket,sizeof(ht_bucket*));
            while(next){
            	for(int j = 0; j < next->count; j++){// for each  entry in the first bucket

                memmove(&entry, next->bucket + sizeof(ht_bucket*) + j*sizeof(Entry), sizeof(Entry));
                //printf("%s\n", "*************************************************************************************************");
                printf("%s ", *(entry.key));
                printf("%d\n", count_tree_nodes(entry.tree));
                //printf("%s\n", "*************************************************************************************************");
                //print_tree(entry.tree,0);
                //printf("%s\n", "*************************************************************************************************");
            
            	}
            	memmove(&b,tmp->bucket,sizeof(ht_bucket*));
                memmove(&next,b->bucket,sizeof(ht_bucket*));
                tmp = b;
            }


		}
	}


}

void globalDiseaseStats_dates(ht_bucket** hash_table, int entries, char* date1, char* date2){
	ht_bucket* tmp;
	ht_bucket* next ; 
	ht_bucket* b ;
	Entry entry;

	for(int i = 0; i < entries; i++){

		if(hash_table[i]->bucket){
			for(int j = 0; j < hash_table[i]->count; j++){// for each  entry in the first bucket

                memmove(&entry, hash_table[i]->bucket + sizeof(ht_bucket*) + j*sizeof(Entry), sizeof(Entry));
                //printf("%s\n", "*************************************************************************************************");
                printf("%s ", *(entry.key));
                printf("%d\n", count_in_range(entry.tree,date1,date2));
                //printf("%s\n", "*************************************************************************************************");
                //print_tree(entry.tree,0);
                //printf("%s\n", "*************************************************************************************************");
            
            }
            tmp = hash_table[i];
            memmove(&next,tmp->bucket,sizeof(ht_bucket*));
            while(next){
            	for(int j = 0; j < next->count; j++){// for each  entry in the first bucket

                memmove(&entry, next->bucket + sizeof(ht_bucket*) + j*sizeof(Entry), sizeof(Entry));
                //printf("%s\n", "*************************************************************************************************");
                printf("%s ", *(entry.key));
                printf("%d\n", count_in_range(entry.tree,date1,date2));
                //printf("%s\n", "*************************************************************************************************");
                //print_tree(entry.tree,0);
                //printf("%s\n", "*************************************************************************************************");
            
            	}
            	memmove(&b,tmp->bucket,sizeof(ht_bucket*));
                memmove(&next,b->bucket,sizeof(ht_bucket*));
                tmp = b;
            }


		}
	}


}


void diseaseFrequency(ht_bucket** hash_table, int entries, char* virusName, char* date1, char* date2){

	ht_bucket* tmp;
	ht_bucket* next ; 
	ht_bucket* b ;
	Entry entry;
	int hash_value = hash_function(virusName,entries);
	int index;

	index = search_key(virusName,hash_table[hash_value]->bucket,hash_table[hash_value]->count);

	if(index != -1){
		memmove(&entry, hash_table[hash_value]->bucket + sizeof(ht_bucket*) + index*sizeof(Entry), sizeof(Entry));
		//printf("%s\n", "*************************************************************************************************");
        printf("%s ", *(entry.key));
        printf("%d\n", count_in_range(entry.tree,date1,date2));
        //printf("%s\n", "*************************************************************************************************");
        //print_tree(entry.tree,0);
        //printf("%s\n", "*************************************************************************************************");
            
	}else{

		int found = 0;
		tmp = hash_table[hash_value];
        memmove(&next,&(tmp->bucket),sizeof(ht_bucket*));/////////
        while(next){

        		index = search_key(virusName,next->bucket,next->count);

        		if(index != -1){

        			memmove(&entry, next->bucket + sizeof(ht_bucket*) + index*sizeof(Entry), sizeof(Entry));
                	//printf("%s\n", "*************************************************************************************************");
                	printf("%s ", *(entry.key));
                	printf("%d\n", count_in_range(entry.tree,date1,date2));
                	//printf("%s\n", "*************************************************************************************************");
                	//print_tree(entry.tree,0);
                	//printf("%s\n", "*************************************************************************************************");
           			found = 1;
           			break;
        		}

            	
            	memmove(&b,tmp->bucket,sizeof(ht_bucket*));
                memmove(&next,b->bucket,sizeof(ht_bucket*));
                tmp = b;
            }

        if(!found) printf("%s %d\n", virusName, 0);
        	//printf("virusName %s\n not found in the system", virusName);/// or return 0

	}

	
}

void country_diseaseFrequency(ht_bucket** hash_table, int entries, char* virusName, char* country, char* date1, char* date2){

	ht_bucket* tmp;
	ht_bucket* next ; 
	ht_bucket* b ;
	Entry entry;
	int hash_value = hash_function(country,entries);
	int index;

	index = search_key(country,hash_table[hash_value]->bucket,hash_table[hash_value]->count);

	if(index != -1){
		memmove(&entry, hash_table[hash_value]->bucket + sizeof(ht_bucket*) + index*sizeof(Entry), sizeof(Entry));
		//printf("%s\n", "*************************************************************************************************");
        printf("%s ", *(entry.key));
        printf("%d\n", disease_count_in_range(entry.tree, virusName,  date1, date2));
        //printf("%s\n", "*************************************************************************************************");
        //print_tree(entry.tree,0);
        //printf("%s\n", "*************************************************************************************************");
            
	}else{

		int found = 0;
		tmp = hash_table[hash_value];
        memmove(&next,&(tmp->bucket),sizeof(ht_bucket*));
        while(next){

        		index = search_key(country,next->bucket,next->count);

        		if(index != -1){

        			memmove(&entry, next->bucket + sizeof(ht_bucket*) + index*sizeof(Entry), sizeof(Entry));
                	//printf("%s\n", "*************************************************************************************************");
                	printf("%s ", *(entry.key));
                	printf("%d\n", disease_count_in_range(entry.tree, virusName,  date1, date2));
                	//printf("%s\n", "*************************************************************************************************");
                	//print_tree(entry.tree,0);
                	//printf("%s\n", "*************************************************************************************************");
           			found = 1;
           			break;
        		}

            	
            	memmove(&b,tmp->bucket,sizeof(ht_bucket*));
                memmove(&next,b->bucket,sizeof(ht_bucket*));
                tmp = b;
            }

        if(!found) printf("%s %d\n", country, 0);
        	//printf("virusName %s\n not found for given country in the system", virusName); // return 0

	}

}

void insertPatientRecord(lnode** record_list, ht_bucket** disease_hash_table, int diseaseHashtableNumOfEntries,
						 ht_bucket** country_hash_table, int countryHashtableNumOfEntries, int bucketSize,
						 char* recordID, char* patientFirstName, char* patientLastName, char* diseaseID,
						 char* country, char* entryDate, char* exitDate){ //line_count++ stin main

	Record record = init_record(recordID,patientFirstName,patientLastName,diseaseID,country,entryDate,exitDate);
	
	if(check_dublicates(*record_list,record)){
        printf("%s\n", "error");
		//printf("recordID: %s already in the system\n",recordID);
		delete_record(&record);	
		return;		
	}

	if(strcmp(exitDate,"-") && check_dates(record) > 0 ){
        printf("%s\n", "error");
		printf(" entry date after exit date");
		delete_record(&record);	
		return;
	}


	delete_record(&record);	

	add(record_list,recordID,patientFirstName,patientLastName,diseaseID,country,entryDate,exitDate);
	disease_hash_table = ht_insert(disease_hash_table,bucketSize,&((*record_list)->record),get_diseaseID(&((*record_list)->record)),diseaseHashtableNumOfEntries);
	country_hash_table =  ht_insert(country_hash_table,bucketSize,&((*record_list)->record),get_country(&((*record_list)->record)),countryHashtableNumOfEntries);
	printf("%s\n", "Record added");	
}

void recordPatientExit(lnode** record_list, ht_bucket** disease_hash_table, int diseaseHashtableNumOfEntries,
					   ht_bucket** country_hash_table, int countryHashtableNumOfEntries, char* recordID, char* exitDate){

	lnode * temp;
    temp = *record_list;
    int found = 0;
    
    while(temp){
        if(strcmp(recordID,temp->record.recordID) == 0){
            if(strcmp(temp->record.exitDate,"-")){

                printf("%s\n", "Not found");
                return;
                //printf("%s\n", "already has exit date");
            }
        	found = 1;
        	break;
        }
        temp = temp->next;
    }

    if(!found){
        printf("%s\n", "Not found");
    	//printf("recordID: %s not found in the system\n",recordID);
		return;		
    }

    if(datecomp(get_entryDate(&(temp->record)),exitDate) > 0){
    	printf("%s\n", "error");
        //printf(" entry date is after given exit date\n");
		return;
    }


    //free((temp->record).exitDate);
    //(temp->record).exitDate = (char*)malloc((sizeof(exitDate) + 1)*sizeof(char));
    //strcpy((temp->record).exitDate,exitDate);



	ht_bucket* tmp;
	ht_bucket* next ; 
	ht_bucket* b ;
	node* a;
	Entry entry;
	int hash_value = hash_function(get_diseaseID(&(temp->record)),diseaseHashtableNumOfEntries);
	int index;

	index = search_key((temp->record).diseaseID,disease_hash_table[hash_value]->bucket,disease_hash_table[hash_value]->count);

	if(index != -1){
		memmove(&entry, disease_hash_table[hash_value]->bucket + sizeof(ht_bucket*) + index*sizeof(Entry), sizeof(Entry));
		a = search_recordID(entry.tree, recordID);
		free((a->record)->exitDate);// free "-"
		(a->record)->exitDate = (char*)malloc((strlen(exitDate) + 1)*sizeof(char));
		strcpy((a->record)->exitDate,exitDate);
		///search tree and get record then update exitdate          
	}else{

		tmp = disease_hash_table[hash_value];
        memmove(&next,&(tmp->bucket),sizeof(ht_bucket*));
        while(next){

        		index = search_key((temp->record).diseaseID,next->bucket,next->count);

        		if(index != -1){

        			memmove(&entry, next->bucket + sizeof(ht_bucket*) + index*sizeof(Entry), sizeof(Entry));
                	a = search_recordID(entry.tree, recordID);
					free((a->record)->exitDate);
					(a->record)->exitDate = (char*)malloc((strlen(exitDate) + 1)*sizeof(char));
					strcpy((a->record)->exitDate,exitDate);
           			break;
        		}

            	
            	memmove(&b,tmp->bucket,sizeof(ht_bucket*));
                memmove(&next,b->bucket,sizeof(ht_bucket*));
                tmp = b;
            }

	}

	hash_value = hash_function(get_country(&(temp->record)),countryHashtableNumOfEntries);


	index = search_key((temp->record).country,country_hash_table[hash_value]->bucket,country_hash_table[hash_value]->count);

	if(index != -1){
		memmove(&entry, country_hash_table[hash_value]->bucket + sizeof(ht_bucket*) + index*sizeof(Entry), sizeof(Entry));
		a = search_recordID(entry.tree, recordID);
		free((a->record)->exitDate);
		(a->record)->exitDate = (char*)malloc((strlen(exitDate) + 1)*sizeof(char));
		strcpy((a->record)->exitDate,exitDate);
		///search tree and get record then update exitdate          
	}else{

		tmp = country_hash_table[hash_value];
        memmove(&next,&(tmp->bucket),sizeof(ht_bucket*));
        while(next){

        		index = search_key((temp->record).country,next->bucket,next->count);

        		if(index != -1){

        			memmove(&entry, next->bucket + sizeof(ht_bucket*) + index*sizeof(Entry), sizeof(Entry));
                	a = search_recordID(entry.tree, recordID);
					free((a->record)->exitDate);
					(a->record)->exitDate = (char*)malloc((strlen(exitDate) + 1)*sizeof(char));
					strcpy((a->record)->exitDate,exitDate);
           			break;
        		}

            	
            	memmove(&b,tmp->bucket,sizeof(ht_bucket*));
                memmove(&next,b->bucket,sizeof(ht_bucket*));
                tmp = b;
            }

	}
    printf("%s\n", "Record updated");
}

void numCurrentPatients(ht_bucket** disease_hash_table, int diseaseHashtableNumOfEntries){

    ht_bucket* tmp;
    ht_bucket* next ; 
    ht_bucket* b ;
    Entry entry;

    for(int i = 0; i < diseaseHashtableNumOfEntries; i++){

        if(disease_hash_table[i]->bucket){
            for(int j = 0; j < disease_hash_table[i]->count; j++){// for each  entry in the first bucket

                memmove(&entry, disease_hash_table[i]->bucket + sizeof(ht_bucket*) + j*sizeof(Entry), sizeof(Entry));
                //printf("%s\n", "*************************************************************************************************");
                printf("%s ", *(entry.key));
                printf("%d\n", stILL(entry.tree));
                //printf("%s\n", "*************************************************************************************************");
                //print_tree(entry.tree,0);
                //printf("%s\n", "*************************************************************************************************");
            
            }
            tmp = disease_hash_table[i];
            memmove(&next,tmp->bucket,sizeof(ht_bucket*));
            while(next){
                for(int j = 0; j < next->count; j++){// for each  entry in the first bucket

                memmove(&entry, next->bucket + sizeof(ht_bucket*) + j*sizeof(Entry), sizeof(Entry));
                //printf("%s\n", "*************************************************************************************************");
                printf("%s ", *(entry.key));
                printf("%d\n", stILL(entry.tree));
                //printf("%s\n", "*************************************************************************************************");
                //print_tree(entry.tree,0);
                //printf("%s\n", "*************************************************************************************************");
            
                }
                memmove(&b,tmp->bucket,sizeof(ht_bucket*));
                memmove(&next,b->bucket,sizeof(ht_bucket*));
                tmp = b;
            }


        }
    }


}

void  numCurrentPatients_disease(ht_bucket** disease_hash_table, int diseaseHashtableNumOfEntries, char* diseaseID){

    ht_bucket* tmp;
    ht_bucket* next ; 
    ht_bucket* b ;
    Entry entry;
    int hash_value = hash_function(diseaseID,diseaseHashtableNumOfEntries);
    int index;

    index = search_key(diseaseID,disease_hash_table[hash_value]->bucket,disease_hash_table[hash_value]->count);

    if(index != -1){
        memmove(&entry, disease_hash_table[hash_value]->bucket + sizeof(ht_bucket*) + index*sizeof(Entry), sizeof(Entry));
        //printf("%s\n", "*************************************************************************************************");
        printf("%s ", *(entry.key));
        printf("%d\n", stILL(entry.tree));
        //printf("%s\n", "*************************************************************************************************");
        //print_tree(entry.tree,0);
        //printf("%s\n", "*************************************************************************************************");
            
    }else{

        int found = 0;
        tmp = disease_hash_table[hash_value];
        memmove(&next,&(tmp->bucket),sizeof(ht_bucket*));
        while(next){

                index = search_key(diseaseID,next->bucket,next->count);

                if(index != -1){

                    memmove(&entry, next->bucket + sizeof(ht_bucket*) + index*sizeof(Entry), sizeof(Entry));
                    //printf("%s\n", "*************************************************************************************************");
                    printf("%s ", *(entry.key));
                    printf("%d\n", stILL(entry.tree));
                    //printf("%s\n", "*************************************************************************************************");
                    //print_tree(entry.tree,0);
                    //printf("%s\n", "*************************************************************************************************");
                    found = 1;
                    break;
                }

                
                memmove(&b,tmp->bucket,sizeof(ht_bucket*));
                memmove(&next,b->bucket,sizeof(ht_bucket*));
                tmp = b;
            }

        if(!found)
            printf("%s\n", "error");
            //printf("disease %s not found  in the system\n", diseaseID);

    }


}



void topkDiseases(ht_bucket** hash_table, int entries, char* country,int k){

    ht_bucket* tmp;
    ht_bucket* next ; 
    ht_bucket* b ;
    Entry entry;
    int hash_value = hash_function(country,entries);
    int index;

    index = search_key(country,hash_table[hash_value]->bucket,hash_table[hash_value]->count);

    if(index != -1){
        memmove(&entry, hash_table[hash_value]->bucket + sizeof(ht_bucket*) + index*sizeof(Entry), sizeof(Entry));
        //printf("%s\n", "*************************************************************************************************");
        topk(entry.tree,1,k);

        //printf("%s\n", "*************************************************************************************************");
        //print_tree(entry.tree,0);
        //printf("%s\n", "*************************************************************************************************");
            
    }else{

        int found = 0;
        tmp = hash_table[hash_value];
        memmove(&next,&(tmp->bucket),sizeof(ht_bucket*));
        while(next){

                index = search_key(country,next->bucket,next->count);

                if(index != -1){

                    memmove(&entry, next->bucket + sizeof(ht_bucket*) + index*sizeof(Entry), sizeof(Entry));
                    //printf("%s\n", "*************************************************************************************************");
                    topk(entry.tree,1,k);
                    
                    //printf("%s\n", "*************************************************************************************************");
                    //print_tree(entry.tree,0);
                    //printf("%s\n", "*************************************************************************************************");
                    found = 1;
                    break;
                }

                
                memmove(&b,tmp->bucket,sizeof(ht_bucket*));
                memmove(&next,b->bucket,sizeof(ht_bucket*));
                tmp = b;
            }

        if(!found) printf("%s %d\n", country, 0); ////////
            //printf("virusName %s\n not found in the system", virusName);/// or return 0

    }

}


void topkDiseases_dates(ht_bucket** hash_table, int entries, char* country,int k, char* date1, char* date2){

    ht_bucket* tmp;
    ht_bucket* next ; 
    ht_bucket* b ;
    Entry entry;
    int hash_value = hash_function(country,entries);
    int index;

    index = search_key(country,hash_table[hash_value]->bucket,hash_table[hash_value]->count);

    if(index != -1){
        memmove(&entry, hash_table[hash_value]->bucket + sizeof(ht_bucket*) + index*sizeof(Entry), sizeof(Entry));
        //printf("%s\n", "*************************************************************************************************");
        topk_dates(entry.tree,1,k,date1,date2);

        //printf("%s\n", "*************************************************************************************************");
        //print_tree(entry.tree,0);
        //printf("%s\n", "*************************************************************************************************");
            
    }else{

        int found = 0;
        tmp = hash_table[hash_value];
        memmove(&next,&(tmp->bucket),sizeof(ht_bucket*));
        while(next){

                index = search_key(country,next->bucket,next->count);

                if(index != -1){

                    memmove(&entry, next->bucket + sizeof(ht_bucket*) + index*sizeof(Entry), sizeof(Entry));
                    //printf("%s\n", "*************************************************************************************************");
                    topk_dates(entry.tree,1,k,date1,date2);
                    
                    //printf("%s\n", "*************************************************************************************************");
                    //print_tree(entry.tree,0);
                    //printf("%s\n", "*************************************************************************************************");
                    found = 1;
                    break;
                }

                
                memmove(&b,tmp->bucket,sizeof(ht_bucket*));
                memmove(&next,b->bucket,sizeof(ht_bucket*));
                tmp = b;
            }

        if(!found) printf("%s %d\n", country, 0); ////////
            //printf("virusName %s\n not found in the system", virusName);/// or return 0

    }

}


void topkCountries(ht_bucket** hash_table, int entries, char* disease,int k){


    ht_bucket* tmp ;
    ht_bucket* next ; 
    ht_bucket* b ;
    Entry entry;
    int hash_value = hash_function(disease,entries);
    int index;
    index = search_key(disease,hash_table[hash_value]->bucket,hash_table[hash_value]->count);


    if(index != -1){


        memmove(&entry, hash_table[hash_value]->bucket + sizeof(ht_bucket*) + index*sizeof(Entry), sizeof(Entry));
        //printf("%s\n", "*************************************************************************************************");
        topk(entry.tree,0,k);

        //printf("%s\n", "*************************************************************************************************");
        //print_tree(entry.tree,0);
        //printf("%s\n", "*************************************************************************************************");
            
    }else{

        int found = 0;
        tmp = hash_table[hash_value];
        memmove(&next,&(tmp->bucket),sizeof(ht_bucket*));////////
       
        while(next){

                index = search_key(disease,next->bucket,next->count);

                if(index != -1){

                    memmove(&entry, next->bucket + sizeof(ht_bucket*) + index*sizeof(Entry), sizeof(Entry));
                    //printf("%s\n", "*************************************************************************************************");
                    topk(entry.tree,0,k);
                    
                    //printf("%s\n", "*************************************************************************************************");
                    //print_tree(entry.tree,0);
                    //printf("%s\n", "*************************************************************************************************");
                    found = 1;
                    break;
                }

                
                memmove(&b,tmp->bucket,sizeof(ht_bucket*));
                memmove(&next,b->bucket,sizeof(ht_bucket*));
                tmp = b;
            }

        if(!found) printf("%s %d\n", disease, 0); ////////
            //printf("virusName %s\n not found in the system", virusName);/// or return 0

    }

}


void topkCountries_dates(ht_bucket** hash_table, int entries, char* disease,int k, char* date1, char* date2){

    ht_bucket* tmp;
    ht_bucket* next ; 
    ht_bucket* b ;
    Entry entry;
    int hash_value = hash_function(disease,entries);
    int index;

    index = search_key(disease,hash_table[hash_value]->bucket,hash_table[hash_value]->count);

    if(index != -1){
        memmove(&entry, hash_table[hash_value]->bucket + sizeof(ht_bucket*) + index*sizeof(Entry), sizeof(Entry));
        //printf("%s\n", "*************************************************************************************************");
        topk_dates(entry.tree,0,k,date1,date2);

        //printf("%s\n", "*************************************************************************************************");
        //print_tree(entry.tree,0);
        //printf("%s\n", "*************************************************************************************************");
            
    }else{

        int found = 0;
        tmp = hash_table[hash_value];
        memmove(&next,&(tmp->bucket),sizeof(ht_bucket*));
        while(next){

                index = search_key(disease,next->bucket,next->count);

                if(index != -1){

                    memmove(&entry, next->bucket + sizeof(ht_bucket*) + index*sizeof(Entry), sizeof(Entry));
                    //printf("%s\n", "*************************************************************************************************");
                    topk_dates(entry.tree,0,k,date1,date2);
                    
                    //printf("%s\n", "*************************************************************************************************");
                    //print_tree(entry.tree,0);
                    //printf("%s\n", "*************************************************************************************************");
                    found = 1;
                    break;
                }

                
                memmove(&b,tmp->bucket,sizeof(ht_bucket*));
                memmove(&next,b->bucket,sizeof(ht_bucket*));
                tmp = b;
            }

        if(!found) printf("%s %d\n", disease, 0); ////////
            //printf("virusName %s\n not found in the system", virusName);/// or return 0

    }




}