#include "ir_object.hpp"

llvm::Value* IRObject::Get() const {
  return object;
}

void IRObject::Set(llvm::Value* object) {
  IRObject::object = object;
}
