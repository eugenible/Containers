#pragma once

#include <exception>
#include <initializer_list>
#include <iostream>
#include <utility>

namespace s21 {

constexpr size_t default_container_size = 0U;

class BasicContainer {
 protected:
  size_t _size;

 public:
  using size_type = size_t;

 public:
  BasicContainer() : _size(default_container_size) {}
  BasicContainer(size_type n) : _size(n) {}
  virtual ~BasicContainer() {}

  size_type size() { return _size; }

  bool empty() { return _size == 0; }
};

}  // namespace s21
