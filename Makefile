goal: diseaseMonitor.o hash_table.o query_functions.o tree.o stack.o list.o record.o auxilary_functions.o heap.o
	gcc  diseaseMonitor.o hash_table.o query_functions.o tree.o stack.o list.o record.o auxilary_functions.o heap.o -o diseaseMonitor

diseaseMonitor.o: diseaseMonitor.c
	gcc -c diseaseMonitor.c

hash_table.o: hash_table.c
	gcc -c hash_table.c

query_functions.o: query_functions.c
	gcc -c query_functions.c

heap.o: heap.c
	gcc -c heap.c

tree.o: tree.c
	gcc -c tree.c

stack.o: stack.c
	gcc -c stack.c

list.o: list.c
	gcc -c record.c

record.o: record.c
	gcc -c record.c

auxilary_functions.o: auxilary_functions.c
	gcc -c auxilary_functions.c

