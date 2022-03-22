#include "../../includes/ArrayList/ArrayList.h"

void initializeArrayList(ArrayList *list) {
  list->first = 0;
  list->last = list->first;
}

void mallocItemMemoryAndAddToList(ArrayList *list, void *item,
                                  unsigned long int item_size) {
  list->array[list->last].item = malloc(item_size);
  memcpy(list->array[list->last].item, item, item_size);
  list->last++;

  return;
}

void addItemArrayList(ArrayList *list, void *item,
                      unsigned long int item_size) {
  if (list->last == list->first) {
    list->array = malloc(sizeof(Node));
    mallocItemMemoryAndAddToList(list, item, item_size);
    return;
  }

  // printf("\nlast %d", list->last);
  list->array = realloc(list->array, (list->last + 1) * sizeof(Node));
  mallocItemMemoryAndAddToList(list, item, item_size);

  return;
}

void removeItemInArray(ArrayList *list, int index_to_remove) {
  // lista esta vazia
  if (list->first == list->last || index_to_remove >= list->last) {
    printf("\nErro ao remover da lista. Lista vazia\n");
    return;
  }

  Node to_remove = list->array[index_to_remove];

  for (int aux = index_to_remove; aux < list->last - 1; aux++) {
    list->array[aux] = list->array[aux + 1];
  }
  list->last -= 1;
  free(to_remove.item);
};