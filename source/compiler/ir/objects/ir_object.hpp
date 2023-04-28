#pragma once

#include <string>
#include <llvm/IR/Value.h>
#include <llvm/IR/Instructions.h>

#include "compiler/types/type.hpp"

class IRObject {
 public:
  IRObject() = default;
  virtual ~IRObject() = default;

  [[nodiscard]] virtual SharedPtr<Type> GetType() const = 0;
  [[nodiscard]] virtual std::string ToString() const = 0;

  [[nodiscard]] llvm::Value* Get() const;
  void Set(llvm::Value* object);

  [[nodiscard]] virtual bool Equals(const IRObject* obj) = 0;

 private:
  llvm::Value* object;
};
