// list.h

#ifndef __LIST_HPP__
#define __LIST_HPP__

#include "cpp/types.h"

class list_t {
public:
  // creation/deletion
  virtual ~list_t() { };

  // information
  virtual size_t size() const = 0;
  virtual const void *find(const void *element, comparator_t& comparator) const = 0;
  virtual const void *get(size_t index) const = 0;

  // manipulation
  virtual void addfront(const void *element) = 0;
  virtual void addback(const void *element) = 0;
  virtual const void *removefront(const void *element, comparator_t& comparator) = 0;
  virtual const void *removeback(const void *element, comparator_t& comparator) = 0;
  virtual const void *remove(const void *element, comparator_t& comparator) = 0;
  virtual void reverse() = 0;
  virtual void insert(const void *element, size_t index) = 0;
};

#endif // __LIST_HPP__
