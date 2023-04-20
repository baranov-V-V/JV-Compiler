#pragma once

#include "ir_object.hpp"

class Float : public IRObject {
 public:
  Float(IRObject::ScopeType scope_type);

  explicit Float(float value);

  ~Float() override = default;

  [[nodiscard]] SharedPtr<Type> GetType() const override;

  [[nodiscard]] std::string ToString() const override;

  [[nodiscard]] bool Equals(const IRObject* obj) override;

 private:
};
