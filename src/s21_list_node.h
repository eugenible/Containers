#pragma once

namespace s21 {

template <class T>
class ListNode {
 private:
  T _value;
  ListNode* _next;
  ListNode* _prev;

 public:
  ListNode();
  ~ListNode();
  void set_value(const T& value);
  void set_next(ListNode* ptr);
  void set_prev(ListNode* ptr);

  ListNode<T>* get_next();
  ListNode<T>* get_prev();
  T& get_value();
};

template <typename T>
ListNode<T>::ListNode() : _next(nullptr), _prev(nullptr) {}

template <typename T>
ListNode<T>::~ListNode() {}

template <typename T>
void ListNode<T>::set_value(const T& value) {
  _value = value;
}

template <typename T>
void ListNode<T>::set_next(ListNode* ptr) {
  _next = ptr;
}

template <typename T>
void ListNode<T>::set_prev(ListNode* ptr) {
  _prev = ptr;
}

template <typename T>
ListNode<T>* ListNode<T>::get_next() {
  return _next;
}

template <typename T>
ListNode<T>* ListNode<T>::get_prev() {
  return _prev;
}

template <typename T>
T& ListNode<T>::get_value() {
  return _value;
}

}  // namespace s21
