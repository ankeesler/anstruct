/* sort.c */

#include <stdio.h>
static void print_array(int *array, int len)
{
  for (int i = 0; i < len; i++) {
    printf("%d ", array[i]);
  }
  printf("\n");
}

void insertion_sort(int *array, int len)
{
  // For each position in the array...
  for (int i = 0; i < len; i++) {
    // ...find the smallest element.
    int smallest = i;
    for (int j = i + 1; j < len; j++) {
      if (array[j] < array[smallest]) {
        smallest = j;
      }
    }
    if (smallest != i) {
      int tmp = array[i];
      array[i] = array[smallest];
      array[smallest] = tmp;
    }
  }
}
        
void bubble_sort(int *array, int len)
{
  // For each position in the array...
  for (int i = 0; i < len; i++) {
    // ...if a number is greater than the next, swap the two.
    print_array(array, len);
    for (int j = i; j < len - 1; j++) {
      if (array[j] > array[j + 1]) {
        int tmp = array[j];
        array[j] = array[j + 1];
        array[j + 1] = tmp;
      }
    }
  }
}
