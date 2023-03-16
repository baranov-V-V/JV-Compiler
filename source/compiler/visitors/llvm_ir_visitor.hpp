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

#include <unordered_map>
#include <string>
#include <deque>

class LLVMIRVisitor : public Visitor, public VisitorHelper<llvm::Value*> {
 public:
  LLVMIRVisitor() = default;
  virtual ~LLVMIRVisitor() override = default;
    
  void TranslateToIR(Program* program);

  virtual void Visit(Program* program) override;
  virtual void Visit(MainClass* main_class) override;
  
  virtual void Visit(ClassDeclaration* class_declaration) override;
  virtual void Visit(ClassDeclarationList* class_declaration_list) override;
  virtual void Visit(DeclarationList* declaration_list) override;
  virtual void Visit(MethodDeclaration* method_declaration) override;
  virtual void Visit(VariableDeclaration* variable_declaration) override;
  
  virtual void Visit(BinOpExpression* expression) override;
  virtual void Visit(TrueExpression* expression) override;
  virtual void Visit(FalseExpression* expression) override;
  virtual void Visit(IdentifierExpression* expression) override;
  virtual void Visit(IntegerExpression* expression) override;
  virtual void Visit(NotExpression* expression) override;

  virtual void Visit(AssignmentStatement* statement) override;
  virtual void Visit(IfElseStatement* statement) override;
  virtual void Visit(IfStatement* statement) override;
  virtual void Visit(PrintStatement* statement) override;
  virtual void Visit(ReturnStatement* statement) override;
  virtual void Visit(WhileStatement* statement) override;
  virtual void Visit(StatementList* statement) override;
  virtual void Visit(LocalVariableStatement* statement) override;
  virtual void Visit(StatementListStatement* expression) override;
  
  virtual llvm::Value* Accept(AstNode* ast_node) override;

 private:
  SymbolTable<llvm::Value*> table;
  ProgramStack<llvm::Value*> stack;
  
  llvm::LLVMContext* context;
  llvm::IRBuilder<>* builder;
  llvm::Module* module;
  
  void InitializeLLVM(const std::string& module_name);
  void TerminateLLVM();
};