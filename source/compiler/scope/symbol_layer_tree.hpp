#pragma once

#include <stack>
#include "scope_layer.hpp"

class SymbolLayerTree {
 public:
  explicit SymbolLayerTree(ScopeLayer* root);
  ~SymbolLayerTree();

  void AddLayer(ScopeLayer* parent);
  //void AddLayer(ScopeLayer* parent, ScopeLayer* class_layer);

  class Iterator : public std::iterator<std::input_iterator_tag, ScopeLayer*> {
   public:
    Iterator() = default;
    explicit Iterator(ScopeLayer* root);
    explicit Iterator(ScopeLayer* root, ScopeLayer* parent, int idx);
    explicit Iterator(ScopeLayer* root, ScopeLayer* parent);

    Iterator& operator++();
    reference operator*() const;
    ScopeLayer* operator->() const;

    void GoDown();
    void GoUp();

   private:

    ScopeLayer* root;
    ScopeLayer* current_parent;

    int curr_idx;
    std::stack<int> child_indexes;
  };

  Iterator begin();
  Iterator end();

 private:
  ScopeLayer* root;
};
