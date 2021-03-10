/*File: query_functions.h*/

void globalDiseaseStats(ht_bucket** , int );

void globalDiseaseStats_dates(ht_bucket** , int , char* , char* );

void diseaseFrequency(ht_bucket** , int , char* , char*, char*);

void country_diseaseFrequency(ht_bucket** , int , char* , char* , char* , char* );

void country_diseaseFrequency(ht_bucket** , int , char* , char* , char* , char* );

void insertPatientRecord(lnode** , ht_bucket** , int , ht_bucket** , int , int , char* , char* , char* , char* , char* , char* , char* ); //line_count++ stin main

void recordPatientExit(lnode** , ht_bucket** , int , ht_bucket** , int ,  char* , char* );

void numCurrentPatients(ht_bucket** , int );

void  numCurrentPatients_disease(ht_bucket** , int , char* );

void topkDiseases(ht_bucket** , int , char* ,int );

void topkDiseases_dates(ht_bucket** , int , char* ,int , char* , char*);

void topkCountries(ht_bucket** , int , char* ,int );

void topkCountries_dates(ht_bucket** , int , char* ,int , char* , char* );