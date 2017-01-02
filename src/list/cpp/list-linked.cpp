// list-linked.cpp

#include "list-linked.hpp"

list_linked_t::~list_linked_t()
{
  node_t *node = this->head, *next;
  while (node != nullptr) {
    next = node->next;
    delete node;
    node = next;
  }
}

size_t list_linked_t::size() const
{
  return this->cur_size;
}

const void *list_linked_t::find(const void *element, comparator_t& comparator) const
{
  node_t *node = this->head;
  while (node != nullptr && comparator.compare(node->data, element) != 0) {
    node = node->next;
  }
  return (node != nullptr ? node->data : nullptr);
}

const void *list_linked_t::get(size_t index) const
{
  node_t *node = this->head;
  while (node != nullptr && index--) {
    node = node->next;
  }
  return (node != nullptr ? node->data : nullptr);
}

void list_linked_t::addfront(const void *element)
{
  if (this->head == nullptr) {
    this->head = new node_t(element);
    this->tail = this->head;
  } else {
    node_t *node = new node_t(element);
    this->head->previous = node;
    node->next = this->head;
    this->head = node;
  }
  this->cur_size++;
}

void list_linked_t::addback(const void *element)
{
  if (this->tail == nullptr) {
    this->tail = new node_t(element);
    this->head = this->tail;
  } else {
    node_t *node = new node_t(element);
    this->tail->next = node;
    node->previous = this->tail;
    this->tail = node;
  }
  this->cur_size++;  
}

const void *list_linked_t::removefront(const void *element, comparator_t& comparator)
{
  return nullptr;
}

const void *list_linked_t::removeback(const void *element, comparator_t& comparator)
{
  return nullptr;
}

const void *list_linked_t::remove(const void *element, comparator_t& comparator)
{
  // TODO: how do I make this a private helper function?
  node_t *node = this->head;
  while (node != nullptr && comparator.compare(node->data, element) != 0) {
    node = node->next;
  }
  if (node == nullptr) {
    return nullptr;
  }

  const void *data = node->data;
  bool head = (node->previous == nullptr);
  bool tail = (node->next == nullptr);
  if (head && tail) {
    this->head = nullptr;
    this->tail = nullptr;
  } else if (head && !tail) {
    this->head = node->next;
    this->head->previous = nullptr;
  } else if (!head && tail) {
    this->tail = node->previous;
    this->tail->next = nullptr;    
  } else { // !head && !tail
    node->previous->next = node->next;
    node->next->previous = node->previous;
  }
  delete node;
  this->cur_size--;
  return data;
}

void list_linked_t::reverse()
{
  node_t *node = this->head;
  while (node != nullptr) {
    node_t *next = node->next;
    node->next = node->previous;
    node->previous = next;
    node = next;
  }
  node = this->head;
  this->head = this->tail;
  this->tail = node;
}

void list_linked_t::insert(const void *element, size_t index)
{
  
}
