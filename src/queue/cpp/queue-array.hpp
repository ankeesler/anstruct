// queue-array.hpp

#ifndef __QUEUE_ARRAY_HPP__
#define __QUEUE_ARRAY_HPP__

#include "queue.hpp"

class queue_array_t : public queue_t {
public:
  // creation/deletion
  queue_array_t(const queue_init_t& init);
  ~queue_array_t();
  
  // information
  size_t size() const;
  const void *peek() const;

  // manipulation
  void add(const void *element);
  const void *remove();

private:
  size_t cur_size;
  size_t max_size;
  size_t resize_factor;
  const void **data;
};

#endif //__QUEUE_ARRAY_HPP__