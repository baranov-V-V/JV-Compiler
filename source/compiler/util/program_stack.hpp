#pragma once

#include "compiler/core/logger.hpp"
#include <deque>

template <typename T>
class ProgramStack {
 public:
  ProgramStack();
  ~ProgramStack();

  T& Top() const;
  void Pop();
  void Put(const T& value);
  T TopAndPop();
  void Clear();

  std::deque<T>& GetData();

 private:
  std::deque<T> data;
};

template<typename T>
std::deque<T>& ProgramStack<T>::GetData() {
  return data;
}

template <typename T>
inline ProgramStack<T>::ProgramStack() {
  LOG_TRACE("Program stack Ctor") 
}

template <typename T>
inline ProgramStack<T>::~ProgramStack() {
  LOG_TRACE("Program stack Dtor") 
}

template <typename T>
T& ProgramStack<T>::Top() const {
  return data.front();
}

template <typename T>
void ProgramStack<T>::Pop() {
  if (!data.empty()) {
    data.pop_front();
  }
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