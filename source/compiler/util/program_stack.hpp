#pragma once

#include <deque>

template <typename T>
class ProgramStack {
 public:
  T& Top() const;
  void Pop();
  void Put(const T& value);
  T TopAndPop();
  void Clear();
 private:
  std::deque<T> data;
};

template <typename T>
T& ProgramStack<T>::Top() const {
  return data.front();
}

template <typename T>
void ProgramStack<T>::Pop() {
  data.pop_front();
}

template <typename T>
void ProgramStack<T>::Put(const T& value) {
  data.push_back(value);
}

template <typename T>
T ProgramStack<T>::TopAndPop() {
  T top = data.front();
  data.pop_front();
  return top;
}

template <typename T>
void ProgramStack<T>::Clear() {
  data.clear();
}