#pragma once

#include "types/class_type.hpp"
#include "ir_object.hpp"

class ClassRef : public IRObject {
 public:
  explicit ClassRef(const SharedPtr<ClassType>& type, IRObject::ScopeType scope_type);

  ~ClassRef() override = default;

  [[nodiscard]] SharedPtr<Type> GetType() const override;

  [[nodiscard]] std::string ToString() const override;

  bool Equals(const IRObject* obj) override;

 private:
  //value is pointer to heap-allocated class
  SharedPtr<ClassType> type;
};
