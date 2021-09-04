#include "mymalloc.h"
#include <stdio.h>

int main() {
  printf("Starting...\n");
  printf("Allocating...\n");
  printFreeList();
  int *ptr = (int *) mymalloc(8);
  printFreeList();
  double *ptr2 = (double *) mymalloc(16);
  printFreeList();
  char *ptr3 = (char *) mymalloc(32);
  printFreeList();
  char *ptr4 = (char *) mymalloc(64);
  printFreeList();


  printf("Freeing...\n");
  myfree(ptr2);
  printFreeList();
  myfree(ptr3);
  printFreeList();
  myfree(ptr);
  printFreeList();
  myfree(ptr4);
  printFreeList();
  printf("Exiting...");

  return 0;
}
