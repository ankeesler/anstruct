/* stack.h */

#ifndef __STACK_H__
#define __STACK_H__

#include "c/types.h"

struct stack_t;

struct stack_init_t {
  size_t size;
  size_t resize_factor;
};

/* creation/deletion */
struct stack_t *stack_alloc(struct stack_init_t *stack_init);
void stack_free(struct stack_t *stack);

/* information */
size_t stack_size(const struct stack_t *stack);
const void *stack_peek(const struct stack_t *stack);

/* manipulation */
void stack_push(struct stack_t *stack, const void *element);
const void *stack_pop(struct stack_t *stack);

#endif /* __STACK_H__ */