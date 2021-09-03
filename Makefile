#make file - this is a comment section

lib:
	gcc -c mymalloc.c
	ar -rc  libmymalloc.a mymalloc.o

main:
	gcc main.c -L. -lmymalloc -o main

clean:
	gcc -c mymalloc.c
	ar -rc  libmymalloc.a mymalloc.o
	gcc main.c -L. -lmymalloc -o main


debug:
	gcc -c -g mymalloc.c -o mymalloc_debug.o
	ar -rc libmymalloc_debug.a mymalloc_debug.o
	gcc -g main.c -L. -lmymalloc_debug -o main_debug
