#pragma once

#include "object.hpp"
#include "types/method_type.hpp"

class Method : public Object {
 public:
  explicit Method(const SharedPtr<MethodType>& type);
  ~Method() override = default;

  [[nodiscard]] SharedPtr<Type> GetType() const override;

  [[nodiscard]] std::string ToString() const override;

  [[nodiscard]] bool Equals(const Object* obj) override;

 private:
  SharedPtr<MethodType> type;
};
