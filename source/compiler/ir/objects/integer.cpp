#include "integer.hpp"
#include "types/type_factory.hpp"

SharedPtr<Type> Integer::GetType() const {
  return TypeFactory::GetIntTy();
}

std::string Integer::ToString() const {
  return TypeFactory::GetIntTy()->ToString();
}

bool Integer::Equals(const IRObject* obj) {
  return true;
  if (obj->GetType() != this->GetType()) {
    return false;
  }
  Integer* casted_obj = (Integer*) obj;
  //return casted_obj->value == this->value;
}

Integer::Integer(IRObject::ScopeType scope_type) : IRObject(scope_type) {

}
