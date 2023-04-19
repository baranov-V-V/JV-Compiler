#include "class_ref.hpp"

SharedPtr<Type> ClassRef::GetType() const {
  return type;
}

std::string ClassRef::ToString() const {
  return type->ToString() + "&";
}

bool ClassRef::Equals(const IRObject* obj) {
  //TODO(make equals)
  return false;
}

ClassRef::ClassRef(const SharedPtr<ClassType>& type, IRObject::ScopeType scope_type) :
  type(type), IRObject(scope_type) {

}
