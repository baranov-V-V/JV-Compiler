#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include "util/symbol.hpp"
#include "objects/object.hpp"
#include "types/class_type.hpp"
#include "types/array_type.hpp"

class ScopeLayer {
 public:
  ScopeLayer();
  explicit ScopeLayer(ScopeLayer* parent);
  virtual ~ScopeLayer();
  
  void DeclareVariable(const Symbol& symbol, const SharedPtr<Type>& type);
  //void DeclareClass(const Symbol& symbol, SharedPtr<ClassType> type);
  void DeclareArray(const Symbol& symbol, SharedPtr<ArrayType> type);

  [[nodiscard]] std::shared_ptr<Object>& GetFromCurrent(const Symbol& symbol);
  [[nodiscard]] const std::shared_ptr<Object>& GetFromAnywhere(const Symbol& symbol) const;

  virtual void Put(Symbol symbol, std::shared_ptr<Object> value) = 0;

  /*
  bool IsClassData(Symbol symbol) const;
  bool IsArgument(Symbol symbol) const;
  size_t GetArgIndex(Symbol symbol) const;
  */

  //[[nodiscard]] SharedPtr<Type> GetType(const Symbol& symbol) const;

  [[nodiscard]] bool IsDeclaredCurrent(const Symbol& symbol) const;
  [[nodiscard]] bool IsDeclaredAnywhere(const Symbol& symbol) const;

  virtual void AddChild(ScopeLayer* child) = 0;

  /*
  void AttachParent(std::shared_ptr<ScopeLayer> parent);
  void AttachClass(std::shared_ptr<ScopeLayer> class_scope);
  */

  [[nodiscard]] int GetChildNum() const;
  [[nodiscard]] ScopeLayer* GetChild(int idx) const;
  [[nodiscard]] ScopeLayer* GetParent() const;

 protected:
  std::string name = "anonymous";
  ScopeLayer* parent;

  std::vector<ScopeLayer*> children;
  std::unordered_map<Symbol, std::shared_ptr<Object>> variables;

  ScopeLayer* class_scope;
};
