/* stack-tst.c */

#include "src/stack/c/stack.h"
#include "tst/tst.h"

#define TINY   1
#define SMALL  10
#define MEDIUM 100
#define LARGE  1000
#define GIANT  10000

int main(int argc, char *argv[])
{
  tst_start();

  struct stack_init_t init;
  init.size = 3;
  init.resize_factor = 2;

  struct stack_t *stack = stack_alloc(&init);
  tst_expect(stack);

  size_t size = stack_size(stack);
  tst_expect_equals(size, 0);

  int data0 = TINY;
  stack_push(stack, &data0);

  size = stack_size(stack);
  tst_expect_equals(size, 1);

  const void *data = stack_peek(stack);
  tst_expect(data);
  tst_expect_equals(*(int *)data, TINY);

  int data1 = SMALL;
  stack_push(stack, &data1);

  size = stack_size(stack);
  tst_expect_equals(size, 2);

  data = stack_peek(stack);
  tst_expect(data);
  tst_expect_equals(*(int *)data, SMALL);

  int data2 = MEDIUM;
  stack_push(stack, &data2);
  int data3 = LARGE;
  stack_push(stack, &data3);

  size = stack_size(stack);
  tst_expect_equals(size, 4);

  data = stack_peek(stack);
  tst_expect(data);
  tst_expect_equals(*(int *)data, LARGE);

  int data4 = GIANT;
  stack_push(stack, &data4);

  size = stack_size(stack);
  tst_expect_equals(size, 5);

  data = stack_peek(stack);
  tst_expect(data);
  tst_expect_equals(*(int *)data, GIANT);

  data = stack_pop(stack);
  tst_expect_equals(*(int *)data, GIANT);
  
  size = stack_size(stack);
  tst_expect_equals(size, 4);

  data = stack_pop(stack);
  tst_expect_equals(*(int *)data, LARGE);

  data = stack_pop(stack);
  tst_expect_equals(*(int *)data, MEDIUM);

  data = stack_peek(stack);
  tst_expect(data);
  tst_expect_equals(*(int *)data, SMALL);

  stack_free(stack);

  tst_end();
  return 0;
}
