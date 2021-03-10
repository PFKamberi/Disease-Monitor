/*File:  Record.h*/

#ifndef _RECORD
#define _RECORD

typedef struct{
	char* recordID;
	char* patientFirstName;
	char* patientLastName;
	char* diseaseID;
	char* country;
	char* entryDate;
	char* exitDate;
} Record;

Record init_record(char* , char* , char* , char* , char* , char* , char* );

void delete_record(Record*);

void print_record(Record* );

int datecmp(Record , Record);

int get_recordID(Record* );

char* get_entryDate(Record*);

char* get_exitDate(Record* );

char* get_diseaseID(Record* );

char* get_country(Record* );

#endif









