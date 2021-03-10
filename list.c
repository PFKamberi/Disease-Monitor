/*FIle: list.c*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "record.h"
#include "list.h"

void init_list(lnode** head) { *head = NULL; }

void print_list(lnode* head) {
    
    lnode * temp;
    temp = head;
    
    while(temp){
        
        printf("{ %s\t %s\t %s\t %s\t %s\t %s\t %s }\t", temp->record.recordID, temp->record.patientFirstName, temp->record.patientLastName, 
            temp->record.diseaseID, temp->record.country, temp->record.entryDate, temp->record.exitDate);
        
        printf("-->\n");
        
        temp = temp->next;
        
    }
    
    printf("NULL\n");

}


lnode* add(lnode** node, char* recordID, char* patientFirstName, char* patientLastName, char* diseaseID, 
                   char* country, char* entryDate, char* exitDate) {
    
    lnode* temp = (lnode*) malloc(sizeof (lnode));
    
    if (temp == NULL) {
        perror("Malloc error while allocating memory for new list node");
        exit(EXIT_FAILURE); 
    }
    
    temp->record = init_record(recordID, patientFirstName, patientLastName,diseaseID, country, entryDate, exitDate);
    temp->next = *node;
    *node = temp;
    return *node;
}

int check_dublicates(lnode* head, Record record){ 
    
    lnode * temp;
    temp = head;
    
    while(temp){
        if(strcmp(record.recordID,temp->record.recordID) == 0) return 1; //dublicate found
        temp = temp->next;
    }
    
    return 0;
}


void free_list(lnode *head) {

    lnode *temp = head;
    lnode *follow;
    
    while (temp){
        follow = temp;
        temp = temp->next;
        delete_record(&(follow->record));
        free(follow);
    }
    
}



/*int main(void){
    
    lnode* head;
    init_list(&head);

    Record r1, r2, r3; 
    r1 = init_record("889","Mary","Smith","COVID-2019","China","25-1-2019","27-1-2019");
    r2 = init_record("776","Larry","Jones","SARS-1","Italy","10-02-2019","-");
    r3 = init_record("889","Larry","Jones","SARS-1","Italy","10-02-2019","-");
        
    add(&head,r1);
    add(&head,r2);

    if(check_dublicates(head,r3)) printf("%s\n", "dublicate found");

    print_list(head);
    free_list(head);
  
    return 0;
}*/


