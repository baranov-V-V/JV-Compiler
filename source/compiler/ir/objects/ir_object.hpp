#pragma once

#include <string>
#include <llvm/IR/Value.h>
#include <llvm/IR/Instructions.h>

#include "compiler/types/type.hpp"

class IRObject {
 public:
  enum class ScopeType {
    Field,
    Local,
    Global
  };

  explicit IRObject(IRObject::ScopeType type = ScopeType::Local);
  virtual ~IRObject() = default;

  [[nodiscard]] virtual SharedPtr<Type> GetType() const = 0;
  [[nodiscard]] virtual std::string ToString() const = 0;

  [[nodiscard]] llvm::Value* Get() const;
  void Set(llvm::Value* object);

  [[nodiscard]] ScopeType GetScopeType() const;
  [[nodiscard]] bool IsLocal() const;
  [[nodiscard]] bool IsGlobal() const;
  [[nodiscard]] bool IsField() const;

  [[nodiscard]] virtual bool Equals(const IRObject* obj) = 0;

 private:
  IRObject::ScopeType scope_type;
  llvm::Value* object = nullptr;
};
