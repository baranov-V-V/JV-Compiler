#include "compiler/core/logger.hpp"
#include "llvm_type_converter.hpp"

LLVMTypeConverter::LLVMTypeConverter(llvm::LLVMContext* context, llvm::Module* module) :
  context(context), module(module) {
}

llvm::Type* LLVMTypeConverter::GetLLVMType(const SharedPtr<Type>& type) {
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
