#include "class_scope_layer.hpp"

ClassScopeLayer::~ClassScopeLayer() {
  //pass;
}

ClassScopeLayer::ClassScopeLayer(ScopeLayer* parent, SharedPtr<ClassType> type) :
  ScopeLayer(parent, this, type->ToString()), type(type) {
}

SharedPtr<ClassType> ClassScopeLayer::GetType() const {
  return type;
}
