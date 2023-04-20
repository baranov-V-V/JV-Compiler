#pragma once

#include "scope/layers/scope_layer.hpp"

class MethodScopeLayer : ScopeLayer {
 public:
  explicit MethodScopeLayer(ScopeLayer* parent, SharedPtr<MethodType> type);

  ~MethodScopeLayer() override = default;

  [[nodiscard]] SharedPtr<MethodType> GetType() const;

 private:
  SharedPtr<MethodType> type;
};
