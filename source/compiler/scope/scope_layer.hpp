#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include "util/symbol.hpp"
#include "objects/object.hpp"

class ScopeLayer {
 public:
  ScopeLayer() = default;
  ScopeLayer(ScopeLayer* parent);
  
  //void DeclareVariable(Symbol symbol, Type type);

  virtual std::shared_ptr<Object>& Get(Symbol symbol) = 0;
  [[nodiscard]] virtual const std::shared_ptr<Object>& Get(Symbol symbol) const = 0;
  virtual void Put(Symbol symbol, std::shared_ptr<Object> value) = 0;

  /*
  bool IsClassData(Symbol symbol) const;
  bool IsArgument(Symbol symbol) const;
  size_t GetArgIndex(Symbol symbol) const;
  */

  [[nodiscard]] virtual SharedPtr<Type> GetType(Symbol symbol) const = 0;

  [[nodiscard]] virtual bool IsDeclared(Symbol symbol) const = 0;
  [[nodiscard]] virtual bool IsDeclaredAnywhere(Symbol symbol) const = 0;

  virtual void AddChild(ScopeLayer* child) = 0;

  /*
  void AttachParent(std::shared_ptr<ScopeLayer> parent);
  void AttachClass(std::shared_ptr<ScopeLayer> class_scope);
  */

  [[nodiscard]] virtual int GetChildNum() const = 0;
  [[nodiscard]] virtual ScopeLayer* GetChild(int idx) const = 0;
  [[nodiscard]] virtual ScopeLayer* GetParent() const = 0;
};
