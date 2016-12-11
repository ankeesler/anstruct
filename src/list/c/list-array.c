/* list-array.c */

#include "list.h"

struct list_t {
  const void **data;
  size_t max_size;
  size_t cur_size;

  size_t resize_factor;
};

static void resize(struct list_t *list);
static int find(const struct list_t *list, const void *element, comparator_t comparator, size_t *index);

/* creation/deletion */
struct list_t *list_alloc(const struct list_init_t *list_init)
{
  struct list_t *list = malloc(sizeof(struct list_t));
  if (list == NULL) {
    return NULL;
  }

  list->data = malloc(sizeof(void *) * list_init->size);
  if (list->data == NULL) {
    return NULL;
  }

  list->max_size = list_init->size;
  list->cur_size = 0;
  list->resize_factor = list_init->resize_factor;

  return list;
}

void list_free(struct list_t *list)
{
  free(list->data);
  free(list);
}

/* information */
size_t list_size(const struct list_t *list)
{
  return list->cur_size;
}

const void *list_find(const struct list_t *list, const void *element, comparator_t comparator)
{
  size_t index;
  return (find(list, element, comparator, &index) ? list->data[index] : NULL);
}

const void *list_get(const struct list_t *list, size_t index)
{
  return (index < list->cur_size ? list->data[index] : NULL);
}

/* manipulation */
void list_addfront(struct list_t *list, const void *element)
{
  if (list->cur_size == list->max_size) {
    resize(list);
  }

  memmove(list->data + 1, list->data, list->cur_size * sizeof(list->data[0]));
  list->data[0] = element;
  list->cur_size++;
}

void list_addback(struct list_t *list, const void *element)
{
  if (list->cur_size == list->max_size) {
    resize(list);
  }

  list->data[list->cur_size++] = element;
}

const void *list_remove(struct list_t *list, const void *element, comparator_t comparator)
{
  size_t index;
  if (!find(list, element, comparator, &index)) {
    return NULL;  
  }

  const void *data = list->data[index];
  list->cur_size--;
  memmove(list->data + index, list->data + index + 1, list->cur_size * sizeof(list->data[0]));
  return data;
}

void list_reverse(struct list_t *list)
{
  if (list->cur_size == 0) {
    return;
  }

  size_t start = 0, end = list->cur_size - 1;
  while (start < end) {
    const void *tmp = list->data[end];
    list->data[end] = list->data[start];
    list->data[start] = tmp;
    start++;
    end--;
  }
}

static void resize(struct list_t *list)
{
  list->max_size *= list->resize_factor;
  const void **new_data = malloc(sizeof(void *) * list->max_size);
  memmove(new_data, list->data, list->cur_size * sizeof(list->data[0]));
  free(list->data);
  list->data = new_data;  
}

static int find(const struct list_t *list, const void *element, comparator_t comparator, size_t *index)
{
  *index = 0;
  while (*index < list->cur_size) {
    if (comparator(list->data[*index], element)) {
      return 1;
    }
    (*index)++;
  }
  return 0;
}
