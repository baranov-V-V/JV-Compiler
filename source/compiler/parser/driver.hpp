#pragma once

#include <string>
#include <fstream>
#include <filesystem>

#include "scanner.hpp"
#include "parser.hpp"
#include "scope/tables/symbol_layer_tree.hpp"

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

  void PrintSymbolTree(const std::filesystem::path& filepath) const;

  void IrGen(const std::filesystem::path& filepath);

  void BuildLayerTree();

  void SetTraceScan(bool trace);

  void SetTraceParse(bool trace);

  yy::location GetLocation();

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

  std::unique_ptr<SymbolLayerTree> layer_tree;
};
