#pragma once

#include "s21_basic_container.h"

namespace s21 {
constexpr size_t default_vector_capacity = 0U;

template <class T>
class vector : public BasicContainer {
 private:
  size_t _capacity;
  T* _array;

  // Member type
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;

  class VectorIterator {
   private:
    T* _value_ptr;

   public:
    using iterator = VectorIterator;
    VectorIterator() : _value_ptr(nullptr) {}
    VectorIterator(T* value) : _value_ptr(value) {}
    VectorIterator(const VectorIterator& other)
        : _value_ptr(other._value_ptr) {}
    ~VectorIterator() {}
    bool operator!=(const iterator& other) {
      return _value_ptr != other._value_ptr;
    }
    bool operator==(const iterator& other) {
      return _value_ptr == other._value_ptr;
    }
    reference operator*() { return *_value_ptr; }
    iterator operator+(int n) {
      _value_ptr += n;
      return *this;
    }
    iterator operator-(int n) {
      _value_ptr -= n;
      return *this;
    }
    iterator operator++() {
      iterator it = *this;
      _value_ptr++;
      return it;
    }
    iterator operator++(int) {
      _value_ptr++;
      return *this;
    }
    iterator operator--() {
      iterator it = *this;
      _value_ptr--;
      return it;
    }
    iterator operator--(int) {
      _value_ptr--;
      return *this;
    }
  };

  class ConstVectorIterator {
   private:
    T* _value_ptr;

   public:
    using const_iterator = ConstVectorIterator;
    ConstVectorIterator() : _value_ptr(nullptr) {}
    ConstVectorIterator(T* value) : _value_ptr(value) {}
    ~ConstVectorIterator() {}
    bool operator!=(const const_iterator& other) {
      return _value_ptr != other._value_ptr;
    }
    bool operator==(const const_iterator& other) {
      return _value_ptr == other._value_ptr;
    }
    const_reference operator*() const { return *_value_ptr; }
    const_iterator operator+(int n) {
      _value_ptr += n;
      return *this;
    }
    const_iterator operator-(int n) {
      _value_ptr -= n;
      return *this;
    }
    const_iterator operator++() {
      const_iterator it = *this;
      _value_ptr++;
      return it;
    }
    const_iterator operator++(int) {
      _value_ptr++;
      return *this;
    }
    const_iterator operator--() {
      const_iterator it = *this;
      _value_ptr--;
      return it;
    }
    const_iterator operator--(int) {
      _value_ptr--;
      return *this;
    }
  };

  using iterator = VectorIterator;
  using const_iterator = ConstVectorIterator;

 private:
  void relocate_values();
  void reserve_more_capacity(size_type size);
  void delete_array();
  void copy_vector(const vector& src);
  void replace_array(value_type* new_array);

 public:
  // Functions
  vector();
  vector(size_type n);
  vector(std::initializer_list<value_type> const& items);
  vector(const vector& other);
  vector(vector&& other);
  ~vector();
  vector<T>& operator=(vector&& other);

  // Element access
  reference at(size_type position);
  reference operator[](size_type position);
  const_reference front();
  const_reference back();
  iterator data();

  // Iterators
  iterator begin();
  iterator end();
  const_iterator cbegin();
  const_iterator cend();

  // Capacity
  size_type max_size();
  void reserve(const size_type& size);
  size_type capacity();
  void shrink_to_fit();

  // Modifiers
  void clear();
  iterator insert(iterator position, const_reference value);
  void erase(iterator position);
  void push_back(const_reference value);
  void pop_back();
  void swap(vector& other);

  template <class... Args>
  iterator emplace(const const_iterator& pos, Args&&... args);

