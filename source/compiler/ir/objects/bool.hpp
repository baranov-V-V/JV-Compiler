#pragma once

#include "ir_object.hpp"

class Boolean : public IRObject {
 public:
  Boolean() = default;
  explicit Boolean(bool value);
  ~Boolean() override = default;

  [[nodiscard]] bool GetValue() const;
  void SetValue(bool value);

  [[nodiscard]] SharedPtr<Type> GetType() const override;
  [[nodiscard]] std::string ToString() const override;
  [[nodiscard]] bool Equals(const IRObject* obj) override;

 private:
  bool value = false;
};
