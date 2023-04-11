#pragma once

#include "compiler/visitors/visitor.hpp"
#include "compiler/util/program_stack.hpp"
#include "compiler/util/symbol_table.hpp"
#include "compiler/util/visitor_helper.hpp"

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
#include "llvm-c/Core.h"
#include <unordered_map>
#include <string>
#include <filesystem>
#include <deque>

class LLVMIRVisitor : public Visitor, public VisitorHelper<llvm::Value*> {
 public:
  LLVMIRVisitor() = default;
  ~LLVMIRVisitor() override = default;

  void TranslateToIR(Program* program, const std::filesystem::path& path);

  void Visit(Program* program) override;
  void Visit(MainClass* main_class) override;

  void Visit(ClassDeclaration* class_declaration) override;
  void Visit(ClassDeclarationList* class_declaration_list) override;
  void Visit(DeclarationList* declaration_list) override;
  void Visit(MethodDeclaration* method_declaration) override;
  void Visit(VariableDeclaration* variable_declaration) override;

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
  void Visit(ArrayIdxExpression *expression) override;
  void Visit(LengthExpression *expression) override;
  void Visit(MethodCallExpression *expression) override;
  void Visit(NewArrayExpression *expression) override;
  void Visit(NewClassExpression *expression) override;
  void Visit(ThisExpression *expression) override;
  void Visit(CommaExpressionList *program) override;
  void Visit(MethodCall *program) override;
  void Visit(AssertStatement *statement) override;
  void Visit(MethodCallStatement *statement) override;
  void Visit(ArrayLValue *statement) override;
  void Visit(FieldLValue *statement) override;
  void Visit(IdentifierLValue *statement) override;

  llvm::Value* Accept(AstNode* ast_node) override;

 private:
  SymbolTable<std::string, llvm::Value*> table;

  ProgramStack<llvm::Value*> stack;

  llvm::LLVMContext* context;
  llvm::IRBuilder<>* builder;
  llvm::Module* module;

  void InitializeLLVM(const std::string& module_name);
  void TerminateLLVM();
};