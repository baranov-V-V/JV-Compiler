#include "compiler/core/logger.hpp"
#include "scope_layer.hpp"

ScopeLayer::ScopeLayer() : parent(nullptr), class_scope(nullptr) {}

ScopeLayer::ScopeLayer(ScopeLayer* parent) : parent(parent), class_scope(parent->class_scope) {}

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
  if (IsDeclaredCurrent(symbol)) {
    COMPILER_ERROR("Variable: \"[{}] {}\" has been already declared", type->ToString(), symbol.name);
  }

  variables.insert({symbol, std::make_shared<Object>(type)});
}

void ScopeLayer::DeclareArray(const Symbol& symbol, SharedPtr<ArrayType> type) {

}

std::shared_ptr<Object>& ScopeLayer::GetFromCurrent(const Symbol& symbol) {
  return ;
}

const std::shared_ptr<Object>& ScopeLayer::GetFromAnywhere(const Symbol& symbol) const {
  return;
}

bool ScopeLayer::IsDeclaredCurrent(const Symbol& symbol) const {
  return false;
}

bool ScopeLayer::IsDeclaredAnywhere(const Symbol& symbol) const {
  return false;
}
