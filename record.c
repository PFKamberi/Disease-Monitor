/*File: record.c*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "record.h"

Record init_record(char* recordID, char* patientFirstName, char* patientLastName, char* diseaseID, 
				   char* country, char* entryDate, char* exitDate){
	
	Record record;

	record.recordID = (char*)malloc((strlen(recordID) + 1)*sizeof(char)); // -1?
	if(!record.recordID){
		perror("Malloc error while allocating memory for record's recordID");
		exit(EXIT_FAILURE);
	}
	strcpy(record.recordID,recordID);

	
	record.patientFirstName = (char*)malloc((strlen(patientFirstName) + 1)*sizeof(char));
	if(!record.patientFirstName){
		perror("Malloc error while allocating memory for record's patientFirstName");
		exit(EXIT_FAILURE);
	}
	strcpy(record.patientFirstName,patientFirstName);

	record.patientLastName = (char*)malloc((strlen(patientLastName) + 1)*sizeof(char));
	if(!record.patientLastName){
		perror("Malloc error while allocating memory for record's patientLastName");
		exit(EXIT_FAILURE);
	}
	strcpy(record.patientLastName,patientLastName);

	record.diseaseID = (char*)malloc((strlen(diseaseID) + 1 )*sizeof(char));
	if(!record.diseaseID){
		perror("Malloc error while allocating memory for record's diseaseID");
		exit(EXIT_FAILURE);
	}
	strcpy(record.diseaseID,diseaseID);

	record.country = (char*)malloc((strlen(country) + 1)*sizeof(char));
	if(!record.country){
		perror("Malloc error while allocating memory for record's country");
		exit(EXIT_FAILURE);
	}
	strcpy(record.country,country);

	record.entryDate = (char*)malloc((strlen(entryDate) + 1)*sizeof(char));
	if(!record.entryDate){
		perror("Malloc error while allocating memory for record's entryDate");
		exit(EXIT_FAILURE);
	}
	strcpy(record.entryDate,entryDate);


	record.exitDate = (char*)malloc((strlen(exitDate) + 1)*sizeof(char));
	if(!record.exitDate){
		perror("Malloc error while allocating memory for record's exitDate");
		exit(EXIT_FAILURE);
	}
	strcpy(record.exitDate,exitDate);


	return record;
}

void delete_record(Record* record){
	free(record->recordID);
	free(record->patientFirstName);
	free(record->patientLastName);
	free(record->diseaseID);
	free(record->country);
	free(record->entryDate);
	free(record->exitDate);
}

void print_record(Record* record){
	if(record)
		printf("%s\t %s\t %s\t %s\t %s\t %s\t %s\n", record->recordID, record->patientFirstName, record->patientLastName, 
			record->diseaseID, record->country, record->entryDate, record->exitDate);
	else
		printf("NULL");
}

char* get_entryDate(Record* record){ return record->entryDate; }

char* get_exitDate(Record* record){ return record->exitDate; }

char* get_diseaseID(Record* record){ return record->diseaseID; }

char* get_country(Record* record) {return record->country; }

int get_recordID(Record* record) { 
	printf("%d\n", atoi(record->recordID));
	return atoi(record->recordID); }

int datecmp(Record record1, Record record2){ 

	char* entry1 = NULL;
	char* entry2 = NULL;
	char* str1 = NULL;
	char* str2 = NULL;
	char* s1 = malloc((strlen(record1.entryDate) + 1 ) * sizeof(char));
	char* s2 = malloc((strlen(record2.entryDate) + 1 ) * sizeof(char));
	int  date1[3], date2[3];

	strcpy(s1,record1.entryDate);
	entry1 = strtok(s1," ");
	for (int i = 0; i < 6; i++){
		entry1 = strtok(s1," ");
	}

	str1 = strtok(entry1,"-");
	int i = 0;
	while(str1 != NULL){
		date1[i] = atoi(str1);
		str1 = strtok(NULL,"-");
		i++;
	}

	strcpy(s2,record2.entryDate);
	entry2 = strtok(s2," ");
	for (int i = 0; i < 6; i++){
		entry2 = strtok(s2," ");
	}

	str2 = strtok(entry2,"-");
	i = 0;
	while(str2 != NULL){
		date2[i] = atoi(str2);
		str2 = strtok(NULL,"-");
		i++;

	}

	free(s1);
	free(s2);

	if(date1[2] == date2[2])
		if(date1[1] == date2[1])
			return (date1[0] - date2[0]);
		else 
			return (date1[1] - date2[1]);
	else
		return (date1[2] - date2[2]);

	
}


