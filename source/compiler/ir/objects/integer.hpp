#pragma once

#include "ir_object.hpp"

class Integer : public IRObject {
 public:
  Integer() = default;
  explicit Integer(int value);
  ~Integer() override = default;

  [[nodiscard]] int GetValue() const;
  void SetValue(int value);

  [[nodiscard]] SharedPtr<Type> GetType() const override;
  [[nodiscard]] std::string ToString() const override;
  [[nodiscard]] bool Equals(const IRObject* obj) override;

 private:
  //llvm::Value*;
  int value = 0;
};
