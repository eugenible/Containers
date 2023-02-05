#pragma once

#include "s21_basic_container.h"
#include "s21_node.h"

namespace s21 {

template <class T>
class queue : public BasicContainer {
 private:
  node<T> *_front;
  node<T> *_rear;

 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

 private:
  void insert_underlaying_values(node<T> *current);

 public:
  // Functions
  queue();
  queue(std::initializer_list<value_type> const &items);
  queue(const queue &q);
  queue(queue &&other);
  ~queue();
  queue<T> &operator=(queue &&q);

  // Element access
  const_reference front();
  const_reference back();

  // Modifiers
  void push(const_reference value);
  void pop();
  void swap(queue &other);

  template <class... Args>
  void emplace_back(Args &&...args);
};

// Functions

template <typename T>
queue<T>::queue() : _front(nullptr), _rear(nullptr) {}

template <typename T>
queue<T>::queue(std::initializer_list<value_type> const &items) : queue() {
  for (auto it = items.begin(); it != items.end(); it++) {
    push(*it);
  }
  _size = items.size();
}

template <typename T>
s21::queue<T>::queue(const queue &s) : _front(nullptr) {
  _size = 0;
  insert_underlaying_values(s._rear);
}

template <typename T>
queue<T>::queue(queue &&other) {
  *this = std::move(other);
}

template <typename T>
queue<T>::~queue() {
  while (_size) {
    pop();
  }
}

template <typename T>
queue<T> &queue<T>::operator=(queue &&other) {
  if (this != &other) {
    _front = other._front;
    _rear = other._rear;
    _size = other._size;
    other._front = nullptr;
    other._rear = nullptr;
    other._size = default_container_size;
  }
  return *this;
}

// Element access
template <typename T>
typename queue<T>::const_reference queue<T>::front() {
  if (empty()) {
    throw std::runtime_error("Empty queue");
  }
  return _front->get_value();
}

template <typename T>
typename queue<T>::const_reference queue<T>::back() {
  if (empty()) {
    throw std::runtime_error("Empty queue");
  }
  return _rear->get_value();
}

// Modifiers
template <typename T>
void queue<T>::push(const_reference value) {
  _size++;
  node<T> *n = new node<T>();
  n->set_value(value);
  if (_front == nullptr) {
    n->set_next(nullptr);
    _front = n;
    _rear = n;
  } else {
    n->set_next(_rear);
    _rear = n;
  }
}

template <typename T>
void queue<T>::pop() {
  if (!empty()) {
    if (_size == 1) {
      delete _rear;
    } else if (_size == 2) {
      node<T> tmp = *_rear;
      delete tmp.get_next();
      _front = _rear;
    } else {
      node<T> tmp = *_rear;
      for (size_type i = 0; i < _size - 2; ++i) {
        if (i == _size - 3) _front = tmp.get_next();
        node<T> *next_ptr = tmp.get_next();
        tmp = *next_ptr;
      }
      delete tmp.get_next();
      tmp.set_next(nullptr);
    }
    _size--;
  }
}

template <typename T>
void queue<T>::swap(queue &other) {
  node<T> *tmp = _front;
  _front = other._front;
  other._front = tmp;

  tmp = _rear;
  _rear = other._rear;
  other._rear = tmp;

  size_type tmp_size = _size;
  _size = other._size;
  other._size = tmp_size;
}

template <typename T>
template <class... Args>
void queue<T>::emplace_back(Args &&...args) {
  for (const auto arg : {args...}) {
    push(arg);
  }
}

// Private
template <typename T>
void s21::queue<T>::insert_underlaying_values(node<T> *current) {
  if (current != nullptr) {
    insert_underlaying_values(current->get_next());
    const_reference elem(current->get_value());
    push(elem);
  }
}
}  // namespace s21
