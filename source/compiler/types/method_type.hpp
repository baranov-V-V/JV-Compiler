#pragma once

#include <vector>

#include "type.hpp"
#include "util/type_entry.hpp"

class MethodType : public Type {
 public:
  MethodType();

  MethodType(const Symbol& name, const std::vector<TypeEntry>& args, const SharedPtr<Type>& return_type);

  [[nodiscard]] std::string ToString() const override;

  bool Equals(std::shared_ptr<Type> other) override;

  [[nodiscard]] const std::vector<TypeEntry>& GetArgs() const;

  [[nodiscard]] const TypeEntry& GetArg(int idx) const;

  [[nodiscard]] const Symbol& GetName() const;

  void AddArg(const TypeEntry& arg_entry);

  [[nodiscard]] SharedPtr<Type> GetReturnType() const;

  [[nodiscard]] int GetArgsNum() const;

 private:
  Symbol name;
  std::vector<TypeEntry> args;
  SharedPtr<Type> return_type;
};