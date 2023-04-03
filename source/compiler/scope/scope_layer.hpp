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
  explicit ScopeLayer(ScopeLayer* parent, ScopeLayer* class_layer);
  virtual ~ScopeLayer();
  
  void DeclareVariable(const Symbol& symbol, const SharedPtr<Type>& type);
  void DeclareVariable(const Symbol& symbol, const std::shared_ptr<Object>& type);
  void DeclareClass(const Symbol& symbol, const SharedPtr<ClassType>& type);
  void DeclareArray(const Symbol& symbol, const SharedPtr<ArrayType>& type);

  [[nodiscard]] std::shared_ptr<Object>& GetFromCurrent(const Symbol& symbol);
  [[nodiscard]] const std::shared_ptr<Object>& GetFromAnywhere(const Symbol& symbol) const;

  template<class ObjType>
  [[nodiscard]] std::shared_ptr<ObjType>& GetTypedFromCurrent(const Symbol& symbol);

  template<class ObjType>
  [[nodiscard]] const std::shared_ptr<ObjType>& GetTypedFromAnywhere(const Symbol& symbol) const;

  void Put(const Symbol& symbol, std::shared_ptr<Object> value);

  /*
  bool IsClassData(Symbol symbol) const;
  bool IsArgument(Symbol symbol) const;
  size_t GetArgIndex(Symbol symbol) const;
  */

  //[[nodiscard]] SharedPtr<Type> GetType(const Symbol& symbol) const;

  [[nodiscard]] bool IsDeclaredCurrent(const Symbol& symbol) const;
  [[nodiscard]] bool IsDeclaredAnywhere(const Symbol& symbol) const;

  void AddChild(ScopeLayer* child);

  /*
  void AttachParent(std::shared_ptr<ScopeLayer> parent);
  void AttachClass(std::shared_ptr<ScopeLayer> class_scope);
  */

  [[nodiscard]] int GetChildNum() const;
  [[nodiscard]] ScopeLayer* GetChild(int idx) const;
  [[nodiscard]] ScopeLayer* GetParent() const;

 protected:
  void CheckDeclared(const Symbol& symbol, const SharedPtr<Type>& type) const;
  void CheckDeclared(const Symbol& symbol) const;

  std::string name = "anonymous";
  ScopeLayer* parent;

  std::vector<ScopeLayer*> children;
  std::unordered_map<Symbol, std::shared_ptr<Object>> variables;

  ScopeLayer* class_scope;
};
