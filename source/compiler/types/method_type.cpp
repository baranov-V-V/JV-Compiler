
#include <vector>
#include <memory>
#include "method_type.hpp"

MethodType::MethodType(const Symbol& name, const std::vector<TypeEntry>& args, const SharedPtr<Type>& return_type)
  : Type(Type::TypeID::MethodTy), args(args), return_type(return_type), name(name) {}

const std::vector<TypeEntry>& MethodType::GetArgs() const {
  return args;
}

void MethodType::AddArg(const TypeEntry& arg_entry) {
  args.push_back(arg_entry);
}

SharedPtr<Type> MethodType::GetReturnType() const {
  return return_type;
}

int MethodType::GetArgsNum() const {
  return args.size();
}

MethodType::MethodType() : Type(Type::TypeID::MethodTy) {}

std::string MethodType::ToString() const {
  std::string res;
  res += "'" + return_type->ToString() + " " + name.name + "(";
  for (const TypeEntry& entry : args) {
    res += entry.type->ToString() + " " + entry.symbol.name + ", ";
  }
  res += ")'";
  return res;
}

bool MethodType::Equals(std::shared_ptr<Type> other) {
  if (other->GetTypeId() != TypeID::MethodTy) {
    return false;
  }
  SharedPtr<MethodType> casted_other = std::reinterpret_pointer_cast<MethodType>(other);

  return args == casted_other->args && return_type->Equals(casted_other->return_type) && casted_other->name == name;
}

const TypeEntry& MethodType::GetArg(int idx) const {
  return args.at(idx);
}

const Symbol& MethodType::GetName() const {
  return name;
}
