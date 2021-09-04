#include "mymalloc.h"
#include <stdio.h>

int main() {
  printf("Starting...\n");
  char *ptr = (char *) mymalloc(8);
  printf("Ptr:  %p\n", ptr);
  char *ptr2 = mymalloc(8);
  printf("Ptr:  %p\n", ptr2);
  char *ptr3 = mymalloc(4000);
  printf("Ptr:  %p\n", ptr3);
  printf("Exiting...");
  return 0;
}
