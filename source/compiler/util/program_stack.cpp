#include "program_stack.hpp"

int ProgramStack::Top() const {
  return data.front();
}

void ProgramStack::Pop() {
  data.pop_front();
}

void ProgramStack::Put(int value) {
  data.push_back(value);
}

int ProgramStack::TopAndPop() {
  int top = data.front();
  data.pop_front();
  return top;
}

void ProgramStack::Clear() {
  data.clear();
}
