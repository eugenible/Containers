#pragma once

#include "s21_basic_container.h"
#include "s21_node.h"

namespace s21 {

template <class T>
class stack : public BasicContainer {
 private:
  node<T> *_head;

 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

 private:
  void insert_underlaying_values(node<T> *current);

 public:
  // Functions
  stack();
  stack(std::initializer_list<value_type> const &items);
  stack(const stack &other);
  stack(stack &&other);
  ~stack();
  stack<T> &operator=(stack &&other);

  // Element access
  const_reference top();

  // Modifiers
  void push(const_reference value);
  void pop();
  void swap(stack &other);

  template <class... Args>
  void emplace_front(Args &&...args);
};

// Functions
template <typename T>
stack<T>::stack() : _head(nullptr) {}

template <typename T>
stack<T>::~stack() {
  while (!empty()) {
    pop();
  }
}

template <typename T>
stack<T>::stack(std::initializer_list<value_type> const &items) : stack() {
  for (auto it = items.begin(); it != items.end(); it++) {
    push(*it);
  }
  _size = items.size();
}

template <typename T>
stack<T>::stack(const stack &s) {
  _size = 0;
  insert_underlaying_values(s._head);
}

template <typename T>
stack<T>::stack(stack &&other) {
  *this = std::move(other);
}

template <typename T>
stack<T> &stack<T>::operator=(stack &&other) {
  if (this != &other) {
    _head = other._head;
    _size = other._size;
    other._head = nullptr;
    other._size = default_container_size;
  }
  return *this;
}

// Element access
template <typename T>
typename stack<T>::const_reference stack<T>::top() {
  if (!_head) {
    throw std::runtime_error("Empty stack");
  }
  return _head->get_value();
}

// Modifiers
template <typename T>
void s21::stack<T>::push(const_reference value) {
  _size++;
  node<T> *n = new node<T>();
  n->set_value(value);
  n->set_next(_head);
  _head = n;
}

template <typename T>
void s21::stack<T>::pop() {
  if (!empty()) {
    _size--;
    node<T> *tmp = _head;
    _head = _head->get_next();
    delete tmp;
  }
}

template <typename T>
void s21::stack<T>::swap(stack &other) {
  node<T> *tmp = other._head;
  other._head = _head;
  _head = tmp;
  size_t tmp_size = other._size;
  other._size = _size;
  _size = tmp_size;
}

template <typename T>
template <class... Args>
void stack<T>::emplace_front(Args &&...args) {
  for (const auto arg : {args...}) {
    push(arg);
  }
}

// Private
template <typename T>
void stack<T>::insert_underlaying_values(node<T> *current) {
  if (current != nullptr) {
    insert_underlaying_values(current->get_next());
    const_reference elem(current->get_value());
    push(elem);
  }
}

}  // namespace s21
