#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include "fmt/os.h"

#include "util/symbol.hpp"
#include "ir/objects/ir_object.hpp"
#include "types/class_type.hpp"
#include "types/array_type.hpp"

class ClassScopeLayer;

//TODO Add MethodSupport and FindMethod Functions;
//Doest do any checks, all checks belong to SymbolTableVisitor
class ScopeLayer {
 public:
  explicit ScopeLayer(const std::string& name = "anonymous");
  explicit ScopeLayer(ScopeLayer* parent, const std::string& name = "anonymous");
  explicit ScopeLayer(ScopeLayer* parent, ClassScopeLayer* class_layer, const std::string& name = "anonymous");
  virtual ~ScopeLayer();
  
  void DeclareVariable(const Symbol& symbol, const SharedPtr<Type>& type);
  void DeclareVariable(const Symbol& symbol, const std::shared_ptr<IRObject>& type);

  [[nodiscard]] std::shared_ptr<IRObject>& GetFromCurrent(const Symbol& symbol);
  [[nodiscard]] const std::shared_ptr<IRObject>& GetFromAnywhere(const Symbol& symbol) const;
  [[nodiscard]] std::vector<std::shared_ptr<IRObject>> GetAllFromCurrent() const;

  template<class ObjType>
  [[nodiscard]] std::shared_ptr<ObjType>& GetTypedFromCurrent(const Symbol& symbol);

  template<class ObjType>
  [[nodiscard]] const std::shared_ptr<ObjType>& GetTypedFromAnywhere(const Symbol& symbol) const;

  void Put(const Symbol& symbol, std::shared_ptr<IRObject> value);

  [[nodiscard]] bool IsDeclaredCurrent(const Symbol& symbol) const;
  [[nodiscard]] bool IsDeclaredAnywhere(const Symbol& symbol) const;

  void AddChild(ScopeLayer* child);

  [[nodiscard]] int GetChildNum() const;
  [[nodiscard]] ScopeLayer* GetChild(int idx) const;
  [[nodiscard]] ScopeLayer* GetParent() const;

  ClassScopeLayer* GetClassScope();

  //TODO make private
  virtual void GraphVizDump(fmt::ostream& ostream);

 protected:
  //void CheckDeclared(const Symbol& symbol, const SharedPtr<Type>& type) const;

  //void CheckDeclared(const Symbol& symbol) const;

  std::string name = "anonymous";

  ScopeLayer* parent;
  std::vector<ScopeLayer*> children;

  std::unordered_map<Symbol, std::shared_ptr<IRObject>> variables;

  ClassScopeLayer* class_scope;
 private:

  void DeclareClass(const Symbol& symbol, const SharedPtr<ClassType>& type);
  void DeclareArray(const Symbol& symbol, const SharedPtr<ArrayType>& type);
  void DeclarePrimitive(const Symbol& symbol, const SharedPtr<Type>& type);
  void DeclareMethod(const Symbol& symbol, const SharedPtr<MethodType>& type);
};
