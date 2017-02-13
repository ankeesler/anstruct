// set-tree.hpp

#ifndef __SET_TREE_HPP__
#define __SET_TREE_HPP__

#include "set.hpp"

class set_tree_t : public set_t {
public:
  set_tree_t(const comparator_t& comparator);
  ~set_tree_t();

  // information
  size_t size() const;
  bool contains(const void *element) const;

  // manipulation
  bool add(const void *element);
  bool remove(const void *element);

private:
  class node_t {
  public:
    node_t(const void *data) : left(nullptr), right(nullptr), data(data) {}
    node_t *left;
    node_t *right;
    const void *data;
  };
  node_t *root;
  comparator_t comparator;
  size_t cur_size;

  static void free(node_t *parent);
  bool add(const void *element, node_t *parent);
  bool contains(const void *element, node_t *parent) const;
};

#endif // __SET_TREE_HPP__
