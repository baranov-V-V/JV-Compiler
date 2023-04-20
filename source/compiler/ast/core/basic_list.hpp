#pragma once

#include <vector>
#include <memory>

#include "ast/core/ast_node.hpp"
#include "visitors/visitor.hpp"

template<typename T>
class BasicList : public AstNode {
 public:
  BasicList() = default;

  virtual ~BasicList() override;

  virtual void Accept(Visitor* visitor) override = 0;

  void Add(T* element);

  std::vector<T*> elements;
};

template<typename T>
inline BasicList<T>::~BasicList() {
  for (T* elem: elements) {
    delete elem;
  }
}

template<typename T>
inline void BasicList<T>::Add(T* element) {
  elements.push_back(element);
}
