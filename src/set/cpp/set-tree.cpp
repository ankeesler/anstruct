// set-tree.cpp

#include "set-tree.hpp"
  
set_tree_t::set_tree_t(const comparator_t& comparator)
  : comparator(comparator), cur_size(0)
{
}

set_tree_t::~set_tree_t()
{
  set_tree_t::free(this->root);
}
  
size_t set_tree_t::size() const
{
  return this->cur_size;
}

bool set_tree_t::contains(const void *element) const
{
  return contains(element, this->root);
}

bool set_tree_t::add(const void *element)
{
  if (this->root == nullptr) {
    this->root = new node_t(element);
    this->cur_size++;
    return true;
  }

  if (add(element, this->root)) {
    this->cur_size++;
    return true;
  } else {
    return false;
  }
}

bool set_tree_t::remove(const void *element)
{
  return false;
}

bool set_tree_t::add(const void *element, node_t *parent)
{
  long cmp = this->comparator.compare(element, parent->data);
  if (cmp == 0) { // element == parent->element
    return false;
  } else if (cmp < 0) { // element < parent->element
    if (parent->left == nullptr) {
      parent->left = new node_t(element);
      return true;
    } else {
      return add(element, parent->left);
    }
  } else { // element > parent->element
    if (parent->right == nullptr) {
      parent->right = new node_t(element);
      return true;
    } else {
      return add(element, parent->left);
    }
  }
}

bool set_tree_t::contains(const void *element, node_t *parent) const
{
  return (parent != nullptr
          && (this->comparator.compare(element, parent->data) == 0
              || contains(element, parent->left)
              || contains(element, parent->right)));
}

void set_tree_t::free(node_t *parent)
{
  if (parent != nullptr) {
    set_tree_t::free(parent->left);
    set_tree_t::free(parent->right);
    delete parent;
  }
}
