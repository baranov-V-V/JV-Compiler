#include "compiler/core/logger.hpp"

#include "compiler/ir/objects/object_factory.hpp"
#include "scope_layer.hpp"
#include "class_scope_layer.hpp"

ScopeLayer::ScopeLayer() : parent(nullptr), class_scope(nullptr) {}

ScopeLayer::ScopeLayer(ScopeLayer* parent, const std::string& name) : parent(parent), name(name), class_scope(parent->class_scope) {}

ScopeLayer::~ScopeLayer() {
  for (ScopeLayer* layer : children) {
    delete layer;
  }
}

int ScopeLayer::GetChildNum() const {
  return children.size();
}

ScopeLayer* ScopeLayer::GetChild(int idx) const {
  return children.at(idx);
}

ScopeLayer* ScopeLayer::GetParent() const {
  return parent;
}

void ScopeLayer::DeclareVariable(const Symbol& symbol, const SharedPtr<Type>& type) {
  CheckDeclared(symbol, type);

  if (type->IsArray()) {
    DeclareArray(symbol, std::reinterpret_pointer_cast<ArrayType>(type));
  } else if (type->IsClass()) {
    DeclareClass(symbol, std::reinterpret_pointer_cast<ClassType>(type));
  } else {
    DeclarePrimitive(symbol, type);
  }
}

void ScopeLayer::DeclareVariable(const Symbol& symbol, const std::shared_ptr<Object>& object) {
  CheckDeclared(symbol);
  variables.insert({symbol, object});
}

void ScopeLayer::DeclareArray(const Symbol& symbol, const SharedPtr<ArrayType>& type) {
  variables.insert({symbol, ObjectFactory::CreateArrayRef(type)});
}

void ScopeLayer::DeclareClass(const Symbol& symbol, const SharedPtr<ClassType>& type) {
  variables.insert({symbol, std::reinterpret_pointer_cast<Object>(ObjectFactory::CreateClassRef(type))});
}

void ScopeLayer::DeclarePrimitive(const Symbol& symbol, const SharedPtr<Type>& type) {
  variables.insert({symbol, ObjectFactory::CreatePrimitive(type)});
}

std::shared_ptr<Object>& ScopeLayer::GetFromCurrent(const Symbol& symbol) {
  CheckDeclared(symbol);

  return variables.at(symbol);
}

const std::shared_ptr<Object>& ScopeLayer::GetFromAnywhere(const Symbol& symbol) const {
  ScopeLayer* current_scope = const_cast<ScopeLayer*>(this);

  while (!current_scope->IsDeclaredCurrent(symbol) && current_scope->parent != nullptr) {
    current_scope = current_scope->parent;
  }

  CheckDeclared(symbol);
  return current_scope->GetFromCurrent(symbol);
}

bool ScopeLayer::IsDeclaredCurrent(const Symbol& symbol) const {
  return variables.contains(symbol);
}

bool ScopeLayer::IsDeclaredAnywhere(const Symbol& symbol) const {
  ScopeLayer* current_scope = const_cast<ScopeLayer*>(this);

  while (!current_scope->IsDeclaredCurrent(symbol) && current_scope->parent != nullptr) {
    current_scope = current_scope->parent;
  }
  return current_scope->IsDeclaredCurrent(symbol);
}

void ScopeLayer::CheckDeclared(const Symbol& symbol, const SharedPtr<Type>& type) const {
  if (IsDeclaredCurrent(symbol)) {
    COMPILER_ERROR("Variable: \"[{}] {}\" has been already declared", type->ToString(), symbol.name);
  }
}

void ScopeLayer::CheckDeclared(const Symbol& symbol) const {
  if (IsDeclaredCurrent(symbol)) {
    COMPILER_ERROR("Variable: \" {}\" has been already declared", symbol.name);
  }
}

ScopeLayer::ScopeLayer(ScopeLayer* parent, ClassScopeLayer* class_layer, const std::string& name) : parent(parent), name(name), class_scope(class_layer) {}

void ScopeLayer::Put(const Symbol& symbol, std::shared_ptr<Object> value) {
  if (!IsDeclaredCurrent(symbol)) {
    variables.insert({symbol, value});
  }
}

void ScopeLayer::AddChild(ScopeLayer* child) {
  children.push_back(child);
}

ClassScopeLayer* ScopeLayer::GetClassScope() {
  return class_scope;
}

void ScopeLayer::GraphVizDump(fmt::ostream& ostream) {
  ostream.print("\tnode{} [label=\"<LayerName> {}\"];", (void*) this, this->name);

  for (const auto& entry: variables) {
    ostream.print("\tnode{} [label=\"<Type> {}|<Var> {}\"];",
                  (void*) &entry.first, entry.second->GetType()->ToString(), entry.first.name);
    ostream.print("\t\tnode{}:s -> node{} [color=\"grey14\"];\n", (void*) this, (void*) &entry.first);
  }

  for (ScopeLayer* layer : children) {
    layer->GraphVizDump(ostream);
  }
}

/*
void ScopeLayer::DeclareMethod(const Symbol& symbol, const SharedPtr<MethodType>& type) {
  variables.insert({symbol, std::reinterpret_pointer_cast<Object>(ObjectFactory::CreateMethod(type))});
}
*/

template<class ObjType>
std::shared_ptr<ObjType>& ScopeLayer::GetTypedFromCurrent(const Symbol& symbol) {
  return std::reinterpret_pointer_cast<ObjType>(ScopeLayer::GetFromCurrent(symbol));
}

template<class ObjType>
const std::shared_ptr<ObjType>& ScopeLayer::GetTypedFromAnywhere(const Symbol& symbol) const {
  return std::reinterpret_pointer_cast<ObjType>(ScopeLayer::GetFromAnywhere(symbol));
}
