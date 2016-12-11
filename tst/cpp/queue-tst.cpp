// queue-tst.cpp

#include "src/queue/cpp/queue.hpp"
#include "src/queue/cpp/queue-array.hpp"
#include "tst/tst.h"

#define TINY   1
#define SMALL  10
#define MEDIUM 100
#define LARGE  1000
#define GIANT  10000

static void run_queue_test(queue_t *queue);

int main(int argc, char *argv[])
{
  queue_init_t init;
  init.size = 3;
  init.resize_factor = 2;
  queue_t *queue = new queue_array_t(init);

  run_queue_test(queue);

  delete queue;

  return 0;
}

static void run_queue_test(queue_t *queue)
{
  size_t size = queue->size();
  tst_expect_equals(size, 0);

  int data0 = TINY;
  queue->add(&data0);

  size = queue->size();
  tst_expect_equals(size, 1);

  const void *data = queue->peek();
  tst_expect(data);
  tst_expect_equals(*(int *)data, TINY);

  int data1 = SMALL;
  queue->add(&data1);

  size = queue->size();
  tst_expect_equals(size, 2);

  data = queue->peek();
  tst_expect(data);
  tst_expect_equals(*(int *)data, TINY);

  int data2 = MEDIUM;
  queue->add(&data2);
  int data3 = LARGE;
  queue->add(&data3);

  size = queue->size();
  tst_expect_equals(size, 4);

  data = queue->peek();
  tst_expect(data);
  tst_expect_equals(*(int *)data, TINY);

  int data4 = GIANT;
  queue->add(&data4);

  size = queue->size();
  tst_expect_equals(size, 5);

  data = queue->peek();
  tst_expect(data);
  tst_expect_equals(*(int *)data, TINY);

  data = queue->remove();
  tst_expect_equals(*(int *)data, TINY);
  
  size = queue->size();
  tst_expect_equals(size, 4);

  data = queue->peek();
  tst_expect(data);
  tst_expect_equals(*(int *)data, SMALL);

  data = queue->remove();
  tst_expect_equals(*(int *)data, SMALL);

  data = queue->remove();
  tst_expect_equals(*(int *)data, MEDIUM);

  data = queue->peek();
  tst_expect(data);
  tst_expect_equals(*(int *)data, LARGE);  
}
