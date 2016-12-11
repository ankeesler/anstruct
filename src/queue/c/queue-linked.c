/* queue-linked.c */

#include "queue.h"

struct node_t {
  struct node_t *next;
  const void *data;
};

struct queue_t {
  struct node_t *head;
  struct node_t *tail; // TODO: config option for tail
  size_t size; // TODO: config option for size
};

/* creation/deletion */
struct queue_t *queue_alloc(struct queue_init_t *queue_init)
{
  struct queue_t *queue = malloc(sizeof(struct queue_t));
  queue->head = NULL;
  queue->tail = NULL;
  queue->size = 0;
  return queue;
}

void queue_free(struct queue_t *queue)
{
  struct node_t *node = queue->head;
  while (node != NULL) {
    free(node);
    node = node->next;
  }
  free(queue);
}

/* information */
size_t queue_size(const struct queue_t *queue)
{
  return queue->size;
}

const void *queue_peek(const struct queue_t *queue)
{
  return (queue->head != NULL ? queue->head->data : NULL);
}

/* manipulation */
void queue_add(struct queue_t *queue, const void *element)
{
  struct node_t *node = malloc(sizeof(struct node_t));
  if (queue->head == NULL) {
    queue->head = node;
  } else {
    queue->tail->next = node;
  }
  node->next = NULL;
  node->data = element;
  queue->tail = node;
  queue->size++;
}

const void *queue_remove(struct queue_t *queue)
{
  if (queue->size == 0) {
    return NULL;
  }

  struct node_t *node = queue->head;
  const void *data = node->data;
  queue->head = node->next;
  queue->size--;
  free(node);
  return data;
}
