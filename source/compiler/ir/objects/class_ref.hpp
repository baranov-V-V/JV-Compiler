#pragma once

#include "types/class_type.hpp"
#include "object.hpp"

class ClassRef : public Object {
 public:
  explicit ClassRef(const SharedPtr<ClassType>& type);

  ~ClassRef() override = default;

  [[nodiscard]] SharedPtr<Type> GetType() const override;
  [[nodiscard]] std::string ToString() const override;

  bool Equals(const Object* obj) override;

 private:

  SharedPtr<ClassType> type;
};
