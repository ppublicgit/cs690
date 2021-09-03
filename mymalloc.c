#include "mymalloc.h"

#include <stdio.h>

extern node_t *head;
extern int magic;


void *mymalloc(int size) {
  void *ptr = 0;

  if (head->next == 0) {
    return ptr;
  }
  else if (head->next->size >= size + sizeof(header_t)) {
    int tempsize = head->next->size;
    node_t *tempnode = head->next->next;
    header_t *header = head->next;
    header->size = size;
    header->magic = ++magic;
    ptr = head->next + sizeof(header_t);
    if (tempsize == size + sizeof(header_t)) {
      head->next = tempnode;
    }
    else {
      head->next = head->next + sizeof(header_t) + size;
      head->next->size = tempsize - size - sizeof(header_t);
    }
  }
  else {
    findspace(size, ptr, head->next);
  }

  return ptr;
}

void findspace(int size, void *ptr, node_t *node) {
  if (node->next == 0) {
    return;
  }
  if (node->next->size >= size + sizeof(header_t)) {
    int tempsize = node->next->size;
    node_t *tempnode = node->next->next;
    header_t *header = node->next;
    header->size = size;
    header->magic = ++magic;
    ptr = node->next + sizeof(header_t);
    if (tempsize == size + sizeof(header_t)) {
      node->next = tempnode;
    }
    else {
      node->next = node->next + sizeof(header_t) + size;
      node->next->size = tempsize - size - sizeof(header_t);
    }
  }
  else {
    findspace(size, ptr, node->next);
  }
  return;
}

void myfree(void *ptr) {
  return;
}
