#include "../../includes/Quicksort/Quicksort.h"

void swap(ArrayList *array, int left, int right)
{
  DecoderStructure *deocde_temp = (DecoderStructure*) array->array[left].item;

  array->array[left].item = (DecoderStructure*) array->array[right].item;

  array->array[right].item = deocde_temp;
}

int partition(ArrayList *array, int left, int right, int pivot_index)
{
  DecoderStructure decode = *(DecoderStructure*) array->array[pivot_index].item;
	int pivot_value = decode.occurrence;
	int store_index = left;
	int i;

	swap(array, pivot_index, right);
	for (i = left; i < right; i++) {
    DecoderStructure curr_decode = *(DecoderStructure*) array->array[i].item;
    if (curr_decode.occurrence >= pivot_value) {
			swap(array, i, store_index);
			++store_index;
		}
  }
		
	swap(array, store_index, right);
	return store_index;
}

void quicksort(ArrayList *array, int left, int right)
{
	int pivot_index = left;
	int pivot_new_index;

	if (right > left) {
		pivot_new_index = partition(array, left, right, pivot_index);
		quicksort(array, left, pivot_new_index - 1);
		quicksort(array, pivot_new_index + 1, right);
	}
}
