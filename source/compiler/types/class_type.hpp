#pragma once

#include "type.hpp"
#include "method_type.hpp"

class ClassType : public Type {
 public:
  ClassType();
  ClassType(const std::vector<ArgEntry>& args, const SharedPtr<Type>& return_type);

  [[nodiscard]] const std::vector<ArgEntry>& GetArgs() const;
  void AddArg(const ArgEntry& arg_entry);

  [[nodiscard]] SharedPtr<Type> GetReturnType() const;
  [[nodiscard]] int GetArgsNum() const;

 private:
  std::vector<SharedPtr<MethodType>> methods;
  std::vector<SharedPtr<Type>> fields;
};