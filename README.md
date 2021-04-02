# Disease-Monitor

A program that manipulates, processes, records and answers queries related to virus infection cases. 

## Application Interface:
 
The application is named diseaseMonitor and can be executed as follows: 

**./diseaseMonitor -p patientRecordsFile –h1 diseaseHashtableNumOfEntries –h2 countryHashtableNumOfEntries –b bucketSize** 

where:
* The parameter diseaseHashtableNumOfEntries stands for the number of buckets of a hash table where patient information is stored based on the patient's disease/ viral infection.
* The parameter countryHashtableNumOfEntries stands for the number of buckets of a hash table where patient information is stored based on the patient's country of origin.
* The parameter bucketSize stands for the size in Bytes of each hash table bucket.
* The parameter patientRecordsFile (or any other file name) is a file containing a collection of patient records to  be processed. Each line in the file describes an               infection case, the patient's name, the country of origin of the case,  the hospitalization date as well as the date when the patient was discharged. For instance if the         file contents  are:
                889 Mary Smith COVID-2019 China 25-1-2019 27-1-2019
                776 Larry Jones SARS-1 Italy 10-02-2003 –
                125 Jon Dupont H1N1 USA 12-02-2016 15-02-2016
       
   then there are three records describing three viral infection cases in three different countries (China, Italy, USA). In the second record there is no discharge date            (which implies that the patient is still hospitalized). In particular, a patient record is an ASCII text line consisting of the following elements:
      
   1. recordID: a unique identification number for each record.
   2. patientFirstName: a letter string without whitespaces.
   3. patientLastName: a letter string without whitespaces.
   4. diseaseID: a string consisting of letters, digits and in some cases dashes “-”, without whitespaces.
   5. country: a letter string without whitespaces.
   6. entryDate: the patient's hospitalization date. The date must have the following form DD-MM-YYYY.
   7. exitDate: the date when the patient was discharged from the hospital.ημερομηνία που βγήκε ο ασθενής από το νοσοκομείο.  The date must have the following form 
         DD-MM-YYYY. In case the a is still hospitalized (i.e there is no actual exitDate), the exitDate is denoted by a dash “-”.

    
                
                
      
