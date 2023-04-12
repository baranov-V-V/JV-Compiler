#pragma once

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Value.h>
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "types/type.hpp"
#include "types/class_type.hpp"

class LLVMTypeConverter {
 public:
  LLVMTypeConverter(llvm::LLVMContext* context, llvm::Module* module);

  llvm::Type* GetLLVMType(const SharedPtr<Type>& type);

 private:
  llvm::LLVMContext* context;
  llvm::Module* module;
};
