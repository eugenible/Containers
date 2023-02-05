#pragma once

namespace s21 {

template <class T1, class T2>
class pair {
 public:
  pair() {}
  pair(T1 first, T2 second) : first(first), second(second) {}
  pair(const pair& other) : first(other.first), second(other.second) {}
  pair(pair&& other) { *this = std::move(other); }
  pair& operator=(const pair& other) {
    first = other.first;
    second = other.second;
    return *this;
  }
  pair& operator=(pair&& other) {
    if (this != &other) {
      first = other.first;
      second = other.second;
      other.first = T1();
      other.second = T2();
    }
    return *this;
  }
  ~pair() {}

  T1 first;
  T2 second;

  bool operator<(const pair<T1, T2>& other) const {
    return first < other.first;
  }
  bool operator>(const pair<T1, T2>& other) const {
    return first > other.first;
  }
  bool operator<=(const pair<T1, T2>& other) const {
    return first <= other.first;
  }
  bool operator>=(const pair<T1, T2>& other) const {
    return first >= other.first;
  }
  bool operator==(const pair<T1, T2>& other) const {
    return first == other.first;
  }
  bool operator!=(const pair<T1, T2>& other) const {
    return first != other.first;
  }
};

}  // namespace s21
