#pragma once

#include <exception>

 class CompilationException : public std::exception {
  public:
    CompilationException() = default;
   ~CompilationException() override = default;

   const char* what() const noexcept override;
 };
