#pragma once

#include <stack>
#include "scope/layers/scope_layer.hpp"

class SymbolLayerTree {
 public:
  explicit SymbolLayerTree(ScopeLayer* root);
  ~SymbolLayerTree();

  void AddLayer(ScopeLayer* parent, const std::string& name = "anonymous");
  void AddClassLayer(ScopeLayer* parent, SharedPtr<ClassType> type);

  class Iterator : public std::iterator<std::input_iterator_tag, ScopeLayer*, int, ScopeLayer*, ScopeLayer*> {
   public:
    Iterator() = default;
    explicit Iterator(ScopeLayer* root);
    explicit Iterator(ScopeLayer* root, ScopeLayer* parent, int idx);
    explicit Iterator(ScopeLayer* root, ScopeLayer* parent);

    Iterator& operator++();
    ScopeLayer* operator*() const;
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
