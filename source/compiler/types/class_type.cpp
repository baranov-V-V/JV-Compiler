#include "class_type.hpp"

ClassType::ClassType(const Symbol& symbol) : Type(Type::TypeID::ClassTy), name(symbol) {
}

std::string ClassType::ToString() const {
  return name.name;
}

bool ClassType::Equals(std::shared_ptr<Type> other) {
  if (other->GetTypeId() != TypeID::ClassTy) {
    return false;
  }
  SharedPtr<ClassType> casted_other = std::reinterpret_pointer_cast<ClassType>(other);

  return name == casted_other->name;
}

const Symbol& ClassType::GetName() const {
  return name;
}
