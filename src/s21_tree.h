#pragma once

#include "s21_tree_node.h"

using s21::TreeNode;

namespace s21 {

template <class T>
class Tree {
 private:
  TreeNode<T>* _root{nullptr};
  TreeNode<T>* _min{nullptr};
  TreeNode<T>* _max{nullptr};

 public:
  using reference = T&;
  using const_reference = const T&;
  using pointer = T*;
  using const_pointer = const T*;
  using size_type = size_t;

  class TreeIterator {
   private:
    TreeNode<T>* _min{nullptr};
    TreeNode<T>* _max{nullptr};
    TreeNode<T>* _node_ptr{nullptr};

   private:
    void increment() {
      if (_node_ptr == _max) {
        _node_ptr = nullptr;
        return;
      }
      if (_node_ptr->has_right()) {
        _node_ptr = _node_ptr->get_right();
        while (_node_ptr->has_left()) {
          _node_ptr = _node_ptr->get_left();
        }
      } else {
        while (_node_ptr->is_right_child()) {
          _node_ptr = _node_ptr->get_parent();
        }
        _node_ptr = _node_ptr->get_parent();
      }
    }

    void decrement() {
      if (_node_ptr == nullptr) {
        _node_ptr = _max;
        return;
      }
      if (_node_ptr == _min) {
        _node_ptr = nullptr;
        return;
      }
      if (_node_ptr->has_left()) {
        _node_ptr = _node_ptr->get_left();
        while (_node_ptr->has_right()) {
          _node_ptr = _node_ptr->get_right();
        }
      } else {
        while (_node_ptr->is_left_child()) {
          _node_ptr = _node_ptr->get_parent();
        }
        _node_ptr = _node_ptr->get_parent();
      }
    }

   public:
    using iterator = TreeIterator;
    TreeIterator() : _node_ptr(nullptr), _min(nullptr), _max(nullptr) {}
    TreeIterator(TreeNode<T>* node, TreeNode<T>* min, TreeNode<T>* max)
        : _node_ptr(node), _min(min), _max(max) {}
    ~TreeIterator() {}
    bool operator!=(const iterator& other) {
      if (other._node_ptr == nullptr || _node_ptr == nullptr) {
        return _node_ptr != other._node_ptr;
      }
      return _node_ptr->get_value() != other._node_ptr->get_value();
    }

    bool operator==(const iterator& other) {
      if (other._node_ptr == nullptr || _node_ptr) {
        return _node_ptr != other._node_ptr;
      }
      return _node_ptr->get_value() == other._node_ptr->get_value();
    }

    reference operator*() {
      if (_node_ptr != nullptr) return _node_ptr->get_value();
      return _max->get_value();
    }

    pointer operator->() {
      if (_node_ptr != nullptr) return _node_ptr->get_value_ptr();
      return _max->get_value_ptr();
    }

    iterator operator++() {
      increment();
      return *this;
    }

    iterator operator--() {
      decrement();
      return *this;
    }
  };

  class ConstTreeIterator {
   private:
    TreeNode<T>* _min{nullptr};
    TreeNode<T>* _max{nullptr};
    TreeNode<T>* _node_ptr{nullptr};

   private:
    void increment() {
      if (_node_ptr == _max) {
        _node_ptr = nullptr;
        return;
      }
      if (_node_ptr->has_right()) {
        _node_ptr = _node_ptr->get_right();
        while (_node_ptr->has_left()) {
          _node_ptr = _node_ptr->get_left();
        }
      } else {
        while (_node_ptr->is_right_child()) {
          _node_ptr = _node_ptr->get_parent();
        }
        _node_ptr = _node_ptr->get_parent();
      }
    }

    void decrement() {
      if (_node_ptr == nullptr) {
        _node_ptr = _max;
        return;
      }
      if (_node_ptr == _min) {
        _node_ptr = nullptr;
        return;
      }
      if (_node_ptr->has_left()) {
        _node_ptr = _node_ptr->get_left();
        while (_node_ptr->has_right()) {
          _node_ptr = _node_ptr->get_right();
        }
      } else {
        while (_node_ptr->is_left_child()) {
          _node_ptr = _node_ptr->get_parent();
        }
        _node_ptr = _node_ptr->get_parent();
      }
    }

