#pragma once

#include "s21_basic_container.h"
#include "s21_list_node.h"

namespace s21 {

template <class T>
class list : public BasicContainer {
 private:
  ListNode<T>* _head;
  ListNode<T>* _tail;

  // Member type
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;

  class ListIterator {
   private:
    ListNode<T>* _value;

   public:
    ListNode<T>* get_node_ptr() { return _value; }

   public:
    using iterator = ListIterator;
    ListIterator() : _value(nullptr) {}
    ListIterator(ListNode<T>* value) : _value(value) {}
    ~ListIterator() {}
    bool operator!=(const iterator& other) { return _value != other._value; }
    bool operator==(const iterator& other) { return _value == other._value; }
    reference operator*() { return _value->get_value(); }
    iterator operator++() {
      _value = _value->get_next();
      return *this;
    }
    iterator operator+(int n) {
      for (int i = 0; i < n; i++) {
        _value = _value->get_next();
      }
      return *this;
    }
    iterator operator--() {
      _value = _value->get_prev();
      return *this;
    }
    iterator operator-(int n) {
      for (int i = 0; i < n - 1; i++) {
        _value = _value->get_prev();
      }
      return *this;
    }
  };

  class ConstListIterator {
   private:
    ListNode<T>* _value;

   public:
    ListNode<T>* get_node_ptr() { return _value; }

   public:
    using const_iterator = ConstListIterator;
    ConstListIterator() : _value(nullptr) {}
    ConstListIterator(ListNode<T>* value) : _value(value) {}
    ~ConstListIterator() {}
    bool operator!=(const const_iterator& other) {
      return _value != other._value;
    }
    bool operator==(const const_iterator& other) {
      return _value == other._value;
    }

    const_reference operator*() const { return _value->get_value(); }

    const_iterator operator++() {
      _value = _value->get_next();
      return *this;
    }
    const_iterator operator+(int n) {
      for (int i = 0; i < n; i++) {
        _value = _value->get_next();
      }
      return *this;
    }
    const_iterator operator--() {
      _value = _value->get_prev();
      return *this;
    }
    const_iterator operator-(int n) {
      for (int i = 0; i < n; i++) {
        _value = _value->get_prev();
      }
      return *this;
    }
  };

  using iterator = ListIterator;
  using const_iterator = ConstListIterator;

 private:
  void first_push(const_reference value);
  iterator get_element_by_index(size_type n);

 public:
  // Functions
  list();
  list(const size_type& n);
  list(std::initializer_list<value_type> const& items);
  list(const list& other);
  list(list&& other);
  ~list();
  list<T>& operator=(list&& other);
  iterator operator[](size_type n);

  // Element access
  const_reference front();
  const_reference back();

  // Iterators
  iterator begin();
  const_iterator cbegin();
  iterator end();
  const_iterator cend();

  // Capacity
  size_type max_size();

  // Modifiers
  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void push_front(const_reference value);
  void pop_front();
  void swap(list& other);
  void merge(list& other);
  void splice(const_iterator pos, list& other);
  void reverse();
  void unique();
  void sort();

  template <class... Args>
  iterator emplace(const const_iterator& pos, Args&&... args);

  template <class... Args>
  void emplace_back(Args&&... args);

