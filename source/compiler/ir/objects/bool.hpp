#pragma once

#include "ir_object.hpp"

class Boolean : public IRObject {
 public:
  explicit Boolean(IRObject::ScopeType scope_type);
  explicit Boolean(bool value);
  ~Boolean() override = default;

  [[nodiscard]] SharedPtr<Type> GetType() const override;
  [[nodiscard]] std::string ToString() const override;
  [[nodiscard]] bool Equals(const IRObject* obj) override;

 private:
};