   public:
    using const_iterator = ConstTreeIterator;
    ConstTreeIterator() : _node_ptr(nullptr), _min(nullptr), _max(nullptr) {}
    ConstTreeIterator(TreeNode<T>* node, TreeNode<T>* min, TreeNode<T>* max)
        : _node_ptr(node), _min(min), _max(max) {}
    ~ConstTreeIterator() {}
    bool operator!=(const const_iterator& other) {
      if (other._node_ptr == nullptr || _node_ptr == nullptr) {
        return _node_ptr != other._node_ptr;
      }
      return _node_ptr->get_value() != other._node_ptr->get_value();
    }

    bool operator==(const const_iterator& other) {
      if (other._node_ptr == nullptr || _node_ptr) {
        return _node_ptr != other._node_ptr;
      }
      return _node_ptr->get_value() == other._node_ptr->get_value();
    }

    const_reference operator*() const {
      if (_node_ptr != nullptr) return _node_ptr->get_value();
      return _max->get_value();
    }

    const_pointer operator->() const {
      if (_node_ptr != nullptr) return _node_ptr->get_value_ptr();
      return _max->get_value_ptr();
    }

    const_iterator operator++() {
      increment();
      return *this;
    }

    const_iterator operator--() {
      decrement();
      return *this;
    }
  };

  using iterator = TreeIterator;
  using const_iterator = ConstTreeIterator;

 private:
  std::pair<iterator, bool> put(const_reference value, bool allow_duplicate,
                                bool allow_assign);
  void rotate_left(TreeNode<T>* node);
  void rotate_right(TreeNode<T>* node);
  TreeNode<T>* get_available_place(const_reference value);
  void swap_colors(TreeNode<T>* left, TreeNode<T>* right);
  TreeNode<T>* get_successor(TreeNode<T>* node);
  void remove_node_without_successor(TreeNode<T>* removable,
                                     bool is_double_black);
  void remove_node_with_successor(TreeNode<T>* removable,
                                  TreeNode<T>* successor, bool is_double_black);
  void fix_red_in_row(TreeNode<T>* node);
  void fix_double_black(TreeNode<T>* node);
  void update_min_max();

 public:
  // Constructors
  Tree();
  ~Tree();

  // Functions
  void merge(Tree<T>& other);
  void delete_tree();
  void copy_tree(const Tree<T>& other);

  // Elements access
  TreeNode<T>* get_node_by_value(const_reference value);
  iterator lower_bound(const_reference value);
  iterator upper_bound(const_reference value);
  std::pair<iterator, iterator> equal_range(const_reference value);

  // Elements insertion
  std::pair<iterator, bool> put_with_duplicate(const_reference value);
  std::pair<iterator, bool> put_without_duplicate(const_reference value);
  std::pair<iterator, bool> put_or_assign(const_reference value);

  // Elemnts delete
  void remove(reference value);
  void remove_node(TreeNode<T>* removable);

  // Lookup
  bool does_node_exist(const_reference value);
  size_type count(const_reference value);

  // Iterators
  iterator begin();
  iterator end();

