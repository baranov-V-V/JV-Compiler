#pragma once

#include <exception>
#include <string>

class RedeclarationException : public std::exception {
 public:
  RedeclarationException(const std::string& variable_info);
  virtual ~RedeclarationException() = default;

  virtual const char* what() const noexcept override;
  
 private:
  const std::string what_string;
};