#pragma once

#include <filesystem>

#include <stack>
#include <map>
#include "scope/layers/scope_layer.hpp"
#include "types/util/class_info.hpp"

class SymbolLayerTree {
 public:
  friend class ScopeLayer;

  explicit SymbolLayerTree(ScopeLayer* root);
  ~SymbolLayerTree();

  void AddLayer(ScopeLayer* parent, const std::string& name = "anonymous");
  void AddClassLayer(ScopeLayer* parent, SharedPtr<ClassType> type);

  void DumpTree(const std::filesystem::path& path);

  //SharedPtr<MethodType> GetMethod(const Symbol& class_name, const Symbol& method_name);
  //ClassInfo GetClass(const Symbol& class_name, const Symbol& method_name);

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
    //std::stack<int> child_indexes;

    std::map<ScopeLayer*, int> child_indexes;
  };

  Iterator begin();
  Iterator end();

 private:
  ScopeLayer* root;
};
