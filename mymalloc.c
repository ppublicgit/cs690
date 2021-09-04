#include "mymalloc.h"

#include <stdio.h>
#include <sys/mman.h>

node_t *head = 0;
int heapsize = 4096;


void *mymalloc(int size) {
  // Initialize heap if it is the first call to mymalloc
  if (head == 0) {
    // alllocate our heap space
    head = mmap(0, heapsize, PROT_READ|PROT_WRITE,
                MAP_ANON|MAP_PRIVATE, -1, 0);
    // create a dummy head node
    head->size = heapsize - sizeof(node_t);
    // create the first node in our free list that has all the remaining space
    node_t *node = head + sizeof(node_t);
    node->size = heapsize - sizeof(node_t) - sizeof(node_t);
    head->next = node;
    node->next = 0;
  }

  // create our pointer to return
  void *ptr;

  return findspace(size, ptr, head);
}

void *findspace(int size, void *ptr, node_t *node) {
  //if no next pointer, allocation does not fit
  if (node->next == 0) {
    ptr = 0;
  }
  //if allocation fits in next node than use that node
  else if (node->next->size >= size + sizeof(node_t)) {
    int tempsize = node->next->size;
    node_t *tempnode = node->next->next;
    ptr = node->next + sizeof(node_t);
    // if allocation uses up all space then remove node from freelist
    if (tempsize <= size + sizeof(node_t) + sizeof(node_t)) {
      node->next = tempnode;
    }
    // point current node->next to the remaining free space not used
    // by current allocation
    else {
      if (size == 1028) {
        printf("QWER\n");
      }
      node_t *newnode = node->next + sizeof(node_t) + size;
      node->next->size = size;
      if (size == 1028) {
        printf("%d\n", tempsize);
        printf("%p\t%d\n", node, node->size);
        printf("%p\t%d\n", node->next, node->next->size);
        printf("%p\n", node->next + node->next->size + sizeof(node_t));
        printf("%p\n", newnode);
        newnode->size = 0;
        printf("%d\n", newnode->size);
      }
      newnode->size = tempsize - size - sizeof(node_t);

      newnode->next = tempnode;
      node->next = newnode;

    }
  }
  // iterate to next node to see if it fits there
  else {
    ptr = findspace(size, ptr, node->next);
  }
  if (size == 1028) {
    printf("ASDF\n");
  }
  return ptr;
}

void myfree(void *ptr) {
  // pointer is not from our heap
  if ((node_t *)(ptr) < head || (node_t *)(ptr) > head + heapsize) {
    ;
  }
  // free list is empty
  else if (head->next == 0) {
    head->next = (node_t *)(ptr) - sizeof(node_t);
    head->next->next  = 0;
  }
  //find where our node belongs in the freelist
  else {
    node_t *node = head;
    int size = ((node_t *)(ptr) - sizeof(node_t))->size;
    node_t *tempnode;
    //find its position by walking the list forward
    while (node->next != 0 && node->next + sizeof(node_t) < (node_t *)(ptr)) {
      node = node->next;
    }
    tempnode = node->next;
    // left coalesce
    if (node != head && node + node->size + sizeof(node_t) + sizeof(node_t) == (node_t *)(ptr)) {
      node->size = node->size + sizeof(node_t) + size;
    }
    // insert a node after current node (dont left coalesce)
    else {
      node->next = (node_t *)(ptr) - sizeof(node_t);
      node = node->next;
      node->next = tempnode;
    }
    // right coalesce
    if (node->next == node->size + node + sizeof(node_t)) {
      node->size = node->size + sizeof(node_t) + node->next->size;
      node->next = node->next->next;
    }
  }
  return;
}

// Print the free list
void printFreeList() {
  printf("Printing Free List:\n");
  // check that we have allocated a heap
  if (head == 0) {
    printf("Head not allocated as no call to mymalloc yet\n\n");
    return;
  }
  // print head of heap
  printf("Head  : %p\n", head);
  node_t *node = head->next;
  int count = 0;
  // check for empty list
  if (node == 0) {
    printf("Empty Free List\n");
  }
  // print info for each node in the free list
  while (node != 0) {
    printf("Node %d: %p\tSize = %d\n", count, node, node->size);
    node = node->next;
    count++;
  }
  printf("\n\n");
  return;
}
