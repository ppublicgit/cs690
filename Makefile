#make file - this is a comment section

lib:
	clang -c mymalloc.c
	ar -rc  libmymalloc.a mymalloc.o

main:
	clang main.c -L. -lmymalloc -o main

clean:
	clang -c mymalloc.c
	ar -rc  libmymalloc.a mymalloc.o
	clang main.c -L. -lmymalloc -o main


debug:
	clang -c -g mymalloc.c -o mymalloc_debug.o
	ar -rc libmymalloc_debug.a mymalloc_debug.o
	clang -g main.c -L. -lmymalloc_debug -o main_debug
