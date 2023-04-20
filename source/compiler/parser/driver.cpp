#include "core/logger.hpp"
#include "core/error.hpp"

#include "driver.hpp"
#include "visitors/file_print_visitor.hpp"
#include "visitors/graph_print_visitor.hpp"

#include "ir/visitors/llvm_ir_visitor.hpp"
#include "ast/program/program.hpp"
#include "exceptions/compilation_exception.hpp"
#include "scope/visitors/symbol_table_visitor.hpp"

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
  LOG_DEBUG("parse file: {}", f.native())

  if (!std::filesystem::exists(f)) {
    COMPILER_ERROR("{}: No such file or directory\n", f.native())
  }

  this->file_in = f.native();
  location.initialize(&file_in);

  ScanBegin();
  parser.set_debug_level(trace_parsing);
  int res = parser();
  LOG_DEBUG("Parsed with code: {}", res);
  ScanEnd();

  if (program == nullptr) {
    LOG_CRITICAL("No program pointer after parsing")
  }
}

void Driver::ScanBegin() {
  scanner.set_debug(trace_scanning);

  stream.open(file_in);
  if (!stream.good()) {
    LOG_CRITICAL("stream is not good");
  }
  scanner.yyrestart(&stream);
}

void Driver::ScanEnd() {
  stream.close();
}

void Driver::PrintTreeTxt(const std::filesystem::path& filepath) const {
  FilePrintVisitor visitor;
  visitor.Print(filepath, program);
}

void Driver::PrintTreePng(const std::filesystem::path& filepath) const {
  if (program == nullptr) {
    LOG_CRITICAL("No program pointer in PrintTree")
  }
  GraphPrintVisitor visitor;
  visitor.Print(filepath, program);
}

void Driver::IrGen(const std::filesystem::path& filepath) {
  LLVMIRVisitor visitor;
  if (program == nullptr) {
    LOG_CRITICAL("No program pointer in IrGen")
  }
  visitor.TranslateToIR(program, std::move(layer_tree), filepath);
}

void Driver::SetTraceScan(bool trace) { trace_scanning = trace; }

void Driver::SetTraceParse(bool trace) {
  trace_parsing = trace;
}

void Driver::PrintSymbolTree(const std::filesystem::path& filepath) const {
  LOG_DEBUG("Start Print")
  layer_tree->DumpTree(filepath);
}

void Driver::BuildLayerTree() {
  SymbolTableVisitor visitor;

  layer_tree = visitor.ConstructSymbolTree(program);
}

yy::location Driver::GetLocation() {
  return location;
}
