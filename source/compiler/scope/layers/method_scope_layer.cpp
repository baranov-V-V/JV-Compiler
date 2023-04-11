#include "method_scope_layer.hpp"

MethodScopeLayer::MethodScopeLayer(ScopeLayer* parent, SharedPtr<MethodType> type) :
  ScopeLayer(parent, type->ToString()), type(type) {
}

SharedPtr<MethodType> MethodScopeLayer::GetType() const {
  return type;
}
