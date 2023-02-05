#pragma once

#include "s21_pair.h"
#include "s21_tree_based_container.h"

using s21::TreeContainer;

namespace s21 {

template <class Key, class T>
class map : public TreeContainer<s21::pair<Key, T>> {
 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = s21::pair<const key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = typename Tree<s21::pair<Key, T>>::iterator;
  using const_iterator = const value_type*;
  using size_type = size_t;
  using TreeContainer<s21::pair<Key, T>>::_elements;
  using TreeContainer<s21::pair<Key, T>>::_size;

 public:
  // Member functions
  map();
  map(std::initializer_list<value_type> const& items);
  map(const map& items);
  map(map&& other);
  ~map();
  map<Key, T>& operator=(map&& other);

  // Element access
  T& at(const Key& key);
  T& operator[](const Key& key);

  // Modifiers
  std::pair<iterator, bool> insert(const Key& key, const T& obj);
  std::pair<iterator, bool> insert_or_assign(const Key& key, const T& obj);
  // Lookup
  bool contains(const Key& key);

  template <class... Args>
  std::pair<iterator, bool> emplace(Args&&... args);
};

// Member functions
template <typename Key, typename T>
map<Key, T>::map() {}

template <typename Key, typename T>
map<Key, T>::~map() {}

template <typename Key, typename T>
map<Key, T>& map<Key, T>::operator=(map&& other) {
  if (this != &other) {
    TreeContainer<s21::pair<Key, T>>(other);
  }
  return *this;
}

template <typename Key, typename T>
map<Key, T>::map(std::initializer_list<value_type> const& items) : map() {
  for (auto it = items.begin(); it != items.end(); it++) {
    insert(it->first, it->second);
  }
}

template <typename Key, typename T>
map<Key, T>::map(const map& items) : TreeContainer<s21::pair<Key, T>>(items) {}

template <typename Key, typename T>
map<Key, T>::map(map&& other) : TreeContainer<s21::pair<Key, T>>(other) {}

// Element access
template <typename Key, typename T>
T& map<Key, T>::at(const Key& key) {
  s21::pair<Key, T> p = {key, T()};
  TreeNode<s21::pair<Key, T>>* node = _elements->get_node_by_value(p);
  if (node == nullptr) {
    throw std::out_of_range("No element with such key");
  }
  return node->get_value().second;
}

template <typename Key, typename T>
T& map<Key, T>::operator[](const Key& key) {
  s21::pair<Key, T> p = {key, T()};
  if (_elements->does_node_exist(p)) {
    return _elements->get_node_by_value(p)->get_value().second;
  }
  std::pair<iterator, bool> pair = insert(key, T());
  return pair.first->second;
}

// Modifiers

template <typename Key, typename T>
std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert(
    const Key& key, const T& obj) {
  std::pair<iterator, bool> pair = _elements->put_without_duplicate({key, obj});
  if (pair.second) _size++;
  return pair;
}

template <typename Key, typename T>
std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert_or_assign(
    const Key& key, const T& obj) {
  std::pair<iterator, bool> pair = _elements->put_or_assign({key, obj});
  if (pair.second) _size++;
  return pair;
}

// Lookup
template <typename Key, typename T>
bool map<Key, T>::contains(const Key& key) {
  s21::pair<Key, T> p = {key, T()};
  return _elements->does_node_exist(p);
}

template <typename Key, typename T>
template <typename... Args>
std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::emplace(
    Args&&... args) {
  std::pair<iterator, bool> p;
  size_t length = sizeof...(args);
  size_t counter = 0;
  for (const auto arg : {args...}) {
    if (counter == length - 1)
      p = insert(arg.first, arg.second);
    else
      insert(arg.first, arg.second);
    counter++;
  }
  return p;
}

}  // namespace s21
