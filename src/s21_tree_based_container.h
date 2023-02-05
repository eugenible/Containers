#pragma once

#include "s21_basic_container.h"
#include "s21_tree.h"

namespace s21 {
template <class Key>
class TreeContainer : public BasicContainer {
 protected:
  Tree<Key>* _elements;

 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = typename Tree<Key>::iterator;
  using const_iterator = typename Tree<Key>::const_iterator;
  using size_type = size_t;

  // Member functions
  TreeContainer();
  TreeContainer(const TreeContainer& items);
  TreeContainer(TreeContainer&& other);
  ~TreeContainer();
  TreeContainer<Key>& operator=(TreeContainer&& other);

  // Iterators
  iterator begin();
  iterator end();
  const_iterator cbegin();
  const_iterator cend();

  // Capacity
  size_type max_size();

  // Modifiers
  void clear();
  void erase(iterator pos);
  void swap(TreeContainer& other);
  void merge(TreeContainer& other);

  // Lookup
  bool contains(const Key& key);
};

// Member functions
template <typename Key>
TreeContainer<Key>::TreeContainer() {
  _elements = new Tree<Key>();
}

template <typename Key>
TreeContainer<Key>::TreeContainer(TreeContainer&& other) {
  *this = std::move(other);
}

template <typename Key>
TreeContainer<Key>::TreeContainer(const TreeContainer& items)
    : TreeContainer() {
  _elements->copy_tree(*items._elements);
}

template <typename Key>
TreeContainer<Key>::~TreeContainer() {
  _elements->delete_tree();
  delete _elements;
}

template <typename Key>
TreeContainer<Key>& TreeContainer<Key>::operator=(TreeContainer&& other) {
  if (this != &other) {
    _elements = other._elements;
    _size = other._size;
    other._elements = nullptr;
    other._size = default_container_size;
  }
  return *this;
}

// Iterators
template <typename Key>
typename TreeContainer<Key>::iterator TreeContainer<Key>::begin() {
  return _elements->begin();
}

template <typename Key>
typename TreeContainer<Key>::iterator TreeContainer<Key>::end() {
  return _elements->end();
}

template <typename Key>
typename TreeContainer<Key>::const_iterator TreeContainer<Key>::cbegin() {
  return _elements->cbegin();
}

template <typename Key>
typename TreeContainer<Key>::const_iterator TreeContainer<Key>::cend() {
  return _elements->cend();
}

// Capacity
template <typename Key>
typename TreeContainer<Key>::size_type TreeContainer<Key>::max_size() {
  return static_cast<size_type>(size_t(-1)) / sizeof(_elements);
}

// Modifiers
template <typename Key>
void TreeContainer<Key>::clear() {
  _elements->delete_tree();
  _size = default_container_size;
}

template <typename Key>
void TreeContainer<Key>::erase(typename TreeContainer<Key>::iterator pos) {
  _elements->remove(*pos);
  _size--;
}

template <typename Key>
void TreeContainer<Key>::swap(TreeContainer& other) {
  Tree<Key>* tmp_elements = other._elements;
  other._elements = _elements;
  _elements = tmp_elements;

  size_type tmp_size = other._size;
  other._size = _size;
  _size = tmp_size;
}

template <typename Key>
void TreeContainer<Key>::merge(TreeContainer& other) {
  _elements->merge(*other._elements);
  _size = 0;
  other._size = 0;
  for (auto it = _elements->begin(); it != _elements->end(); ++it) {
    _size++;
  }
  for (auto it = other._elements->begin(); it != other._elements->end(); ++it) {
    other._size++;
  }
}

// Lookup
template <typename Key>
bool TreeContainer<Key>::contains(const Key& key) {
  return _elements->does_node_exist(key);
}

}  // namespace s21
