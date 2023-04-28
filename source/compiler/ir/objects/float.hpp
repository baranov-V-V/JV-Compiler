#pragma once

#include "ir_object.hpp"

class Float : public IRObject {
 public:
  Float() = default;
  explicit Float(float value);
  ~Float() override = default;

  [[nodiscard]] float GetValue() const;
  void SetValue(float value);

  [[nodiscard]] SharedPtr<Type> GetType() const override;
  [[nodiscard]] std::string ToString() const override;
  [[nodiscard]] bool Equals(const IRObject* obj) override;

 private:
  //llvm:Value* value;
  float value = 0.0;
};
