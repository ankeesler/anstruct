/* queue.h */

#ifndef __STACK_H__
#define __STACK_H__

#include "c/types.h"

struct queue_t;

struct queue_init_t {
  size_t size;
  size_t resize_factor;
};

/* creation/deletion */
struct queue_t *queue_alloc(struct queue_init_t *queue_init);
void queue_free(struct queue_t *queue);

/* information */
size_t queue_size(const struct queue_t *queue);
const void *queue_peek(const struct queue_t *queue);

/* manipulation */
void queue_add(struct queue_t *queue, const void *element);
const void *queue_remove(struct queue_t *queue);

#endif /* __QUEUE_H__ */
