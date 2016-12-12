// list-linked.h

#ifndef __LIST_LINKED_HPP__
#define __LIST_LINKED_HPP__

#include "list.hpp"

class list_linked_t : public list_t {
public:
  // information
  size_t size() const;
  const void *find(const void *element, comparator_t& comparator) const;
  const void *get(size_t index) const;

  // manipulation
  void addfront(const void *element);
  void addback(const void *element);
  void removefront(const void *element, comparator_t& comparator);
  void removeback(const void *element, comparator_t& comparator);
  void remove(const void *element, comparator_t& comparator);
  void reverse();
  void insert(const void *element, size_t index);
};

#endif // __LIST_LINKED_HPP__
