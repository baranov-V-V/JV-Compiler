#include "float.hpp"
#include "types/type_factory.hpp"

SharedPtr<Type> Float::GetType() const {
  return TypeFactory::GetFloatTy();
}

std::string Float::ToString() const {
  return TypeFactory::GetFloatTy()->ToString();
}

bool Float::Equals(const IRObject* obj) {
  //TODO(make equals)
  return false;
}

Float::Float(IRObject::ScopeType scope_type) : IRObject(scope_type) {

}

