#pragma once

#include <cstdio>
#include <unistd.h>
#include <cstdlib>
#include <filesystem>

#include "gtest/gtest.h"

#include "util/output_buffer.hpp"

class TestCompiledProgram : public ::testing::Test {
 protected:
  void SetUp() override {
    stdout_bk = dup(fileno(stdout));
    pipe2(pipe_fd, 0);
    dup2(pipe_fd[1], fileno(stdout));

    test_path = std::filesystem::current_path().parent_path().parent_path().append("test").append("jv_programs");
    execute_string = "/" + std::filesystem::current_path().append("a").replace_extension("out").string();

    argv[0] = "compiling from test";
  }

  void TearDown() override {}

  void CompileProgram() {
    argv[1] = test_path.c_str();

    try {
      compiler.Compile(2, argv);
    } catch (const CompilationException& e) {
      FAIL() << "Compilation failed, abort";
    }
  }

  OutputBuffer ExecuteProgram() {
    system(execute_string.c_str());
    fflush(stdout);

    close(pipe_fd[1]);
    dup2(stdout_bk, fileno(stdout));

    OutputBuffer buffer;

    read(pipe_fd[0], buffer.Data(), OutputBuffer::buf_size - 1);

    //std::cerr << "got: " << buffer.Data();

    return buffer;
  }

  int stdout_bk;
  int pipe_fd[2];

  Compiler compiler;

  const char* argv[2];

  std::filesystem::path test_path;
  std::string execute_string;
};
