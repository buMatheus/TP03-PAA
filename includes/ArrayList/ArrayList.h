#ifndef ARRAYLIST
#define ARRAYLIST

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Node {
  void *item;
} Node;

typedef struct ArrayList {
  Node *array;
  int first, last;
} ArrayList;

//initialize 
void initializeArrayList(ArrayList *list);
//add
void addItemArrayList(ArrayList *list, void *item, unsigned long int item_size);
//remove
void removeItemInArray(ArrayList *list, int index_to_remove);

#endif