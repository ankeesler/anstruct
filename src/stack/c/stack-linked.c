/* stack-linked.c */

#include "stack.h"

struct node_t {
  struct node_t *previous;
  const void *data;
};

struct stack_t {
  struct node_t *head;
  size_t size; // TODO: config option for size
};

/* creation/deletion */
struct stack_t *stack_alloc(struct stack_init_t *stack_init)
{
  struct stack_t *stack = malloc(sizeof(struct stack_t));
  stack->head = NULL;
  stack->size = 0;
  return stack;
}

void stack_free(struct stack_t *stack)
{
  struct node_t *node = stack->head;
  while (node != NULL) {
    free(node);
    node = node->previous;
  }
  free(stack);
}

/* information */
size_t stack_size(const struct stack_t *stack)
{
  return stack->size;
}

const void *stack_peek(const struct stack_t *stack)
{
  return (stack->head != NULL ? stack->head->data : NULL);
}

/* manipulation */
void stack_push(struct stack_t *stack, const void *element)
{
  struct node_t *node = malloc(sizeof(struct node_t));
  node->previous = stack->head;
  node->data = element;
  stack->head = node;
  stack->size++;
}

const void *stack_pop(struct stack_t *stack)
{
  if (stack->size == 0) {
    return NULL;
  }

  struct node_t *node = stack->head;
  const void *data = node->data;
  stack->head = node->previous;
  stack->size--;
  free(node);
  return data;
}