  template <class... Args>
  void emplace_back(Args&&... args);
};

// Functions
template <typename T>
vector<T>::vector() : _capacity(default_vector_capacity) {
  _array = new value_type[_capacity];
}

template <typename T>
vector<T>::vector(size_type n) : _capacity(n) {
  _size = n;
  _array = new value_type[_capacity];
}

template <typename T>
vector<T>::vector(std::initializer_list<vector<T>::value_type> const& items) {
  _array = new value_type[items.size()];
  int i = 0;
  for (auto it = items.begin(); it != items.end(); it++) {
    _array[i++] = *it;
  }
  _size = items.size();
  _capacity = items.size();
}

template <typename T>
vector<T>::vector(const vector& other) {
  copy_vector(other);
}

template <typename T>
vector<T>::vector(vector&& other) {
  *this = std::move(other);
}

template <typename T>
vector<T>::~vector() {
  delete_array();
}

template <typename T>
vector<T>& vector<T>::operator=(vector&& other) {
  if (this != &other) {
    _size = other._size;
    _capacity = other._capacity;
    _array = other._array;
    other._size = default_container_size;
    other._capacity = default_vector_capacity;
    other._array = nullptr;
  }
  return *this;
}

// Element access
template <typename T>
typename vector<T>::reference vector<T>::at(size_type position) {
  if (position > _size) {
    throw std::out_of_range("Index out of range");
  }
  return _array[position];
}

template <typename T>
typename vector<T>::reference vector<T>::operator[](size_type position) {
  return _array[position];
}

template <typename T>
typename vector<T>::const_reference vector<T>::front() {
  return _array[0];
}

template <typename T>
typename vector<T>::const_reference vector<T>::back() {
  return _array[_size - 1];
}

template <typename T>
typename vector<T>::iterator vector<T>::data() {
  return _array;
}

// Iterators
template <typename T>
typename vector<T>::iterator vector<T>::begin() {
  return iterator(_array);
}

template <typename T>
typename vector<T>::iterator vector<T>::end() {
  return iterator(_array + _size);
}

template <typename T>
typename vector<T>::const_iterator vector<T>::cbegin() {
  return const_iterator(_array);
}

template <typename T>
typename vector<T>::const_iterator vector<T>::cend() {
  return const_iterator(_array + _size);
}

// Capacity

template <typename T>
typename vector<T>::size_type vector<T>::max_size() {
  return static_cast<size_type>(((size_t(-1) / 2) / sizeof(T)));
}

template <typename T>
typename vector<T>::size_type vector<T>::capacity() {
  return _capacity;
}

template <typename T>
void vector<T>::reserve(const vector<T>::size_type& size) {
  reserve_more_capacity(size);
}

template <typename T>
void vector<T>::shrink_to_fit() {
  _capacity = _size;
  relocate_values();
}

// Modifiers

template <typename T>
void vector<T>::clear() {
  _size = 0;
  delete_array();
}

template <typename T>
typename vector<T>::iterator vector<T>::insert(iterator position,
                                               const_reference value) {
  _capacity++;
  value_type* buffer = new value_type[_size + 1];
  size_type i = 0, new_value_position = 0;
  for (auto it = begin(); it != position; ++it) {
    buffer[i++] = *it;
  }
  new_value_position = i;
  buffer[i++] = value;
  for (auto it = position; it != end(); ++it) {
    buffer[i++] = *it;
  }
  replace_array(buffer);
  _size++;
  return (begin() + new_value_position);
}

template <typename T>
void vector<T>::erase(iterator position) {
  value_type* buffer = new value_type[_capacity];
  size_type i = 0;
  for (auto it = begin(); it != position; ++it) {
    buffer[i++] = *it;
  }
  for (auto it = position + 1; it != end(); ++it) {
    buffer[i++] = *it;
  }
  replace_array(buffer);
  _size--;
}

template <typename T>
void vector<T>::push_back(const const_reference& value) {
  if (_size == _capacity) {
    reserve_more_capacity(_size * 2);
  }
  _array[_size++] = value;
}

template <typename T>
void vector<T>::pop_back() {
  if (!empty()) {
    _size--;
    relocate_values();
  }
}

template <typename T>
void vector<T>::swap(vector& other) {
  T* tmp = other._array;
  size_type tmp_size = other._size;
  other._array = _array;
  _array = tmp;
  other._size = _size;
  _size = tmp_size;
  tmp_size = other._capacity;
  other._capacity = _capacity;
  _capacity = tmp_size;
}

template <typename T>
template <typename... Args>
typename vector<T>::iterator vector<T>::emplace(const const_iterator& pos,
                                                Args&&... args) {
  iterator it = begin();
  for (; it != end() && &(*it) != &(*pos); ++it) {
  }
  int i = 1;
  for (const auto arg : {args...}) {
    insert(it, arg);
    it = begin() + i;
    i++;
  }
  return it - i + 1;
}

template <typename T>
template <typename... Args>
void vector<T>::emplace_back(Args&&... args) {
  for (const auto arg : {args...}) {
    push_back(arg);
  }
}

// Private
template <typename T>
void vector<T>::relocate_values() {
  value_type* new_values = new value_type[_capacity];
  if (_array != nullptr) {
    for (size_type i = 0; i < _size; ++i) {
      new_values[i] = std::move(_array[i]);
    }
    delete_array();
  }
  _array = new_values;
}

template <typename T>
void vector<T>::reserve_more_capacity(size_type size) {
  if (empty()) {
    size = 1;
  }
  if (size > _capacity) {
    _capacity = size;
    relocate_values();
  }
}

template <typename T>
void vector<T>::delete_array() {
  if (_array) {
    delete[] _array;
    _array = nullptr;
  }
}

template <typename T>
void vector<T>::copy_vector(const vector& src) {
  _size = src._size;
  _capacity = src._capacity;
  _array = new value_type[_size];
  for (int i = 0; i < _size; i++) {
    _array[i] = src._array[i];
  }
}

template <typename T>
void vector<T>::replace_array(value_type* new_array) {
  delete_array();
  _array = new_array;
}

}  // namespace s21
