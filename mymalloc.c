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
      int size = (ptr-sizeof(header_t))->size + sizeof(header_t) - sizeof(node_t);
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
    }*/
  return;
}
