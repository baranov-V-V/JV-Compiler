#pragma once

#include "object.hpp"

class Bool : public Object {
 public:
  explicit Bool(bool value);
  ~Bool() override = default;

  [[nodiscard]] bool GetValue() const;
  void SetValue(bool value);

  [[nodiscard]] SharedPtr<Type> GetType() const override;
  [[nodiscard]] std::string ToString() const override;
  [[nodiscard]] bool Equals(const Object* obj) override;

 private:
  bool value;
};
