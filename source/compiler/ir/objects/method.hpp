#pragma once

#include "ir_object.hpp"
#include "types/method_type.hpp"

class Method : public IRObject {
 public:
  explicit Method(const SharedPtr<MethodType>& type);
  ~Method() override = default;

  [[nodiscard]] SharedPtr<Type> GetType() const override;

  [[nodiscard]] std::string ToString() const override;

  [[nodiscard]] bool Equals(const IRObject* obj) override;

 private:
  SharedPtr<MethodType> type;
};
