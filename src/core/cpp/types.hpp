/* types.hpp */

#ifndef __TYPES_HPP__
#define __TYPES_HPP__

#include <cstddef>
#include <cstdlib>
#include <cstring>

class comparator_t {
public:
  virtual long compare(const void *arg0, const void *arg1) const { return (long)arg0 - (long)arg1; }
};

#endif // __TYPES_HPP__