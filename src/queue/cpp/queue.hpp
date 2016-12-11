// queue.h

#ifndef __QUEUE_H__
#define __QUEUE_H__

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
  virtual void init(const queue_init_t& init) = 0;

  // information
  virtual size_t size() = 0;
  //virtual const void peek() = 0;

  // manipulation
  //virtual void add(const void& element) = 0;
  //virtual const void& remove() = 0;
};

#endif // __QUEUE_H__
