#pragma once

#include "s21_basic_container.h"

namespace s21 {

template <class T, size_t N>
class array : public BasicContainer {
 public:
  T _elements[N];

 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  // Member functions
  array();
  ~array();
  array(std::initializer_list<value_type> const &items);
  array(const array &other);
  array(array &&other);
  array<T, N> &operator=(array &&other);

  // Array Element Access
  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference front();
  const_reference back();
  iterator data();

  // Array Iterators
  iterator begin();
  iterator end();

  // Array Capacity
  size_type max_size();

  // Array Modifiers
  void swap(array &other);
  void fill(const_reference value);
};

// Member functions
template <typename T, size_t N>
array<T, N>::array() : BasicContainer(N) {}

template <typename T, size_t N>
array<T, N>::array(const array &other) : BasicContainer(N) {
  for (size_type i = 0; i < size(); ++i) {
    _elements[i] = other._elements[i];
  }
}

template <typename T, size_t N>
array<T, N>::array(array &&other) : BasicContainer(N) {
  if (N != other.size()) throw std::out_of_range("Array sizes are not equal");
  *this = std::move(other);
}

template <typename T, size_t N>
array<T, N>::~array() {}

template <typename T, size_t N>
array<T, N> &array<T, N>::operator=(array &&other) {
  if (this != &other) {
    for (size_type i = 0; i < size(); ++i) {
      _elements[i] = std::move(other._elements[i]);
    }
    other._size = default_container_size;
  }
  return *this;
}

// Array Element Access
template <typename T, size_t N>
T &array<T, N>::at(size_type pos) {
  if (pos >= size())
    throw std::out_of_range("Requested index is out of bounds");
  return _elements[pos];
}

template <typename T, size_t N>
array<T, N>::array(std::initializer_list<array<T, N>::value_type> const &items)
    : BasicContainer(N) {
  if (items.size() > size())
    throw std::out_of_range("Initializer list size is larger than array size");
  int i = 0;
  for (auto it = items.begin(); it != items.end(); it++) {
    _elements[i++] = *it;
  }
}

template <typename T, size_t N>
T &array<T, N>::operator[](size_type pos) {
  return _elements[pos];
}

template <typename T, size_t N>
const T &array<T, N>::front() {
  return at(0);
}

template <typename T, size_t N>
const T &array<T, N>::back() {
  return at(size() - 1);
}

template <typename T, size_t N>
T *array<T, N>::begin() {
  return &_elements[0];
}

template <typename T, size_t N>
T *array<T, N>::end() {
  return &_elements[size()];
}

template <typename T, size_t N>
void array<T, N>::swap(array &other) {
  for (size_t i = 0; i < size(); i++) {
    T tmp = other._elements[i];
    other._elements[i] = _elements[i];
    _elements[i] = tmp;
  }
}

template <typename T, size_t N>
void array<T, N>::fill(const_reference value) {
  for (iterator it = begin(); it < end(); it++) {
    *it = value;
  }
}

template <typename T, size_t N>
T *array<T, N>::data() {
  return _elements;
}

template <typename T, size_t N>
size_t array<T, N>::max_size() {
  return size();
}

}  // namespace s21
