#pragma once

#include "s21_set.h"

namespace s21 {

template <class Key>
class multiset : public set<Key> {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = typename set<Key>::iterator;
  using const_iterator = typename set<Key>::const_iterator;
  using size_type = size_t;
  using set<Key>::_elements;
  using set<Key>::_size;

 public:
  multiset();
  multiset(std::initializer_list<value_type> const& items);
  multiset(const multiset& items);
  multiset(multiset&& other);
  ~multiset();
  multiset<Key>& operator=(multiset&& other);

  std::pair<iterator, bool> insert(const value_type& value);

  size_type count(const Key& key);
  std::pair<iterator, iterator> equal_range(const Key& key);
  iterator lower_bound(const Key& key);
  iterator upper_bound(const Key& key);

  template <class... Args>
  std::pair<iterator, bool> emplace(Args&&... args);
};

template <typename Key>
multiset<Key>::multiset() {}

template <typename Key>
multiset<Key>::~multiset() {}

template <typename Key>
multiset<Key>::multiset(const multiset& items) : set<Key>(items) {}

template <typename Key>
multiset<Key>::multiset(multiset&& other) : set<Key>(other) {}

template <typename Key>
multiset<Key>::multiset(std::initializer_list<value_type> const& items) {
  for (auto it = items.begin(); it != items.end(); it++) {
    insert(*it);
  }
  _size = items.size();
}

template <typename Key>
multiset<Key>& multiset<Key>::operator=(multiset&& other) {
  if (*this != other) {
    set<Key>(other);
  }
  return *this;
}

template <typename Key>
std::pair<typename set<Key>::iterator, bool> multiset<Key>::insert(
    const value_type& value) {
  std::pair<typename set<Key>::iterator, bool> p =
      _elements->put_with_duplicate(value);
  if (p.second) _size++;
  return p;
}

template <typename Key>
typename multiset<Key>::size_type multiset<Key>::count(const Key& key) {
  return _elements->count(key);
}

template <typename Key>
std::pair<typename set<Key>::iterator, typename set<Key>::iterator>
multiset<Key>::equal_range(const Key& key) {
  return _elements->equal_range(key);
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::lower_bound(const Key& key) {
  return _elements->lower_bound(key);
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::upper_bound(const Key& key) {
  return _elements->upper_bound(key);
}

template <typename Key>
template <class... Args>
std::pair<typename multiset<Key>::iterator, bool> multiset<Key>::emplace(
    Args&&... args) {
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
