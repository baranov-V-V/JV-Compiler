#include "compiler/core/logger.hpp"
#include "driver.hpp"

#include "compiler/visitors/interpreter.hpp"
#include "compiler/visitors/file_print_visitor.hpp"
#include "compiler/visitors/graph_print_visitor.hpp"
#include "compiler/visitors/llvm_ir_visitor.hpp"

#include "compiler/ast/program/program.hpp"
#include <cstdio>

Driver::Driver() : trace_parsing(false), trace_scanning(false), 
  scanner(*this), parser(scanner, *this), program(nullptr) {
}

Driver::~Driver() {
  delete program;
}

void Driver::SetProgram(Program* program) {
  this->program = program;
}

void Driver::DeleteProgram() {
  delete program;
}

void Driver::Parse(const std::filesystem::path& f) {
  file_in = f.native();
  location.initialize(&file_in);
  
  ScanBegin();
  parser.set_debug_level(trace_parsing);
  int res = parser();
  ScanEnd();
}

void Driver::ScanBegin() {
  scanner.set_debug(trace_scanning);
  if (file_in.empty()) {
    LOG_CRITICAL("No file in ScanBegin")
  } else {
    stream.open(file_in);
    scanner.yyrestart(&stream);
  }
}

void Driver::ScanEnd() {
  stream.close();
}

void Driver::PrintTreeTxt(const std::filesystem::path& filepath) const {
  if (program == nullptr) {
    LOG_CRITICAL("No program pointer in PrintTree")
    return;
  }
  FilePrintVisitor visitor;
  visitor.Print(filepath, program);
}

void Driver::PrintTreePng(const std::filesystem::path& filepath) const {
  if (program == nullptr) {
    LOG_CRITICAL("No program pointer in PrintTree")
    return;
  }
  GraphPrintVisitor visitor;
  visitor.Print(filepath, program);
}

void Driver::Run() const {
  Interpreter interpreter;
  interpreter.Run(program);
}

void Driver::IrGen(const std::filesystem::path& filepath) {
  LLVMIRVisitor visitor{};
  if (program == nullptr) {
    LOG_CRITICAL("No program pointer in IrGen")
    return;
  }
  visitor.TranslateToIR(program, filepath);
}

void Driver::SetTraceScan(bool trace) { trace_scanning = trace; }

void Driver::SetTraceParse(bool trace) {
  trace_parsing = trace;
}
