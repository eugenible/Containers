#pragma once

#include <exception>
#include <initializer_list>
#include <iostream>
#include <utility>

namespace s21 {

template <class T>
class node {
 private:
  T _value;
  node* _next;

 public:
  node();
  ~node();
  void set_value(const T& value);
  void set_next(node* ptr);
  node<T>* get_next();
  const T& get_value();
};

template <typename T>
node<T>::node() : _value(0), _next(nullptr) {}

template <typename T>
node<T>::~node() {}

template <typename T>
void node<T>::set_value(const T& value) {
  _value = value;
}

template <typename T>
void node<T>::set_next(node* ptr) {
  _next = ptr;
}

template <typename T>
node<T>* node<T>::get_next() {
  return _next;
}

template <typename T>
const T& node<T>::get_value() {
  return _value;
}

}  // namespace s21
