#include "mymalloc.h"

#include <stdio.h>
#include <sys/mman.h>

node_t *head = 0;


void *mymalloc(int size) {
  // Initialize heap if it is the first call to mymalloc
  if (head == 0) {
    // alllocate our heap space
    head = mmap(0, 4096, PROT_READ|PROT_WRITE,
                MAP_ANON|MAP_PRIVATE, -1, 0);
    // create a dummy head node
    head->size = 4096 - sizeof(node_t);
    // create the first node in our free list that has all the remaining space
    node_t *node = head + sizeof(node_t);
    node->size = 4096 - sizeof(node_t) - sizeof(node_t);
    head->next = node;
    node->next = 0;
    printf("Hed:  %p\n", head);
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
      node_t *newnode = node->next + sizeof(node_t) + size;
      node->next->size = size;
      newnode->size = tempsize - size - sizeof(node_t);
      newnode->next = tempnode;
      head->next = newnode;
    }
  }
  // iterate to next node to see if it fits there
  else {
    ptr = findspace(size, ptr, node->next);
  }
  return ptr;
}

void myfree(void *ptr) {/*
  if (head->next == 0) { //free list is empty
    node_t *newnode;
    int size = (ptr-sizeof(header_t))->size + sizeof(header_t) - sizeof(node_t);
    newnode = ptr - sizeof(header_t);
    newnode->size = size;
    newnode->next = 0;
    head->next = newnode;
  }
  else { //have to find where in free list this space goes
    node_t *node = head;
    //find its position by walking the list forward
    while ((node->next != 0) && (node->next + node->next->size + sizeof(node_t) < ptr - sizeof(header_t))) {
      node = node->next;
    }
    if (node->next == 0 && node + node->size + sizeof(node_t) != ptr - sizeof(header_t)) { // append to free list
      node_t *newnode;
      int size = (header_t*)(ptr-sizeof(header_t))->size + sizeof(header_t) - sizeof(node_t);
      newnode = ptr - sizeof(header_t);
      newnode->size = size;
      newnode->next = 0;
      node->next = newnode;
    }
    else if (node->next == 0) { // coalesce last node and new space
      node->size = node->size + (ptr-sizeof(header_t))->size + sizeof(header_t);
    }
    else { //internal node in list
      int coalesced = 0;
      if (node->next + node->next->size + sizeof(node_t) == ptr - sizeof(header_t)) { //coalesce left
        node->next->size = node->next->size + sizeof(header_t) + (ptr - sizeof(header_t))->size;
        coalesced = 1;
      }
      if (node->next + node->next->size + sizeof(node_t) == node->next->next) { //coalesce right
        node->next->size = node->next->size + sizeof(node_t) + node->next->next->size;
        node->next->next = node->next->next->next;
        coalesced = 1;
      }
      if (coalesced == 0) {
        node_t *newnode;
        int size = (ptr-sizeof(header_t))->size + sizeof(header_t) - sizeof(node_t);
        newnode = ptr - sizeof(header_t);
        newnode->size = size;
        newnode->next = node->next->next;
        node->next = newnode;
      }
    }
  }
                        */
  return;
}
