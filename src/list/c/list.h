/* list.h */

#ifndef __LIST_H__
#define __LIST_H__

#include "c/types.h"

struct list_t;

struct list_init_t {
  size_t size;
  size_t resize_factor;
};

/* creation/deletion */
struct list_t *list_alloc(const struct list_init_t *list_init);
void list_free(struct list_t *list);

/* information */
size_t list_size(const struct list_t *list);
const void *list_find(const struct list_t *list, const void *element, comparator_t comparator);
const void *list_get(const struct list_t *list, size_t index);

/* manipulation */
void list_addfront(struct list_t *list, const void *element);
void list_addback(struct list_t *list, const void *element);
const void *list_removefront(struct list_t *list); // TODO: implement me
const void *list_removeback(struct list_t *list); // TODO: implement me
const void *list_remove(struct list_t *list, const void *element, comparator_t comparator);
void list_reverse(struct list_t *list);
void list_insert(struct list_t *list, size_t index); // TODO: implement me

#endif /* __LIST_H__ */