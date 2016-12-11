/* queue-array.c */

#include "queue.h"

struct queue_t {
  const void **data;
  size_t max_size;
  size_t cur_size;

  size_t resize_factor;
};

/* creation/deletion */
struct queue_t *queue_alloc(struct queue_init_t *queue_init)
{
  struct queue_t *queue = malloc(sizeof(struct queue_t));
  queue->data = malloc(queue_init->size * sizeof(void *));
  queue->max_size = queue_init->size;
  queue->cur_size = 0;
  return queue;
}

void queue_free(struct queue_t *queue)
{
  free(queue->data);
  free(queue);
}

/* information */
size_t queue_size(const struct queue_t *queue)
{
  return queue->cur_size;
}

const void *queue_peek(const struct queue_t *queue)
{
  return (queue->cur_size > 0 ? queue->data[0] : NULL);
}

/* manipulation */
void queue_add(struct queue_t *queue, const void *element)
{
  if (queue->cur_size == queue->max_size) {
    queue->max_size *= queue->resize_factor;
    const void **new_data = malloc(sizeof(void *) * queue->max_size);
    memmove(new_data, queue->data, queue->cur_size * sizeof(queue->data[0]));
    free(queue->data);
    queue->data = new_data;
  }
  queue->data[queue->cur_size++] = element;
}

const void *queue_remove(struct queue_t *queue)
{
  const void *data = queue_peek(queue);
  if (data != NULL) {
    queue->cur_size--;
    memmove(queue->data, queue->data + 1, queue->cur_size * sizeof(data));
  }
  return data;
}