  template <class... Args>
  void emplace_front(Args&&... args);
};

// Functions

template <typename T>
list<T>::list() : _head(nullptr), _tail(nullptr) {
  _size = default_container_size;
}

template <typename T>
list<T>::list(const list<T>::size_type& n) : list() {
  T value;
  for (list<T>::size_type i = 0; i < n; ++i) {
    push_back(value);
  }
  _size = n;
}

template <typename T>
list<T>::list(std::initializer_list<value_type> const& items) : list() {
  for (auto it = items.begin(); it != items.end(); ++it) {
    push_back(*it);
  }
  _size = items.size();
}

template <typename T>
list<T>::list(const list& other) : list() {
  for (iterator it(other._head); it != iterator(nullptr); ++it) {
    push_back(*it);
  }
}

template <typename T>
list<T>::list(list&& other) {
  *this = std::move(other);
}

template <typename T>
list<T>::~list() {
  while (!empty()) {
    pop_back();
  }
}

template <typename T>
list<T>& list<T>::operator=(list&& other) {
  if (this != &other) {
    _size = other._size;
    _head = other._head;
    _tail = other._tail;
    other._size = default_container_size;
    other._head = nullptr;
    other._tail = nullptr;
  }
  return *this;
}

template <typename T>
typename list<T>::iterator list<T>::operator[](size_type n) {
  return get_element_by_index(n);
}

// Element access
template <typename T>
typename list<T>::const_reference list<T>::front() {
  if (empty()) {
    throw std::runtime_error("Empty list");
  }
  return _head->get_value();
}

template <typename T>
typename list<T>::const_reference list<T>::back() {
  if (empty()) {
    throw std::runtime_error("Empty list");
  }
  return _tail->get_value();
}

// Iterators
template <typename T>
typename list<T>::iterator list<T>::begin() {
  return iterator(_head);
}

template <typename T>
typename list<T>::const_iterator list<T>::cbegin() {
  return const_iterator(_head);
}

template <typename T>
typename list<T>::iterator list<T>::end() {
  return iterator(nullptr);
}

template <typename T>
typename list<T>::const_iterator list<T>::cend() {
  return const_iterator(nullptr);
}

// Capacity
template <typename T>
typename list<T>::size_type list<T>::max_size() {
  return (static_cast<size_type>(size_t(-1) / 2) / sizeof(ListNode<T>));
}

// Modifiers
template <typename T>
typename list<T>::iterator list<T>::insert(list<T>::iterator pos,
                                           list<T>::const_reference value) {
  if (pos.get_node_ptr() == nullptr) {
    push_back(value);
    return iterator(_tail);
  }

  if (pos.get_node_ptr() == _head) {
    push_front(value);
    --pos;
    return pos;
  }

  ListNode<T>* new_node = new ListNode<T>();
  new_node->set_value(value);

  ListNode<T>* current_node = pos.get_node_ptr();

  new_node->set_next(pos.get_node_ptr());
  new_node->set_prev(current_node->get_prev());

  ListNode<T>* prev_node = current_node->get_prev();

  prev_node->set_next(new_node);
  current_node->set_prev(new_node);

  _size++;
  --pos;
  return pos;
}

template <typename T>
void list<T>::erase(iterator pos) {
  if (pos.get_node_ptr() == _tail) {
    pop_back();
  } else if (pos.get_node_ptr() == _head) {
    pop_front();
  } else {
    ListNode<T>* current_node = pos.get_node_ptr();
    current_node->get_prev()->set_next(current_node->get_next());
    current_node->get_next()->set_prev(current_node->get_prev());
    delete pos.get_node_ptr();
    _size--;
  }
}

template <typename T>
void list<T>::push_back(const_reference value) {
  if (empty()) {
    first_push(value);
  } else {
    _size++;
    ListNode<T>* n = new ListNode<T>();
    n->set_value(value);
    n->set_next(nullptr);
    n->set_prev(_tail);
    _tail->set_next(n);
    _tail = n;
  }
}

template <typename T>
void list<T>::push_front(const_reference value) {
  if (empty()) {
    first_push(value);
  } else {
    _size++;
    ListNode<T>* n = new ListNode<T>();
    n->set_value(value);
    n->set_next(_head);
    n->set_prev(nullptr);
    _head->set_prev(n);
    _head = n;
  }
}

template <typename T>
void list<T>::pop_front() {
  if (empty()) throw std::runtime_error("Empty list");
  if (_size <= 2) {
    delete _head;
    if (_size == 2) {
      _head = _tail;
      _head->set_prev(nullptr);
    }
  } else {
    ListNode<T> tmp = *_head;
    delete _head;
    _head = tmp.get_next();
    _head->set_prev(nullptr);
  }
  _size--;
}

template <typename T>
void list<T>::pop_back() {
  if (empty()) throw std::runtime_error("Empty list");
  if (_size <= 2) {
    delete _tail;
    if (_size == 2) {
      _tail = _head;
      _tail->set_next(nullptr);
    }
  } else {
    ListNode<T> tmp = *_tail;
    delete _tail;
    _tail = tmp.get_prev();
    _tail->set_next(nullptr);
  }
  _size--;
}

template <typename T>
void list<T>::swap(list& other) {
  ListNode<T>* tmp = _head;
  _head = other._head;
  other._head = tmp;

  tmp = _tail;
  _tail = other._tail;
  other._tail = tmp;

  size_type tmp_size = _size;
  _size = other._size;
  other._size = tmp_size;
}

template <typename T>
void list<T>::merge(list<T>& other) {
  list<T>::iterator other_it = other.begin();
  for (list<T>::iterator it = begin(); other_it != other.end() && it != end();
       ++it) {
    for (; other_it != other.end() && *it > *other_it; ++other_it) {
      insert(it, *other_it);
    }
  }
  for (; other_it != other.end(); ++other_it) {
    push_back(*other_it);
  }
  while (!other.empty()) {
    other.pop_front();
  }
}

template <typename T>
void list<T>::splice(const_iterator pos, list& other) {
  iterator it;
  for (; it != end() && &(*it) != &(*pos); ++it) {
  }
  auto other_it = other.begin();
  for (; other_it != other.end(); ++other_it) {
    it = insert(it, *other_it);
    ++it;
  }
  while (!other.empty()) {
    other.pop_back();
  }
}

template <typename T>
void list<T>::reverse() {
  ListNode<T>* current_node = _head;
  ListNode<T>* tmp_next = _head->get_next();

  while (current_node != nullptr) {
    tmp_next = current_node->get_next();
    current_node->set_next(current_node->get_prev());
    current_node->set_prev(tmp_next);
    current_node = current_node->get_prev();
  }

  ListNode<T>* tmp_head = _head;
  _head = _tail;
  _tail = tmp_head;
}

template <typename T>
void list<T>::unique() {
  iterator it = begin();
  ++it;

  for (; it != end();) {
    ListNode<T>* current_node = it.get_node_ptr();
    if (current_node->get_prev()->get_value() == *it) {
      erase(it);
      it = begin();
      ++it;
    } else {
      ++it;
    }
  }
}

template <typename T>
void list<T>::sort() {
  double factor = 1.2473309;
  size_type step = size() - 1;
  iterator it1;
  iterator it2;
  ListNode<T>* tmp1;
  ListNode<T>* tmp2;
  T tmp;
  while (step >= 1) {
    for (size_type i = 0; i + step < size(); ++i) {
      it1 = get_element_by_index(i);
      it2 = get_element_by_index(i + step);
      if (*it1 > *it2) {
        tmp1 = it1.get_node_ptr();
        tmp2 = it2.get_node_ptr();
        tmp = tmp1->get_value();
        tmp1->set_value(tmp2->get_value());
        tmp2->set_value(tmp);
      }
    }
    step /= factor;
  }
}

template <typename T>
template <typename... Args>
typename list<T>::iterator list<T>::emplace(const const_iterator& pos,
                                            Args&&... args) {
  iterator it = begin();
  for (; it != end() && &(*it) != &(*pos); ++it) {
  }
  int i = 1;
  for (const auto arg : {args...}) {
    it = insert(it, arg);
    ++it;
    i++;
  }
  return it;
}

template <typename T>
template <class... Args>
void list<T>::emplace_back(Args&&... args) {
  for (const auto arg : {args...}) {
    push_back(arg);
  }
}

template <typename T>
template <class... Args>
void list<T>::emplace_front(Args&&... args) {
  iterator it = begin();
  for (const auto arg : {args...}) {
    it = insert(it, arg);
    ++it;
  }
}

// Private

template <typename T>
void list<T>::first_push(const_reference value) {
  ListNode<T>* n = new ListNode<T>();
  n->set_value(value);
  n->set_next(nullptr);
  n->set_prev(nullptr);
  _head = n;
  _tail = n;
  _size++;
}

template <typename T>
typename list<T>::iterator list<T>::get_element_by_index(size_type n) {
  iterator it = begin();
  while (n--) {
    ++it;
  }
  return it;
}

}  // namespace s21
