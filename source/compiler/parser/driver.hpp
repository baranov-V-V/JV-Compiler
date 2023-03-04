#pragma once

#include <string>
#include <fstream>

#include "scanner.hpp"
#include "parser.hpp"

class Program;

class Driver {
 public:
  Driver();

  void SetProgram(Program* program);

  void Parse(std::string file);
  
  void ScanBegin();
  void ScanEnd();

  void PrintTree(const std::string& filename) const;
  int Run() const;

  void SetTraceScan(bool trace);
  void SetTraceParse(bool trace);

 private:
  friend class Scanner;
  Scanner scanner;
  yy::parser parser;

  Program* program;
  std::ifstream stream;

  bool trace_parsing;
  bool trace_scanning;
  yy::location location;
  
  std::string file;
};
