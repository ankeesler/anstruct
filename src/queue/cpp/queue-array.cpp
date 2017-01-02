// queue-array.cpp

#include "queue-array.hpp"

queue_array_t::queue_array_t(const queue_init_t& init)
  : cur_size(0),
    max_size(init.size),
    resize_factor(init.resize_factor),
    data((const void **)new void*[this->max_size])
{
}

queue_array_t::~queue_array_t()
{
  delete[] this->data;  
}

size_t queue_array_t::size() const
{
  return this->cur_size;
}

const void *queue_array_t::peek() const
{
  return (this->cur_size == 0 ? nullptr : this->data[0]);
}

void queue_array_t::add(const void *element)
{
  if (this->cur_size == this->max_size) {
    this->max_size *= this->resize_factor;
    const void **new_data = (const void **)new void*[this->max_size];
    memmove(new_data, this->data, this->cur_size * sizeof(this->data[0]));
    delete[] this->data;
    this->data = new_data;
  }
  this->data[this->cur_size++] = element;
}

const void *queue_array_t::remove()
{
  const void *data = this->peek();
  if (data != nullptr) {
    this->cur_size--;
    memmove(this->data, this->data + 1, this->cur_size * sizeof(data));
  }
  return data;
}
