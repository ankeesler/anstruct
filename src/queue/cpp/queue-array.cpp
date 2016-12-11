// queue-array.cpp

#include "queue.hpp"

class queue_array_t : public queue_t {
public:
  // creation/deletion
  //queue_array_t();
  //~queue_array_t();
  
  // information
  size_t size();
  //void& peek();

  // manipulation
  //void add(const void& element);
  //void& remove();

private:
  //void **data;
  size_t cur_size;
  //size_t max_size;
};

//queue_array_t::queue_array_t()
//{
//  this->cur_size = 0;
//}

//queue_array_t::~queue_array_t()
//{
//}

size_t queue_array_t::size()
{
  return this->cur_size;
}

//void& queue_array_t::peek()
//{
//  return NULL;
//}

//void queue_array_t::add(const void& element)
//{
//}

//void& queue_array_t::remove()
//{
//  return NULL;
//}
