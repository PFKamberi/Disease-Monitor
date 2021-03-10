/*File: auxilary_functions.c*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "record.h"

int check_dates(/*char**/Record record){
	char* enter = NULL;
	enter = malloc((strlen(record.entryDate)+1)*sizeof(char));
	char* exit = NULL;
	exit = malloc((strlen(record.exitDate)+1)*sizeof(char));
	char* str1 = NULL;
	char* str2 = NULL;
	int en[3], ex[3];

	strcpy(enter,record.entryDate);
	strcpy(exit,record.exitDate);


	str1 = strtok(enter,"-");
	int i = 0;
	while(str1 != NULL){
		en[i] = atoi(str1);
		str1 = strtok(NULL,"-");
		i++;
	}

	str2 = strtok(exit,"-");
	i = 0;
	while(str2 != NULL){
		ex[i] = atoi(str2);
		str2 = strtok(NULL,"-");
		i++;
	}

	free(enter);
	free(exit);

	if(en[2] == ex[2])
		if(en[1] == ex[1])
			return (en[0] - ex[0]);
		else 
			return (en[1] - ex[1]);
	else
		return (en[2] - ex[2]);

	
	
}

