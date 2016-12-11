/* list-linked.c */

#include "list.h"

struct node_t {
  struct node_t *next;
  struct node_t *previous; // TODO: config option for previous
  const void *data;
};

struct list_t {
  struct node_t *head;
  struct node_t *tail; // TODO: config option for tail
  size_t size; // TODO: config option for size
};

struct node_t *node_alloc(const void *data);
struct node_t *find(const struct list_t *list, const void *element, comparator_t comparator);

/* creation/deletion */
struct list_t *list_alloc(const struct list_init_t *list_init)
{
  struct list_t *list = malloc(sizeof(struct list_t));
  list->head = NULL;
  list->tail = NULL;
  list->size = 0;
  return list;
}

void list_free(struct list_t *list)
{
  struct node_t *node = list->head;
  while (node != NULL) {
    free(node);
    node = node->next;
  }
  free(list);
}

/* information */
size_t list_size(const struct list_t *list)
{
  return list->size;
}

const void *list_find(const struct list_t *list, const void *element, comparator_t comparator)
{
  struct node_t *node = find(list, element, comparator);
  return (node == NULL ? NULL : node->data);  
}

const void *list_get(const struct list_t *list, size_t index)
{
  struct node_t *node = list->head;
  while (node != NULL && index != 0) {
    node = node->next;
    index--;
  }
  return (node == NULL ? NULL : node->data);
}

/* manipulation */
void list_addfront(struct list_t *list, const void *element)
{
  if (list->head == NULL) {
    list->head = node_alloc(element);
    list->tail = list->head;
  } else {
    struct node_t *node = node_alloc(element);
    node->next = list->head;
    list->head->previous = node;
    list->head = node;
  }
  list->size++;
}

void list_addback(struct list_t *list, const void *element)
{
  if (list->head == NULL) {
    list->head = node_alloc(element);
    list->tail = list->head;
  } else {
    struct node_t *node = node_alloc(element);
    node->previous = list->tail;
    list->tail->next = node;
    list->tail = node;
  }
  list->size++;
}

const void *list_remove(struct list_t *list, const void *element, comparator_t comparator)
{
  struct node_t *node = find(list, element, comparator);
  if (node == NULL) {
    return NULL;
  }

  const void *data = node->data;
  int head = (node->previous == NULL);
  int tail = (node->next == NULL);
  if (head && tail) {
    list->head = NULL;
    list->tail = NULL;
  } else if (head && !tail) {
    list->head = node->next;
    list->head->previous = NULL;
  } else if (!head && tail) {
    list->tail = node->previous;
    list->tail->next = NULL;    
  } else { // !head && !tail
    node->previous->next = node->next;
    node->next->previous = node->previous;
  }
  free(node);
  list->size--;
  return data;
}

void list_reverse(struct list_t *list)
{
  struct node_t *node = list->head;
  while (node != NULL) {
    struct node_t *next = node->next;
    node->next = node->previous;
    node->previous = next;
    node = next;
  }
  struct node_t *old_head = list->head;
  list->head = list->tail;
  list->tail = old_head;
}

struct node_t *node_alloc(const void *data)
{
  struct node_t *node = malloc(sizeof(struct node_t));
  node->next = NULL;
  node->previous = NULL;
  node->data = data;
  return node;
}

struct node_t *find(const struct list_t *list, const void *element, comparator_t comparator)
{
  struct node_t *node = list->head;
  while (node != NULL && !comparator(node->data, element)) {
    node = node->next;
  }
  return node;
}
