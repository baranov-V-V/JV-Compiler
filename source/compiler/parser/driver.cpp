#include "driver.hpp"

#include "compiler/visitors/interpreter.hpp"
#include "compiler/visitors/file_print_visitor.hpp"

#include "compiler/ast/program/program.hpp"

Driver::Driver() : trace_parsing(false), trace_scanning(false), 
  scanner(*this), parser(scanner, *this) {
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

void Driver::Parse(const std::string& f) {
  file = f;
  location.initialize(&file);
  ScanBegin();
  parser.set_debug_level(trace_parsing);
  int res = parser();
  ScanEnd();
}

void Driver::ScanBegin() {
    scanner.set_debug(trace_scanning);
  if (file.empty () || file == "-") {
    std::cerr << "empty!" << std::endl;
  } else {
    stream.open(file);
    scanner.yyrestart(&stream);
  }
}

void Driver::ScanEnd() {
  stream.close();
}

void Driver::PrintTree(const std::string& filename) const {
  if (program == nullptr) {
    return;
  }
  FilePrintVisitor visitor;
  visitor.Print(filename, program);
}

void Driver::Run() const {
  Interpreter interpreter;
  interpreter.Run(program);
}

void Driver::SetTraceScan(bool trace) { trace_scanning = trace; }

void Driver::SetTraceParse(bool trace) {
  trace_parsing = trace;
}
