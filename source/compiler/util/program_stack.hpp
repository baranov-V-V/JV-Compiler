#pragma once

#include <deque>

class ProgramStack {
 public:
  int Top() const;
  void Pop();
  void Put(int value);
  int TopAndPop();
  void Clear();
 private:
  std::deque<int> data;
};