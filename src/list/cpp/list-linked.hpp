// list-linked.h

#ifndef __LIST_LINKED_HPP__
#define __LIST_LINKED_HPP__

#include "list.hpp"

class list_linked_t : public list_t {
public:
  // creation/deletion
  ~list_linked_t();

  // information
  size_t size() const;
  const void *find(const void *element, comparator_t& comparator) const;
  const void *get(size_t index) const;

  // manipulation
  void addfront(const void *element);
  void addback(const void *element);
  const void *removefront(const void *element, comparator_t& comparator); // TODO: implement me
  const void *removeback(const void *element, comparator_t& comparator); // TODO: implement me
  const void *remove(const void *element, comparator_t& comparator);
  void reverse();
  void insert(const void *element, size_t index); // TODO: implement me

private:
  class node_t {
  public:
    node_t(const void *data)
    {
      this->data = data;
      this->next = NULL;
      this->previous = NULL;
    }

    const void *data;
    node_t *next;
    node_t *previous; // TODO: config option for tail
  };

  node_t *head;
  node_t *tail; // TODO: config option for tail
  size_t cur_size; // TODO: config option for cur_size
};

#endif // __LIST_LINKED_HPP__
