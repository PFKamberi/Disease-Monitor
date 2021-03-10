#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "record.h"
#include "auxilary_functions.h"
#include "tree.h"
#include "list.h"
#include "hash_table.h"
#include "query_functions.h"



//krousma einai kapoios pou isix8i mesa sto diasthma anexarthta apo to an bghke h oxi

int main(int argc, char* argv[]){
	int diseaseHashtableNumOfEntries = 0;
	int countryHashtableNumOfEntries = 0;
	int bucketSize = 0;
	char* patientRecordsFile; 

	/*read and check command line arguements*/

	if(argc != 9){
		perror("Not enough command line arguements provided.");
		exit(EXIT_FAILURE);
	}

	for(int i = 1; i < argc; i++){
		if(strcmp(argv[i],"-p") == 0){
			patientRecordsFile = (char*)malloc((strlen(argv[i+1]) + 1)*sizeof(char));
			strcpy(patientRecordsFile,argv[++i]);
		}
		else if(strcmp(argv[i],"-h1") == 0){

			diseaseHashtableNumOfEntries = atoi(argv[++i]);
		}
		else if(strcmp(argv[i],"-h2") == 0){
			
			countryHashtableNumOfEntries = atoi(argv[++i]);
		}else if(strcmp(argv[i],"-b") == 0){
			bucketSize = atoi(argv[++i]);
			/*if(bucketSize < sizeof(Entry) + sizeof(ht_bucket**))// =24
			{
				perror("Too small bucket size");
				exit(EXIT_FAILURE);
			}*/
		}
		else{
			perror("Command line arguements error");
			exit(EXIT_FAILURE);
		}
	}

	FILE* fd = fopen(patientRecordsFile,"r+"); 
	if(fd == NULL){
		perror("Cannot open patientRecordsFile");
		exit(EXIT_FAILURE);
	}

/**********************************************/
	char* recordID = NULL;
	char* patientFirstName = NULL;
	char* patientLastName = NULL;
	char* diseaseID = NULL;
	char* country = NULL;
	char* entryDate = NULL;
	char* exitDate = NULL;


	int line_count = 0;
	char* line= NULL;
	size_t line_size;


	lnode* record_list;
    init_list(&record_list);

    Record record;
/**********************************************/

	while(getline(&line,&line_size,fd) != -1){ 
		
		recordID = strtok(line," ");
		patientFirstName = strtok(NULL," ");
		patientLastName = strtok(NULL," ");
		diseaseID = strtok(NULL," ");
		country = strtok(NULL," ");
		entryDate = strtok(NULL," ");
		exitDate = strtok(NULL," ");

		record = init_record(recordID,patientFirstName,patientLastName,diseaseID,country,entryDate,exitDate);
		
		if(check_dublicates(record_list,record)){
			perror("Dublicate found");
			exit(EXIT_FAILURE);
		}

		if(strcmp(record.exitDate,"-") && check_dates(record) > 0){
			perror("Record found with entry date after exit date");
			exit(EXIT_FAILURE);
		}


		delete_record(&record);
		add(&record_list,recordID,patientFirstName,patientLastName,diseaseID,country,entryDate,exitDate);
		check_dates(record_list->record);///
		line_count++;
	}


	lnode * temp;
    temp = record_list;

	ht_bucket** disease_hash_table = ht_init(diseaseHashtableNumOfEntries);
	ht_bucket** country_hash_table = ht_init(countryHashtableNumOfEntries);

	while(temp){

		disease_hash_table = ht_insert(disease_hash_table,bucketSize,&(temp->record),get_diseaseID(&(temp->record)),diseaseHashtableNumOfEntries);
		country_hash_table =  ht_insert(country_hash_table,bucketSize,&(temp->record),get_country(&(temp->record)),countryHashtableNumOfEntries);
		temp = temp->next;

	}

	/*ht_print(disease_hash_table,diseaseHashtableNumOfEntries);

    printf("%s\n","###########" );

    ht_print(country_hash_table,countryHashtableNumOfEntries);

	print_list(record_list);*/

	
	char* command = NULL;
	while(1){

		//printf("%s\n", "type command to continue:");
		
		getline(&line,&line_size,stdin);

		command = strtok(line," \n"); //\t?

		if(!strcmp(command,"/globalDiseaseStats")){

			char* date1 = NULL;
			char* date2 = NULL;

			date1 = strtok(NULL," \n");

			if(!date1)
				globalDiseaseStats(disease_hash_table,diseaseHashtableNumOfEntries);
			else{

				date2 = strtok(NULL," \n");
				if(!date2){
					perror("error");
					//perror("No date2 provided");
					break;
					//exit(EXIT_FAILURE);
				}else
					globalDiseaseStats_dates(disease_hash_table,diseaseHashtableNumOfEntries,date1,date2);
				
			}

		}else if(!strcmp(command,"/diseaseFrequency")){

			char* virusName = NULL;
			char* date1 = NULL;
			char* date2 = NULL;
			char* country = NULL;

			virusName = strtok(NULL," \n");
			date1 = strtok(NULL," \n");
			date2 = strtok(NULL," \n");
			country = strtok(NULL," \n");

			if(virusName && date1 && date2){

				if(!country)
					diseaseFrequency(disease_hash_table, diseaseHashtableNumOfEntries, virusName,date1,date2);
				else
					country_diseaseFrequency(country_hash_table, countryHashtableNumOfEntries, virusName, country, date1,date2);
	
			}else{
				perror("error");
				//perror("Not enough arguments provided");
				break;
				//exit(EXIT_FAILURE);
			}


		}else if(!strcmp(command,"/topk-Diseases")){

			char* country = NULL;
			char* k = NULL;
			char* date1 = NULL;
			char* date2 = NULL;


			k = strtok(NULL," \n");
			country = strtok(NULL," \n");
			date1 = strtok(NULL," \n");
			date2 = strtok(NULL," \n");


			if(country && k){

				if(date1 && date2){
					 topkDiseases_dates(country_hash_table , countryHashtableNumOfEntries , country , atoi(k) , date1 , date2);
				}else if(!date1 && ! date2){
					topkDiseases(country_hash_table , countryHashtableNumOfEntries , country , atoi(k) );
				}else{
					perror("error");
					break;
				}


			}else{
				perror("error");
				break;
			}



		}else if(!strcmp(command,"/topk-Countries")){

			char* virusName = NULL;
			char* k = NULL;
			char* date1 = NULL;
			char* date2 = NULL;

			k = strtok(NULL," \n");
			virusName = strtok(NULL," \n");
			date1 = strtok(NULL," \n");
			date2 = strtok(NULL," \n");


			if(country && k){

				if(date1 && date2){
					 topkCountries_dates(disease_hash_table , diseaseHashtableNumOfEntries , virusName ,atoi(k)  , date1 , date2);
				}else if(!date1 && ! date2){
					topkCountries(disease_hash_table , diseaseHashtableNumOfEntries , virusName , atoi(k) );
				}else{
					perror("error");
					break;
				}


			}else{
				perror("error");
				break;
			}

		}else if(!strcmp(command,"/insertPatientRecord")){

			char* recordID = NULL;
			char* patientFirstName = NULL;
			char* patientLastName = NULL;
			char* diseaseID = NULL;
			char* country = NULL;
			char* entryDate = NULL;
			char* exitDate = NULL;

			recordID = strtok(NULL," \n");
			patientFirstName = strtok(NULL," \n");
			patientLastName = strtok(NULL," \n");
			diseaseID = strtok(NULL," \n");
			country = strtok(NULL," \n");
			entryDate = strtok(NULL," \n");
			exitDate = strtok(NULL," \n");

			if(recordID && patientFirstName && patientLastName && diseaseID && country && entryDate ){
				if(!exitDate)
					insertPatientRecord(&record_list, disease_hash_table,  diseaseHashtableNumOfEntries, country_hash_table,  countryHashtableNumOfEntries,
					    bucketSize, recordID, patientFirstName, patientLastName, diseaseID, country, entryDate, "-");
				else
					insertPatientRecord(&record_list, disease_hash_table,  diseaseHashtableNumOfEntries, country_hash_table,  countryHashtableNumOfEntries,
					    bucketSize, recordID, patientFirstName, patientLastName, diseaseID, country, entryDate, exitDate);
				
			}else{
				//perror("error");
				perror("Not enough arguments provided");
				break;
				//exit(EXIT_FAILURE);
			}
			
		}else if(!strcmp(command,"/recordPatientExit")){

			char* recordID = NULL;
			char* exitDate = NULL;

			recordID = strtok(NULL," \n");
			exitDate = strtok(NULL," \n");

			if(recordID && exitDate)
				recordPatientExit(&record_list, disease_hash_table,  diseaseHashtableNumOfEntries, country_hash_table,  countryHashtableNumOfEntries,  recordID, exitDate);
			else{
				perror("error");
				//perror("Not enough arguments provided");
				break;
				//exit(EXIT_FAILURE);
			}
			
		}else if(!strcmp(command,"/numCurrentPatients")){ //still ill patients have record.exitDate == "-"
			char* disease = NULL;

			disease = strtok(NULL," \n");

			if(!disease)
				numCurrentPatients(disease_hash_table, diseaseHashtableNumOfEntries);
			else
				numCurrentPatients_disease(disease_hash_table, diseaseHashtableNumOfEntries, disease);

		}else if(!strcmp(command,"/exit")){
			printf("%s\n", "exiting");
			break;
		}else{
			//perror("error");
			perror("Unknown command");
			exit(EXIT_FAILURE);
		}

	}



	free_ht(disease_hash_table,diseaseHashtableNumOfEntries);
	free_ht(country_hash_table,countryHashtableNumOfEntries);

	free_list(record_list);

	/*close patientRecordsFile*/
	fclose(fd);

	/*free the memory alloc'd to store the patientRecordsFile string*/
	free(patientRecordsFile);

	exit(EXIT_SUCCESS);
}
