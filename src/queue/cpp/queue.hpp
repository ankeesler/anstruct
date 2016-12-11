// queue.h

#ifndef __QUEUE_HPP__
#define __QUEUE_HPP__

#include "cpp/types.h"

class queue_init_t {
public:
  size_t size;
  size_t resize_factor;
};

// TODO: where do the const's go?
class queue_t {
public:
  // creation/deletion
  virtual ~queue_t() { };

  // information
  virtual size_t size() = 0;
  virtual void *peek() = 0;

  // manipulation
  virtual void add(void *element) = 0;
  virtual void *remove() = 0;
};

#endif // __QUEUE_HPP__
