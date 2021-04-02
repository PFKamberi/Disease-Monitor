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

As the application starts, the patientRecordsFile is opened, read record by record, each record is checked for its validation and the data structures used for query answering are initialized and stored in memory. When the application finishes the patientRecordsFile processing, it waits for user input. The user can give the following commands (arguments enclosed in [ ] are optional):

* **/globalDiseaseStats \[date1 date2\]** <br/>
The application prints for each virus the number of viral infection cases recorded in the system. If the arguments date1 and date2 are given, then the application prints for each type of virus the number of viral infections recorded in the system in the time period between date1 and date2. If date1 argument is given, then date2 argument must be given as well, otherwise an error message appears.
* **/diseaseFrequency virusName \[country\] date1 date2** <br/>
If country argument is not given, then the application prints for virusName infection the number of viral infection cases recorded in the system in the time period between date1 and date2. If country argument is given, the application prints for the virusName infection, the number of viral infection cases found in this particular country and recorded in the system in the time period between date1 and date2.
* **/topk-Diseases k country \[date1 date2\]** <br/>
The application prints for the top k viral infections with the most recorded cases in the country in the time period between date1 and date2, in case date1 and date2 arguments are given.If date1 argument is given, then date2 argument must be given as well, otherwise an error message appears.
* **/topk-Countries k disease \[date1 date2\]** <br/>
The application prints for disease virus the top k countries with the most viral infection cases from disease virus.
* **/insertPatientRecord recordID patientFirstName patientLastName diseaseID entryDate \[exitDate\]**
The application enters a new record in the system. ExitDate is optional.
* **/recordPatientExit recordID exitDate** <br/>
The application adds an exitDate into the record with ID recordID.
* **/numCurrentPatients \[disease\]** <br/>
If disease is given, the application prints the number of patients that are still hospitalized with due to disease viral infection. If disease argument is not given, the application prints for each virus the records of the patients that are still hospitalized.
* **/exit** <br/>
The application terminates.
                
<!---
Δομές δεδομένων
Για την υλοποίηση της εφαρμογής μπορείτε να χρησιμοποιήσετε C ή C++. Δεν μπορείτε να χρησιμοποιήσετε
όμως την Standard Template Library (STL). Όλες οι δομές δεδομένων θα πρέπει να υλοποιηθούν από εσάς.
Βεβαιωθείτε πως δεσμεύετε μόνο όση μνήμη χρειάζεται, π.χ. η ακόλουθη τακτική δε συνιστάται:
int diseases[512];// store up to 512 diseases, but really we don’t know how many
Επίσης βεβαιωθείτε πως απελευθερώνετε τη μνήμη σωστά κατά την εκτέλεση του προγράμματός σας αλλά
και κατά την έξοδο.
Για να ολοκληρώσετε την άσκηση θα χρειαστεί, μεταξύ άλλων, να υλοποιήσετε τις εξής δομές δεδομένων.
1. Δύο πίνακες κατακερματισμού (diseaseHashTable και countryHashTable) που με index
προσφέρουν γρήγορες προσπελάσεις σε στοιχεία ασθενών ανά κρούσμα και κρουσμάτων ανά χώρα. Οι
πίνακες κατακερματισμού θα χρησιμοποιούν κουβάδες για να εξυπηρετήσουν diseases/countries
που παρουσιάζουν «σύγκρουση»/collision (δηλαδή, το αποτέλεσμα της συνάρτησης κατακερματισμού
οδηγεί στο ίδιο στοιχείο του hash table). Αν χρειάζονται πιο πολλοί από ένα κουβάδες για να
αποθηκευτούν δεδομένα, δημιουργούνται δυναμικά και διατάσσονται σε μια λίστα.
2. Για κάθε disease που γίνεται hashed σε ένα στοιχείο του diseaseHashTable, υπάρχει ένα σύνολο
από εγγραφές ασθενών που έχουν νοσηλευτεί λόγω της ίωσης disease. Αυτό το σύνολο τοποθετείται
σε ένα balanced binary search tree. Κάθε κόμβος του δέντρου παρέχει στοιχεία (η προσπέλαση σε
στοιχεία, δείτε Σχήμα 1) μιας εγγραφής ασθενούς. Το δέντρο θα πρέπει να είναι ταξινομημένο με βάση
την ημερομηνία εισαγωγής του ασθενούς στο νοσοκομείο.
3. Για κάθε country που γίνεται hashed σε ένα στοιχείο του countryHashTable, υπάρχει ένα σύνολο
από εγγραφές ασθενών που έχουν νοσηλευτεί στην χώρα country. Αυτό το σύνολο τοποθετείται σε
ένα balanced binary search tree όπου κάθε κόμβος του δέντρου παρέχει στοιχεία (η προσπέλαση σε
στοιχεία) εγγραφής ασθενούς. Το δέντρο θα πρέπει να είναι ταξινομημένο με βάση την ημερομηνία
εισαγωγής του ασθενούς στο νοσοκομείο.
Επειδή θα υπάρχει επικάλυψη μεταξύ των εγγραφών στα δέντρα που προσπελάζονται μέσω
diseaseHashTable και countryHashTable θα πρέπει να φροντίζετε να μην υπάρχει σπατάλη
στην μνήμη, δηλαδή μια εγγραφή θα πρέπει να αποθηκεύεται μόνο μια φορά στην μνήμη και σε
οποιαδήποτε δομή δεδομένων χρειάζεται πρόσβαση στην εγγραφή, η πρόσβαση θα γίνεται μέσω
pointers. (δείτε Σχήμα 1 για μια πιθανή πρόταση του layout κάποιων δομών δεδομένων).
4. Για την εντολή topk-Diseases, το πρόγραμμα σας θα πρέπει να χτίζει on-the-fly ένα binary heap
(i.e., max heap) όπου κάθε κόμβος θα κρατάει το σύνολο των κρουσμάτων μιας ίωσης και θα σας
βοηθά να βρίσκετε εύκολα ποιες είναι οι ιώσεις που αποτελούν το top k των κρουσμάτων στη χώρα.
Επίσης για την εντολή topk-Countries, το πρόγραμμά σας θα πρέπει να χτίζει on-the-fly ένα binary
heap (i.e., max heap) όπου κάθε κόμβος θα κρατάει το σύνολο κρουσμάτων μιας χώρας της
συγκεκριμένης ίωσης και θα σας βοήθα να βρίσκετε εύκολα ποιες είναι οι χώρες που έχουν εμφανίσει
το top k των κρουσμάτων της συγκεκριμένη ίωσης.
5. Οποιαδήποτε άλλη βοηθητική δομή δεδομένων χρειαστείτε για τις ανάγκες της εργασίας
--->
                
                
      
