#include <iostream>
#include <string>
#include <fstream>
#include "compiler/parser/driver.hpp"
#include <filesystem>

int main(int argc, char** argv) {
  Driver driver;
  std::string filename = "../test1.jv";

  for (int i = 1; i < argc; ++i) {
    if (argv[i] == std::string("-p")) {
      driver.SetTraceParse(true);
    } else if (argv[i] == std::string("-s")) {
      driver.SetTraceScan(true);
    } else {
      filename = argv[i];
    }
  }

  driver.Parse(filename);
  driver.Run();
  
  return 0;
}