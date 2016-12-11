// queue.h

#ifndef __QUEUE_H__
#define __QUEUE_H__

class queue_init_t {
public:
  size_t size;
  size_t resize_factor;
};

// TODO: where do the const's go?
class queue_t {
public:
  // creation/deletion
  void queue_t(const queue_init_t& init) = 0;

  // information
  const size_t size() = 0;
  const void peek() = 0;

  // manipulation
  void add(const void& element) = 0;
  const void& remove() = 0;
};

#endif // __QUEUE_H__
