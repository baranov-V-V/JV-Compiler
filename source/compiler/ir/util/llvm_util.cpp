#include "compiler/core/logger.hpp"
#include "llvm_util.hpp"
/*
LLVMUtil::LLVMUtil(llvm::LLVMContext* context, llvm::Module* module) :
  context(context), module(module) {}

llvm::Type* LLVMUtil::GetLLVMType(const SharedPtr<Type>& type) {
  if (type->IsClass()) {
    return module->getTypeByName(llvm::StringRef(
      std::reinterpret_pointer_cast<ClassType>(type)->GetName().name))->getPointerTo();
  } else {
    switch (type->GetTypeId()) {
      case Type::TypeID::VoidTy:
        return llvm::Type::getVoidTy(*context);

      case Type::TypeID::IntTy:
        return llvm::Type::getInt32Ty(*context);

      case Type::TypeID::BoolTy:
        return llvm::Type::getInt8Ty(*context);

      default:
        LOG_CRITICAL("Unreachable code with type {}", type->ToString());
    }
  }
}

void LLVMUtil::CreateStore(std::shared_ptr<IRObject> obj, llvm::Value* value) {

}

llvm::Value* LLVMUtil::CreateLoad(std::shared_ptr<IRObject> obj) {
  return nullptr;
}

llvm::Value* LLVMUtil::CreateCast(llvm::Value* value, llvm::Type* type) {
  if (value->getType()->getTypeID() == type->getTypeID()) {
    return value;
  }

  // return ;
}

llvm::Value* LLVMUtil::CreateCast(llvm::Value* value, const SharedPtr<Type>& type) {
  return nullptr;
}

llvm::Type* LLVMUtil::GetCommonType(llvm::Type* lhs, llvm::Type* rhs) {
  return nullptr;
}

void LLVMUtil::CastToCommonType(llvm::Value* lhs, llvm::Value* rhs) {

}
*/