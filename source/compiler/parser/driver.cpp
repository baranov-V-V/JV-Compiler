#include "driver.hpp"

#include "compiler/visitors/interpreter.hpp"
#include "compiler/visitors/print_visitor.hpp"

#include "compiler/ast/program/program.hpp"

Driver::Driver() :
    trace_parsing(false),
    trace_scanning(false),
    scanner(*this), parser(scanner, *this) {
}

void Driver::SetProgram(Program* program) {
  program = program;
}

void Driver::Parse(std::string file) {
  location.initialize(&file);
  ScanBegin();
  parser.set_debug_level(trace_parsing);
  int res = parser();
  ScanEnd();
}

void Driver::ScanBegin() {
  if (file.empty()) {
    return;
  }
  scanner.set_debug(trace_scanning);
  stream.open(file);
  scanner.yyrestart(&stream);
}

void Driver::ScanEnd() {
  stream.close();
}

void Driver::PrintTree(const std::string& filename) const {
  if (program == nullptr) {
    return;
  }
}

int Driver::Run() const {
  return 0;
}

void Driver::SetTraceScan(bool trace) { trace_scanning = trace; }

void Driver::SetTraceParse(bool trace) {
  trace_parsing = trace;
}