  const_iterator cbegin();
  const_iterator cend();
};

// Constructors
template <typename T>
Tree<T>::Tree() {}

template <typename T>
Tree<T>::~Tree() {
  delete_tree();
}

// Functions
template <typename T>
void Tree<T>::merge(Tree<T>& other) {
  for (Tree<T>::iterator it = other.begin(); it != other.end();) {
    if (!does_node_exist(*it)) {
      put_with_duplicate(*it);
      other.remove(*it);
      it = other.begin();
    } else {
      ++it;
    }
  }
}

template <typename T>
void Tree<T>::delete_tree() {
  while (_root) {
    remove_node(_root);
  }
}

template <typename T>
void Tree<T>::copy_tree(const Tree<T>& other) {
  delete_tree();
  for (Tree<T>::iterator it(other._min, other._min, other._max);
       it != Tree<T>::iterator(nullptr, other._min, other._max); ++it) {
    put_with_duplicate(*it);
  }
}

// Elements access
template <typename T>
TreeNode<T>* Tree<T>::get_node_by_value(const_reference value) {
  TreeNode<T>* current = _root;
  while (current != nullptr) {
    if (value < current->get_value()) {
      if (current->has_left()) {
        current = current->get_left();
      } else {
        break;
      }
    } else if (value > current->get_value()) {
      if (current->has_right()) {
        current = current->get_right();
      } else {
        break;
      }
    } else {
      return current;
    }
  }
  return nullptr;
}

template <typename T>
typename Tree<T>::iterator Tree<T>::lower_bound(const_reference value) {
  iterator it = begin();
  for (; it != end() && *it != value; ++it) {
  }
  return it;
}

template <typename T>
typename Tree<T>::iterator Tree<T>::upper_bound(const_reference value) {
  iterator it = lower_bound(value);
  for (; it != end() && *it == value; ++it) {
  }
  return it;
}

template <typename T>
std::pair<typename Tree<T>::iterator, typename Tree<T>::iterator>
Tree<T>::equal_range(const_reference value) {
  std::pair<iterator, iterator> iterators;
  iterators.first = lower_bound(value);
  iterators.second = upper_bound(value);
  return iterators;
}

// Elements insertion
template <typename T>
std::pair<typename Tree<T>::iterator, bool> Tree<T>::put_with_duplicate(
    const_reference value) {
  return put(value, true, false);
}

template <typename T>
std::pair<typename Tree<T>::iterator, bool> Tree<T>::put_without_duplicate(
    const_reference value) {
  return put(value, false, false);
}

template <typename T>
std::pair<typename Tree<T>::iterator, bool> Tree<T>::put_or_assign(
    const_reference value) {
  return put(value, false, true);
}

// Elemnts delete
template <typename T>
void Tree<T>::remove(reference value) {
  TreeNode<T>* temp = _root;
  while (temp != nullptr) {
    if (value < temp->get_value()) {
      if (temp->get_left() == nullptr)
        break;
      else
        temp = temp->get_left();
    } else if (value == temp->get_value()) {
      break;
    } else {
      if (temp->get_right() == nullptr)
        break;
      else
        temp = temp->get_right();
    }
  }
  remove_node(temp);
}

template <typename T>
void Tree<T>::remove_node(TreeNode<T>* removable) {
  TreeNode<T>* successor = get_successor(removable);
  bool is_double_black = ((successor == nullptr || successor->is_black()) &&
                          (removable->is_black()));
  if (successor == nullptr) {
    remove_node_without_successor(removable, is_double_black);
  } else if (!removable->has_left() || !removable->has_right()) {
    remove_node_with_successor(removable, successor, is_double_black);
  } else {
    successor->swap_values(removable);
    update_min_max();
    remove_node(successor);
  }
}

// Lookup
template <typename T>
bool Tree<T>::does_node_exist(const_reference value) {
  return get_node_by_value(value) != nullptr;
}

template <typename T>
typename Tree<T>::size_type Tree<T>::count(const_reference value) {
  size_type quantity = 0;
  std::pair<iterator, iterator> iterators = equal_range(value);
  for (iterator it = iterators.first; it != iterators.second; ++it) {
    ++quantity;
  }
  return quantity;
}

// Iterators
template <typename T>
typename Tree<T>::iterator Tree<T>::begin() {
  return iterator(_min, _min, _max);
}

template <typename T>
typename Tree<T>::iterator Tree<T>::end() {
  return iterator(nullptr, _min, _max);
}

template <typename T>
typename Tree<T>::const_iterator Tree<T>::cbegin() {
  return const_iterator(_min, _min, _max);
}

template <typename T>
typename Tree<T>::const_iterator Tree<T>::cend() {
  return const_iterator(nullptr, _min, _max);
}

// Private
template <typename T>
std::pair<typename Tree<T>::iterator, bool> Tree<T>::put(const_reference value,
                                                         bool allow_duplicate,
                                                         bool allow_assign) {
  TreeNode<T>* node = new TreeNode<T>(value);
  if (_root == nullptr) {
    node->set_black();
    _root = node;
    _min = node;
    _max = node;
  } else {
    TreeNode<T>* tmp = get_available_place(value);
    if (allow_assign && tmp->get_value() == value) {
      tmp->set_value(value);
      delete node;
      return std::make_pair(iterator(tmp, _min, _max), true);
    }
    if (!allow_duplicate && tmp->get_value() == value) {
      delete node;
      return std::make_pair(iterator(tmp, _min, _max), false);
    }
    if (tmp->has_right() && allow_duplicate) {
      tmp = tmp->get_right();
      while (tmp->has_right() && tmp->get_right()->get_value() == value) {
        tmp = tmp->get_right();
      }
      while (tmp->has_left()) {
        tmp = tmp->get_left();
      }
    }
    node->set_parent(tmp);
    if (value < tmp->get_value()) {
      tmp->set_left(node);
    } else {
      tmp->set_right(node);
    }
    fix_red_in_row(node);
  }
  if (node->get_value() < _min->get_value()) {
    _min = node;
  } else if (node->get_value() >= _max->get_value()) {
    _max = node;
  }
  return std::make_pair(iterator(node, _min, _max), true);
}

template <typename T>
void Tree<T>::rotate_left(TreeNode<T>* node) {
  TreeNode<T>* new_parent = node->get_right();
  if (_root == node) {
    _root = new_parent;
  }
  node->move_down(new_parent);
  node->set_right(new_parent->get_left());
  if (new_parent->has_left()) {
    new_parent->get_left()->set_parent(node);
  }
  new_parent->set_left(node);
}

template <typename T>
void Tree<T>::rotate_right(TreeNode<T>* node) {
  TreeNode<T>* new_parent = node->get_left();
  if (_root == node) {
    _root = new_parent;
  }
  node->move_down(new_parent);
  node->set_left(new_parent->get_right());
  if (new_parent->has_right()) {
    new_parent->get_right()->set_parent(node);
  }
  new_parent->set_right(node);
}

template <typename T>
TreeNode<T>* Tree<T>::get_available_place(const_reference value) {
  TreeNode<T>* current = _root;
  while (true) {
    if (value < current->get_value()) {
      if (current->has_left()) {
        current = current->get_left();
      } else {
        break;
      }
    } else if (value > current->get_value()) {
      if (current->has_right()) {
        current = current->get_right();
      } else {
        break;
      }
    } else {
      while (current->has_right() &&
             current->get_right()->get_value() == value) {
        current = current->get_right();
      }
      break;
    }
  }
  return current;
}

template <typename T>
void Tree<T>::swap_colors(TreeNode<T>* left, TreeNode<T>* right) {
  s21::NodeColors tmp = left->get_color();
  left->set_color(right->get_color());
  right->set_color(tmp);
  update_min_max();
}

template <typename T>
TreeNode<T>* Tree<T>::get_successor(TreeNode<T>* node) {
  if (node && node->has_left() && node->has_right()) {
    TreeNode<T>* successor = node->get_right();
    while (successor->has_left()) {
      successor = successor->get_left();
    }
    return successor;
  }
  if (!node->has_left() && !node->has_right()) {
    return nullptr;
  }
  if (node->has_left()) {
    return node->get_left();
  }
  return node->get_right();
}

template <typename T>
void Tree<T>::remove_node_without_successor(TreeNode<T>* removable,
                                            bool is_double_black) {
  TreeNode<T>* parent = removable->get_parent();
  if (removable == _root) {
    update_min_max();
    _root = nullptr;
    _min = nullptr;
    _max = nullptr;
  } else {
    if (is_double_black) {
      fix_double_black(removable);
    } else {
      if (removable->has_sibling()) {
        removable->get_sibling()->set_red();
      }
    }
    if (removable->is_left_child()) {
      parent->remove_left();
    } else {
      parent->remove_right();
    }
  }
  delete removable;
  update_min_max();
  return;
}

template <typename T>
void Tree<T>::remove_node_with_successor(TreeNode<T>* removable,
                                         TreeNode<T>* successor,
                                         bool is_double_black) {
  TreeNode<T>* parent = removable->get_parent();
  if (removable == _root) {
    removable->set_value(successor->get_value());
    removable->set_left(nullptr);
    removable->set_right(nullptr);
    delete successor;
    update_min_max();
  } else {
    if (removable->is_left_child()) {
      parent->set_left(successor);
    } else {
      parent->set_right(successor);
    }
    delete removable;
    successor->set_parent(parent);
    if (is_double_black) {
      fix_double_black(successor);
    } else {
      successor->set_black();
    }
    update_min_max();
  }
}

template <typename T>
void Tree<T>::fix_red_in_row(TreeNode<T>* node) {
  if (node == _root) {
    node->set_black();
    return;
  }
  TreeNode<T>* parent = node->get_parent();
  TreeNode<T>* grand_parent = node->get_grand_parent();
  TreeNode<T>* uncle = node->get_uncle();
  if (parent->is_red()) {
    if (uncle != nullptr && uncle->is_red()) {
      parent->set_black();
      uncle->set_black();
      grand_parent->set_red();
      fix_red_in_row(grand_parent);
    } else {
      if (parent->is_left_child()) {
        if (node->is_left_child()) {
          swap_colors(parent, grand_parent);
        } else {
          rotate_left(parent);
          swap_colors(node, grand_parent);
        }
        rotate_right(grand_parent);
      } else {
        if (node->is_left_child()) {
          rotate_right(parent);
          swap_colors(node, grand_parent);
        } else {
          swap_colors(parent, grand_parent);
        }
        rotate_left(grand_parent);
      }
    }
  }
}

template <typename T>
void Tree<T>::fix_double_black(TreeNode<T>* node) {
  if (_root == node) {
    return;
  }
  TreeNode<T>* sibling = node->get_sibling();
  TreeNode<T>* parent = node->get_parent();

  if (sibling == nullptr) {
    fix_double_black(parent);
  } else {
    if (sibling->is_red()) {
      parent->set_red();
      sibling->set_black();
      if (sibling->is_left_child()) {
        rotate_right(parent);
      } else {
        rotate_left(parent);
      }
      fix_double_black(node);
    } else {
      if (sibling->has_red_child()) {
        if (sibling->has_left() && sibling->get_left()->is_red()) {
          if (sibling->is_left_child()) {
            sibling->get_left()->set_color(sibling->get_color());
            sibling->set_color(parent->get_color());
            rotate_right(parent);
          } else {
            sibling->get_left()->set_color(parent->get_color());
            rotate_right(sibling);
            rotate_left(parent);
          }
        } else {
          if (sibling->is_left_child()) {
            sibling->get_right()->set_color(parent->get_color());
            rotate_left(sibling);
            rotate_right(parent);
          } else {
            sibling->get_right()->set_color(sibling->get_color());
            sibling->set_color(parent->get_color());
            rotate_left(parent);
          }
        }
        parent->set_black();
      } else {
        sibling->set_red();
        if (parent->is_black()) {
          fix_double_black(parent);
        } else {
          parent->set_black();
        }
      }
    }
  }
}

template <typename T>
void Tree<T>::update_min_max() {
  TreeNode<T>* node = _root;
  if (node != nullptr) {
    while (node->has_left()) {
      node = node->get_left();
    }
    _min = node;
    node = _root;
    while (node->has_right()) {
      node = node->get_right();
    }
    _max = node;
  }
}

}  // namespace s21
