#include <iostream>
#include <string>
#include <fstream>
#include "compiler/parser/driver.hpp"
#include "compiler/core/compiler.hpp"
#include <filesystem>

#include "fmt/os.h"

int main(int argc, char** argv) {
  /*
  Driver driver;
  std::string filename;
  bool need_print = false;

  for (int i = 1; i < argc; ++i) {
    if (argv[i] == std::string("-p") || argv[i] == std::string("--parse")) {
      driver.SetTraceParse(true);
    } else if (argv[i] == std::string("-s") || argv[i] == std::string("--scan")) {
      driver.SetTraceScan(true);
    } else if (argv[i] == std::string("-d") || argv[i] == std::string("--dump")) {
      need_print = true;
    } else {
      filename = argv[i];
    }
  }

  driver.Parse(filename);

  if (need_print) {
    std::filesystem::path file_path(filename);
    file_path.replace_extension(".dmp");
    driver.PrintTree(file_path.string());
  }
  
  driver.Run();
  */
  
  /*
  Compiler compiler;
  compiler.Compile(argc, argv);
  */

  /*
  std::filesystem::create_directories("lol/kek"); 
  fmt::ostream stream = fmt::output_file("lol/kek/test.txt");
  stream.print("test {}\n", 3);
  stream.print("more test {}\n", 42);
  stream.close();
  */

  return 0;
}