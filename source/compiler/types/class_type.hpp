#pragma once

#include <initializer_list>

#include "type.hpp"
#include "method_type.hpp"


class ClassType : public Type {
 public:
  explicit ClassType(const Symbol& symbol);

  [[nodiscard]] std::string ToString() const override;

  bool Equals(std::shared_ptr<Type> other) override;

 private:
  Symbol name;
};