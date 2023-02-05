#pragma once

#include "s21_tree_based_container.h"

namespace s21 {

template <class Key>
class set : public TreeContainer<Key> {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = typename Tree<Key>::iterator;
  using const_iterator = typename Tree<Key>::const_iterator;
  using size_type = size_t;
  using TreeContainer<Key>::_elements;
  using TreeContainer<Key>::_size;

 public:
  // Constructors and destructors
  set();
  set(std::initializer_list<value_type> const& items);
  set(const set& items);
  set(set&& other);
  ~set();
  set<Key>& operator=(set&& other);

  std::pair<iterator, bool> insert(const value_type& value);
  iterator find(const Key& key);

  template <class... Args>
  std::pair<iterator, bool> emplace(Args&&... args);
};

template <typename Key>
set<Key>::set() {}

template <typename Key>
set<Key>::~set() {}

template <typename Key>
set<Key>::set(const set& items) : TreeContainer<Key>(items) {}

template <typename Key>
set<Key>::set(set&& other) : TreeContainer<Key>(other) {}

template <typename Key>
set<Key>& set<Key>::operator=(set&& other) {
  if (this != &other) {
    *this = std::move(other);
  }
  return *this;
}

template <typename Key>
set<Key>::set(std::initializer_list<value_type> const& items) {
  for (auto it = items.begin(); it != items.end(); it++) {
    insert(*it);
  }
}

template <typename Key>
std::pair<typename set<Key>::iterator, bool> set<Key>::insert(
    const value_type& value) {
  std::pair<typename Tree<Key>::iterator, bool> p =
      _elements->put_without_duplicate(value);
  if (p.second) _size++;
  return p;
}

template <typename Key>
typename set<Key>::iterator set<Key>::find(const value_type& value) {
  return _elements->lower_bound(value);
}

template <typename Key>
template <class... Args>
std::pair<typename set<Key>::iterator, bool> set<Key>::emplace(Args&&... args) {
  std::pair<iterator, bool> p;
  size_t length = sizeof...(args);
  size_t counter = 0;
  for (const auto arg : {args...}) {
    if (counter == length - 1)
      p = insert(arg);
    else
      insert(arg);
    counter++;
  }
  return p;
}

}  // namespace s21
