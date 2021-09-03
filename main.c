#include "mymalloc.h"
#include <sys/mman.h>
#include <stdio.h>

// Make heap global
node_t *head;
int magic = 1;

int main() {
  printf("Starting...\n");

  // Initialize heap
  head = mmap(0, 4096, PROT_READ|PROT_WRITE,
                    MAP_ANON|MAP_PRIVATE, -1, 0);
  head->size = 4096 - sizeof(node_t);
  node_t *node = head + sizeof(node_t);
  node->size = 4096 - sizeof(node_t) - sizeof(node_t);
  head->next = node;
  node->next = 0;

  printf("Hed:  %p\n", head);
  char *ptr = mymalloc(100);
  printf("Ptr:  %p\n", ptr);
  char *ptr2 = mymalloc(100);
  printf("Ptr:  %p\n", ptr2);
  char *ptr3 = mymalloc(4000);
  printf("Ptr:  %p\n", ptr3);
  printf("Exiting...");
  return 0;
}
