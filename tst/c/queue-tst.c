/* queue-tst.c */

#include "src/queue/c/queue.h"
#include "tst/tst.h"

#define TINY   1
#define SMALL  10
#define MEDIUM 100
#define LARGE  1000
#define GIANT  10000

int main(int argc, char *argv[])
{
  tst_start();

  struct queue_init_t init;
  init.size = 3;
  init.resize_factor = 2;

  struct queue_t *queue = queue_alloc(&init);
  tst_expect(queue);

  size_t size = queue_size(queue);
  tst_expect_equals(size, 0);

  int data0 = TINY;
  queue_add(queue, &data0);

  size = queue_size(queue);
  tst_expect_equals(size, 1);

  const void *data = queue_peek(queue);
  tst_expect(data);
  tst_expect_equals(*(int *)data, TINY);

  int data1 = SMALL;
  queue_add(queue, &data1);

  size = queue_size(queue);
  tst_expect_equals(size, 2);

  data = queue_peek(queue);
  tst_expect(data);
  tst_expect_equals(*(int *)data, TINY);

  int data2 = MEDIUM;
  queue_add(queue, &data2);
  int data3 = LARGE;
  queue_add(queue, &data3);

  size = queue_size(queue);
  tst_expect_equals(size, 4);

  data = queue_peek(queue);
  tst_expect(data);
  tst_expect_equals(*(int *)data, TINY);

  int data4 = GIANT;
  queue_add(queue, &data4);

  size = queue_size(queue);
  tst_expect_equals(size, 5);

  data = queue_peek(queue);
  tst_expect(data);
  tst_expect_equals(*(int *)data, TINY);

  data = queue_remove(queue);
  tst_expect_equals(*(int *)data, TINY);
  
  size = queue_size(queue);
  tst_expect_equals(size, 4);

  data = queue_peek(queue);
  tst_expect(data);
  tst_expect_equals(*(int *)data, SMALL);

  data = queue_remove(queue);
  tst_expect_equals(*(int *)data, SMALL);

  data = queue_remove(queue);
  tst_expect_equals(*(int *)data, MEDIUM);

  data = queue_peek(queue);
  tst_expect(data);
  tst_expect_equals(*(int *)data, LARGE);

  queue_free(queue);

  tst_end();
  return 0;
}
