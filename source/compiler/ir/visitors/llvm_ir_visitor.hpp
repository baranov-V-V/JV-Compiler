#pragma once

#include "visitors/visitor.hpp"
#include "util/program_stack.hpp"
#include "util/visitor_helper.hpp"

#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/LegacyPassManager.h" //new
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Transforms/InstCombine/InstCombine.h"
#include "llvm/Transforms/Scalar.h"
#include "llvm/Transforms/Scalar/GVN.h"
#include "llvm/Transforms/Utils.h"
#include "llvm-c/Core.h"
#include "scope/tables/symbol_layer_tree.hpp"
#include "types/util/naive_type_converter.hpp"

#include <unordered_map>
#include <string>
#include <filesystem>
#include <deque>

class LLVMIRVisitor : public Visitor, public VisitorHelper<llvm::Value*> {
 public:
  LLVMIRVisitor() = default;

  ~LLVMIRVisitor() override = default;

  void TranslateToIR(Program* program, std::unique_ptr<SymbolLayerTree> layer_tree, const std::filesystem::path& path);

  void Visit(Program* program) override;

  void Visit(MainClass* main_class) override;

  void Visit(ClassDeclaration* class_declaration) override;

  void Visit(ClassDeclarationList* class_declaration_list) override;

  void Visit(DeclarationList* declaration_list) override;

  void Visit(MethodDeclaration* method_declaration) override;

  void Visit(VariableDeclaration* declaration) override;

  void Visit(LogicOpExpression* expression) override;

  void Visit(CompareOpExpression* expression) override;

  void Visit(MathOpExpression* expression) override;

  void Visit(TrueExpression* expression) override;

  void Visit(FalseExpression* expression) override;

  void Visit(IdentifierExpression* expression) override;

  void Visit(IntegerExpression* expression) override;

  void Visit(NotExpression* expression) override;

  void Visit(AssignmentStatement* statement) override;

  void Visit(IfElseStatement* statement) override;

  void Visit(IfStatement* statement) override;

  void Visit(PrintStatement* statement) override;

  void Visit(ReturnStatement* statement) override;

  void Visit(WhileStatement* statement) override;

  void Visit(StatementList* statement) override;

  void Visit(LocalVariableStatement* statement) override;

  void Visit(StatementListStatement* expression) override;

  void Visit(FieldDeclaration* declaration) override;

  void Visit(ArrayIdxExpression* expression) override;

  void Visit(LengthExpression* expression) override;

  void Visit(MethodCallExpression* expression) override;

  void Visit(NewArrayExpression* expression) override;

  void Visit(NewClassExpression* expression) override;

  void Visit(ThisExpression* expression) override;

  void Visit(CommaExpressionList* program) override;

  void Visit(MethodCall* program) override;

  void Visit(AssertStatement* statement) override;

  void Visit(MethodCallStatement* statement) override;

  void Visit(ArrayLValue* statement) override;

  void Visit(FieldLValue* statement) override;

  void Visit(IdentifierLValue* statement) override;

  llvm::Value* Accept(AstNode* ast_node) override;

 private:
  void GenerateStandartLib();

  void GenerateClassesDecl();

  void GenerateMethodsDecl();

  std::string GenMethodName(SharedPtr<ClassType> class_type, SharedPtr<MethodType> method_type);
  std::string GenMethodName(SharedPtr<ClassType> class_type, const std::string& method_name);

  std::string GenArrayName(const SharedPtr<ArrayType>& array_type);

  void ScopeGoUp();

  void ScopeGoDown();

  llvm::Type* GetLLVMType(const SharedPtr<Type>& type);
  //const SharedPtr<Type>& GetJVCType(llvm::Type* type);
  //llvm::Value* CreateCast(llvm::Value* to, llvm::Value* from);

  void CreateStore(std::shared_ptr<IRObject> obj, llvm::Value* value);

  llvm::Value* CreateLoad(std::shared_ptr<IRObject> obj);

  llvm::Value* CreateCast(llvm::Value* value, llvm::Type* type);

  llvm::Value* CreateCast(llvm::Value* value, const SharedPtr<Type>& type);

  llvm::Type* GetCommonType(llvm::Type* lhs, llvm::Type* rhs);

  void CastToCommonType(llvm::Value** lhs, llvm::Value** rhs);

  std::unique_ptr<SymbolLayerTree> symbol_tree;
  SymbolLayerTree::Iterator current_scope;

  ProgramStack<llvm::Value*> stack;

  llvm::Value* current_this;

  llvm::LLVMContext* context;
  llvm::IRBuilder<>* builder;
  llvm::Module* module;
  llvm::legacy::FunctionPassManager* pass_manager;

  SharedPtr<ClassType> current_class;
  SharedPtr<MethodType> current_method;

  SharedPtr<ClassType> last_expr_class;

  void InitializeLLVM(const std::string& module_name);

  void TerminateLLVM();
};