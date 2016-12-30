// set.h

#ifndef __SET_HPP__
#define __SET_HPP__

#include "cpp/types.hpp"

class set_t {
public:
  // creation/deletion
  virtual ~set_t() { };

  // information
  virtual size_t size() const = 0;
  virtual bool contains(const void *element) const = 0;

  // manipulation
  virtual bool add(const void *element) = 0;
  virtual bool remove(const void *element) = 0;
};

#endif // __SET_HPP__