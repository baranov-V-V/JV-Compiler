#pragma once

#include <initializer_list>

#include "type.hpp"
#include "method_type.hpp"


class ClassType : public Type {
 public:
  explicit ClassType(const Symbol& symbol);

  [[nodiscard]] std::string ToString() const override;

  bool Equals(std::shared_ptr<Type> other) override;

  [[nodiscard]] const Symbol& GetName() const;

 private:
  Symbol name;
};

struct ClassTypeHash {
  std::size_t operator()(const SharedPtr<ClassType>& other) const {
    return std::hash<std::string>()(other->GetName().name);
  }
};

struct ClassTypeEq {
  bool operator()(const SharedPtr<ClassType>& lhs, const SharedPtr<ClassType>& rhs) const {
    return lhs->Equals(rhs);
  }
};