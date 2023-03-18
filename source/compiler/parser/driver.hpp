#pragma once

#include <string>
#include <fstream>
#include <filesystem>

#include "scanner.hpp"
#include "parser.hpp"

class Program;

class Driver {
 public:
  Driver();
  ~Driver();

  void SetProgram(Program* program);
  void DeleteProgram();

  void Parse(const std::filesystem::path& f);
  
  void ScanBegin();
  void ScanEnd();

  void PrintTreeTxt(const std::filesystem::path& filepath) const;
  void PrintTreePng(const std::filesystem::path& filepath) const;
  
  void Run() const;
  void IrGen(const std::filesystem::path& filepath);

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
  
  std::string file_in;
};
