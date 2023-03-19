#pragma once

#include <string>
#include <fstream>

#include "scanner.hpp"
#include "parser.hpp"

class Program;

class Driver {
 public:
  Driver();
  ~Driver();

  void SetProgram(Program* program);
  void DeleteProgram();

  void Parse(const std::string& f);
  
  void ScanBegin();
  void ScanEnd();

  void PrintTree(const std::string& filename) const;
  void Run() const;

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
