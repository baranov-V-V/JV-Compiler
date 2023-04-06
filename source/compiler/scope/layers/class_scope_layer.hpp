#pragma once

#include "scope/layers/scope_layer.hpp"

class ClassScopeLayer : public ScopeLayer {
 public:
  explicit ClassScopeLayer(ScopeLayer* parent, SharedPtr<ClassType> type);
  ~ClassScopeLayer() override;

  [[nodiscard]] SharedPtr<ClassType> GetType() const;

 private:
  SharedPtr<ClassType> type;
};
