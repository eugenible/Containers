#pragma once

#include <iostream>

namespace s21 {

enum NodeColors { BLACK, RED };

template <class T>
class TreeNode {
 private:
  T _value;
  NodeColors _color{NodeColors::RED};

  TreeNode<T>* _parent{nullptr};
  TreeNode<T>* _left{nullptr};
  TreeNode<T>* _right{nullptr};

 public:
  using reference = T&;
  using const_reference = const T&;
  using pointer = T*;
  // Constructors and destructors
  TreeNode();
  ~TreeNode();
  TreeNode(const_reference value);

  // Functions
  bool is_left_child();
  bool is_right_child();
  bool is_red();
  bool is_black();
  void move_down(TreeNode<T>* new_parent);
  bool has_red_child();
  void swap_values(TreeNode<T>* other);
  bool has_left();
  bool has_right();
  bool has_sibling();
  void remove_left();
  void remove_right();
  // Setters
  void set_parent(TreeNode<T>* parent);
  void set_left(TreeNode<T>* left);
  void set_right(TreeNode<T>* right);
  void set_value(const_reference value);
  void set_color(NodeColors color);
  void set_red();
  void set_black();

  // Getters
  reference get_value();
  pointer get_value_ptr();
  TreeNode<T>* get_parent();
  TreeNode<T>* get_grand_parent();
  TreeNode<T>* get_left_uncle();
  TreeNode<T>* get_right_uncle();
  TreeNode<T>* get_uncle();
  TreeNode<T>* get_left();
  TreeNode<T>* get_right();
  NodeColors get_color();
  TreeNode<T>* get_sibling();

  // Operators
  bool operator<(const TreeNode& other);
  bool operator>(const TreeNode& other);
  bool operator>=(const TreeNode& other);
  bool operator<=(const TreeNode& other);
  bool operator==(const TreeNode& other);
  bool operator!=(const TreeNode& other);
};

// Constructors and Destructors

template <typename T>
TreeNode<T>::TreeNode() {}

template <typename T>
TreeNode<T>::TreeNode(const_reference value) : _value(value) {}

template <typename T>
TreeNode<T>::~TreeNode() {}

// Functions
template <typename T>
bool TreeNode<T>::is_left_child() {
  return this == _parent->get_left();
}

template <typename T>
bool TreeNode<T>::is_right_child() {
  return this == _parent->get_right();
}

template <typename T>
bool TreeNode<T>::is_red() {
  return _color == NodeColors::RED;
}

template <typename T>
bool TreeNode<T>::is_black() {
  return _color == NodeColors::BLACK;
}

template <typename T>
void TreeNode<T>::move_down(TreeNode<T>* new_parent) {
  if (_parent != nullptr) {
    if (is_left_child()) {
      _parent->set_left(new_parent);
    } else {
      _parent->set_right(new_parent);
    }
  }
  new_parent->set_parent(_parent);
  _parent = new_parent;
}

template <typename T>
bool TreeNode<T>::has_red_child() {
  return (has_left() && _left->is_red()) || (has_right() && _right->is_red());
}

template <typename T>
void TreeNode<T>::swap_values(TreeNode<T>* other) {
  T tmp = other->get_value();
  other->set_value(get_value());
  set_value(tmp);
}

template <typename T>
bool TreeNode<T>::has_left() {
  return _left != nullptr;
}

template <typename T>
bool TreeNode<T>::has_right() {
  return _right != nullptr;
}

template <typename T>
bool TreeNode<T>::has_sibling() {
  return get_sibling() != nullptr;
}

template <typename T>
void TreeNode<T>::remove_left() {
  _left = nullptr;
}

template <typename T>
void TreeNode<T>::remove_right() {
  _right = nullptr;
}

// Setters

template <typename T>
void TreeNode<T>::set_parent(TreeNode<T>* parent) {
  _parent = parent;
}

template <typename T>
void TreeNode<T>::set_left(TreeNode<T>* left) {
  _left = left;
}

template <typename T>
void TreeNode<T>::set_right(TreeNode<T>* right) {
  _right = right;
}

template <typename T>
void TreeNode<T>::set_value(const_reference value) {
  _value = value;
}

template <typename T>
void TreeNode<T>::set_color(NodeColors color) {
  _color = color;
}

template <typename T>
void TreeNode<T>::set_red() {
  _color = NodeColors::RED;
}

template <typename T>
void TreeNode<T>::set_black() {
  _color = NodeColors::BLACK;
}

// Getters

template <typename T>
typename TreeNode<T>::reference TreeNode<T>::get_value() {
  return _value;
}

template <typename T>
typename TreeNode<T>::pointer TreeNode<T>::get_value_ptr() {
  return &_value;
}

template <typename T>
TreeNode<T>* TreeNode<T>::get_parent() {
  return _parent;
}

template <typename T>
TreeNode<T>* TreeNode<T>::get_grand_parent() {
  return _parent->get_parent();
}

template <typename T>
TreeNode<T>* TreeNode<T>::get_left_uncle() {
  return _parent->get_parent()->get_left();
}

template <typename T>
TreeNode<T>* TreeNode<T>::get_right_uncle() {
  return _parent->get_parent()->get_right();
}

template <typename T>
TreeNode<T>* TreeNode<T>::get_uncle() {
  if (_parent == nullptr || _parent->get_parent() == nullptr) {
    return nullptr;
  }
  if (_parent->is_left_child()) {
    return get_right_uncle();
  }
  return get_left_uncle();
}

template <typename T>
TreeNode<T>* TreeNode<T>::get_left() {
  return _left;
}

template <typename T>
TreeNode<T>* TreeNode<T>::get_right() {
  return _right;
}

template <typename T>
NodeColors TreeNode<T>::get_color() {
  return _color;
}

template <typename T>
TreeNode<T>* TreeNode<T>::get_sibling() {
  if (is_left_child()) {
    return _parent->get_right();
  } else {
    return _parent->get_left();
  }
  return nullptr;
}

}  // namespace s21
