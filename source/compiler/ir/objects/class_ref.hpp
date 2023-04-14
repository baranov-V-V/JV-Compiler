#pragma once

#include "types/class_type.hpp"
#include "ir_object.hpp"

class ClassRef : public IRObject {
 public:
  explicit ClassRef(const SharedPtr<ClassType>& type);

  ~ClassRef() override = default;

  [[nodiscard]] SharedPtr<Type> GetType() const override;
  [[nodiscard]] std::string ToString() const override;

  bool Equals(const IRObject* obj) override;

 private:
  SharedPtr<ClassType> type;
};
