#pragma once

#include <vector>

#include "type.hpp"
#include "util/arg_entry.hpp"

class MethodType : public Type {
 public:
  MethodType();
  MethodType(const std::vector<ArgEntry>& args, const SharedPtr<Type>& return_type);

  std::string ToString() const override;

  [[nodiscard]] const std::vector<ArgEntry>& GetArgs() const;
  void AddArg(const ArgEntry& arg_entry);

  [[nodiscard]] SharedPtr<Type> GetReturnType() const;
  [[nodiscard]] int GetArgsNum() const;

 private:
  std::vector<ArgEntry> args;
  SharedPtr<Type> return_type;
};