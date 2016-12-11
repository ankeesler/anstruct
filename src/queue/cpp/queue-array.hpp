// queue-array.hpp

#ifndef __QUEUE_ARRAY_HPP__
#define __QUEUE_ARRAY_HPP__

class queue_array_t : public queue_t {
public:
  // creation/deletion
  queue_array_t(const queue_init_t& init);
  ~queue_array_t();
  
  // information
  size_t size();
  void *peek();

  // manipulation
  void add(void *element);
  void *remove();

private:
  void **data;
  size_t cur_size;
  size_t max_size;

  size_t resize_factor;
};

#endif //__QUEUE_ARRAY_HPP__