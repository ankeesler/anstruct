/* list-tst.c */

#include "src/list/c/list.h"
#include "tst/tst.h"

#define TINY   1
#define SMALL  10
#define MEDIUM 100
#define LARGE  1000
#define GIANT  10000

static int integer_comparator(const void *arg0, const void *arg1);

int main(int argc, char *argv[])
{
  tst_start();

  struct list_init_t init;
  init.size = 3;
  init.resize_factor = 2;

  struct list_t *list = list_alloc(&init);
  tst_expect(list);

  size_t size = list_size(list);
  tst_expect_equals(size, 0);

  int data0 = TINY;
  list_addback(list, &data0);

  size = list_size(list);
  tst_expect_equals(size, 1);

  const void *data = list_get(list, 0);
  tst_expect(data);
  tst_expect_equals(*(int *)data, TINY);

  int data1 = SMALL;
  list_addback(list, &data1);

  size = list_size(list);
  tst_expect_equals(size, 2);

  data = list_get(list, 0);
  tst_expect(data);
  tst_expect_equals(*(int *)data, TINY);
  data = list_get(list, 1);
  tst_expect(data);
  tst_expect_equals(*(int *)data, SMALL);

  int data2 = MEDIUM;
  list_addback(list, &data2);
  int data3 = LARGE;
  list_addback(list, &data3);

  size = list_size(list);
  tst_expect_equals(size, 4);

  data = list_get(list, 0);
  tst_expect_equals(*(int *)data, TINY);
  data = list_get(list, 1);
  tst_expect_equals(*(int *)data, SMALL);
  data = list_get(list, 2);
  tst_expect_equals(*(int *)data, MEDIUM);
  data = list_get(list, 3);
  tst_expect_equals(*(int *)data, LARGE);

  int data4 = GIANT;
  list_addfront(list, &data4);

  size = list_size(list);
  tst_expect_equals(size, 5);

  data = list_get(list, 0);
  tst_expect_equals(*(int *)data, GIANT);
  data = list_get(list, 1);
  tst_expect_equals(*(int *)data, TINY);
  data = list_get(list, 2);
  tst_expect_equals(*(int *)data, SMALL);
  data = list_get(list, 3);
  tst_expect_equals(*(int *)data, MEDIUM);
  data = list_get(list, 4);
  tst_expect_equals(*(int *)data, LARGE);

  data = list_find(list, &data0, integer_comparator);
  tst_expect(data);
  tst_expect_equals(data0, *(int *)data);

  int dataX = -1;
  data = list_find(list, &dataX, integer_comparator);
  tst_expect(!data);

  data = list_remove(list, &dataX, integer_comparator);
  tst_expect(!data);

  data = list_remove(list, &data0, integer_comparator);
  tst_expect(data);
  tst_expect_equals(data0, *(int *)data);

  size = list_size(list);
  tst_expect_equals(size, 4);

  data = list_get(list, 0);
  tst_expect_equals(*(int *)data, GIANT);
  data = list_get(list, 1);
  tst_expect_equals(*(int *)data, SMALL);
  data = list_get(list, 2);
  tst_expect_equals(*(int *)data, MEDIUM);
  data = list_get(list, 3);
  tst_expect_equals(*(int *)data, LARGE);

  list_addback(list, &data0);

  size = list_size(list);
  tst_expect_equals(size, 5);

  data = list_get(list, 0);
  tst_expect_equals(*(int *)data, GIANT);
  data = list_get(list, 1);
  tst_expect_equals(*(int *)data, SMALL);
  data = list_get(list, 2);
  tst_expect_equals(*(int *)data, MEDIUM);
  data = list_get(list, 3);
  tst_expect_equals(*(int *)data, LARGE);
  data = list_get(list, 4);
  tst_expect_equals(*(int *)data, TINY);

  list_reverse(list);
  data = list_get(list, 0);
  tst_expect_equals(*(int *)data, TINY);
  data = list_get(list, 1);
  tst_expect_equals(*(int *)data, LARGE);
  data = list_get(list, 2);
  tst_expect_equals(*(int *)data, MEDIUM);
  data = list_get(list, 3);
  tst_expect_equals(*(int *)data, SMALL);
  data = list_get(list, 4);
  tst_expect_equals(*(int *)data, GIANT);

  list_free(list);

  tst_end();
  return 0;
}

static int integer_comparator(const void *arg0, const void *arg1)
{
  return (*(long *)arg0 == *(long *)arg1);
}