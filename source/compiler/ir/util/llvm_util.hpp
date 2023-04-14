#pragma once

#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"
#include "types/type.hpp"
#include "types/class_type.hpp"
#include "types/util/naive_type_converter.hpp"
#include "ir/objects/ir_object.hpp"

/*
class LLVMUtil {
 public:
  LLVMUtil(llvm::LLVMContext* context, llvm::Module* module);

  llvm::Type* GetLLVMType(const SharedPtr<Type>& type);
  //const SharedPtr<Type>& GetJVCType(llvm::Type* type);

  //llvm::Value* CreateCast(llvm::Value* to, llvm::Value* from);

  void CreateStore(std::shared_ptr<IRObject> obj, llvm::Value* value);

  llvm::Value* CreateLoad(std::shared_ptr<IRObject> obj);

  llvm::Value* CreateCast(llvm::Value* value, llvm::Type* type);
  llvm::Value* CreateCast(llvm::Value* value, const SharedPtr<Type>& type);

  llvm::Type* GetCommonType(llvm::Type* lhs, llvm::Type* rhs);

  void CastToCommonType(llvm::Value* lhs, llvm::Value* rhs);

 private:
  llvm::LLVMContext* context;
  llvm::Module* module;

  NaiveTypeConverter type_converter;
};
*/