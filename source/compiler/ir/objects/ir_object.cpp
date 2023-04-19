#include "ir_object.hpp"

llvm::Value* IRObject::Get() const {
  return object;
}

void IRObject::Set(llvm::Value* object) {
  IRObject::object = object;
}

IRObject::IRObject(IRObject::ScopeType type) : scope_type(type) {

}

IRObject::ScopeType IRObject::GetScopeType() const {
  return scope_type;
}

bool IRObject::IsLocal() const {
  return GetScopeType() == ScopeType::Local;
}

bool IRObject::IsGlobal() const {
  return GetScopeType() == ScopeType::Global;
}

bool IRObject::IsField() const {
  return GetScopeType() == ScopeType::Field;
}
