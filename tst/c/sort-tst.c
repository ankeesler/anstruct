/* sort-tst.c */

#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <stdio.h>

#include "tst/tst.h"

#define SIZE(a) (sizeof((a)) / sizeof((a)[0]))

static int is_sorted(int *array, int length)
{
  for (int i = 1; i < length; i++) {
    if (array[i] < array[i-1]) {
      return 0;
    }
  }
  return 1;
}

typedef enum {
  SORTED_SIMILAR,
  SORTED_CONTIGUOUS,
  SORTED_SPACED,
  REVERSED_SIMILAR,
  REVERSED_CONTIGUOUS,
  REVERSED_SPACED,
  RANDOM,
  MAXIMUM,
} array_type_t;

static int *make_array(array_type_t type, int size)
{
  int *array = malloc(size * sizeof(int));
  switch (type) {
  case SORTED_SIMILAR:
    for (int i = 0; i < size; i++) {
      array[i] = i >> 1;
    }
    break;
  case SORTED_CONTIGUOUS:
    for (int i = 0; i < size; i++) {
      array[i] = i;
    }
    break;
  case SORTED_SPACED:
    for (int i = 0; i < size; i++) {
      array[i] = i << 1;
    }
    break;
  case REVERSED_SIMILAR:
    for (int i = 0; i < size; i++) {
      array[i] = (size - i) >> 1;
    }
    break;
  case REVERSED_CONTIGUOUS:
    for (int i = 0; i < size; i++) {
      array[i] = size - i;
    }
    break;
  case REVERSED_SPACED:
    for (int i = 0; i < size; i++) {
      array[i] = (size - i) << 1;
    }
    break;
  case RANDOM:
    for (int i = 0; i < size; i++) {
      array[i] = rand();
    }
    break;
  default:
    tst_expect(0);
  }
  return array;
}

int main(int argc, char *argv[])
{
  tst_start();

  srand(time(NULL));

  int small_sorted[] = {1, 2, 3};
  tst_expect(is_sorted(small_sorted, SIZE(small_sorted)));

  int small_unsorted[] = {3, 1, 2};
  tst_expect(!is_sorted(small_unsorted, SIZE(small_unsorted)));

  int small_backwards[] = {3, 2, 1};
  tst_expect(!is_sorted(small_backwards, SIZE(small_backwards)));

  int small_other[] = {1, 3, 1};
  tst_expect(!is_sorted(small_other, SIZE(small_other)));

  FILE *results = fopen("results.csv", "w");
  extern void insertion_sort(int *array, int len);
  extern void bubble_sort(int *array, int len);
  typedef void (*sorter_t)(int *, int);
  const char *names[] = { "insertion", "bubble", };
  const sorter_t sorters[] = { insertion_sort, bubble_sort, };
  int sizes[] = { 1e1, 1e2, 1e3, 1e4, };//1e5, 1e6, 1e7, 1e8, 1e9 };
  // For each implementation...
  for (int i = 0; i < SIZE(sorters); i++) {
    printf("(%s)\n", names[i]);
    // ...and each size...
    for (int j = 0; j < SIZE(sizes); j++) {
    // ...and each type of array...
      for (int type = 0; type < MAXIMUM; type++) {
        // ...run the test.
        struct timeval start, end;
        int *array = make_array(type, sizes[j]);
        gettimeofday(&start, NULL);
        (*(sorters[i]))(array, sizes[j]);
        gettimeofday(&end, NULL);
        fprintf(results, "%s, %d, %d, %ld,\n",
                names[i],
                sizes[j],
                type,
                (((end.tv_sec * 1000000) + end.tv_usec)
                 - ((start.tv_sec * 1000000) + start.tv_usec)));
        tst_expect(is_sorted(array, sizes[j]));
        free(array);
      }
    }
  }
  tst_expect_equals(fclose(results), 0);

  tst_end();
  return 0;
}
