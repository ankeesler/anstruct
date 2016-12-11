/* stack-array.c */

#include "stack.h"

struct stack_t {
  const void **data;
  size_t max_size;
  size_t cur_size;

  size_t resize_factor;
};

/* creation/deletion */
struct stack_t *stack_alloc(struct stack_init_t *stack_init)
{
  struct stack_t *stack = malloc(sizeof(struct stack_t));
  stack->data = malloc(stack_init->size * sizeof(void *));
  stack->max_size = stack_init->size;
  stack->cur_size = 0;
  return stack;
}

void stack_free(struct stack_t *stack)
{
  free(stack->data);
  free(stack);
}

/* information */
size_t stack_size(const struct stack_t *stack)
{
  return stack->cur_size;
}

const void *stack_peek(const struct stack_t *stack)
{
  return (stack->cur_size > 0 ? stack->data[stack->cur_size-1] : NULL);
}

/* manipulation */
void stack_push(struct stack_t *stack, const void *element)
{
  if (stack->cur_size == stack->max_size) {
    stack->max_size *= stack->resize_factor;
    const void **new_data = malloc(sizeof(void *) * stack->max_size);
    memmove(new_data, stack->data, stack->cur_size * sizeof(stack->data[0]));
    free(stack->data);
    stack->data = new_data;  
  }
  stack->data[stack->cur_size++] = element;
}

const void *stack_pop(struct stack_t *stack)
{
  return (stack->cur_size > 0 ? stack->data[--stack->cur_size] : NULL);
}
