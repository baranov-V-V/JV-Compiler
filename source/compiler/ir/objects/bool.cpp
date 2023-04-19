#include "bool.hpp"
#include "types/type_factory.hpp"

SharedPtr<Type> Boolean::GetType() const {
  return TypeFactory::GetBoolTy();
}

std::string Boolean::ToString() const {
  return TypeFactory::GetBoolTy()->ToString();
}

bool Boolean::Equals(const IRObject* obj) {
  //TODO(make equals)
  return false;
}

Boolean::Boolean(IRObject::ScopeType scope_type) : IRObject(scope_type) {

}
