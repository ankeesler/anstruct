// queue.h

#ifndef __QUEUE_HPP__
#define __QUEUE_HPP__

#include "cpp/types.h"

class queue_init_t {
public:
  size_t size;
  size_t resize_factor;
};

class queue_t {
public:
  // creation/deletion
  virtual ~queue_t() { };

  // information
  virtual size_t size() const = 0;
  virtual const void *peek() const = 0;

  // manipulation
  virtual void add(const void *element) = 0;
  virtual const void *remove() = 0;
};

#endif // __QUEUE_HPP__
