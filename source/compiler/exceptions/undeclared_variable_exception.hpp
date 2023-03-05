#include <exception>
#include <string>

class UndeclaredVarException : public std::exception {
 public:
  UndeclaredVarException(const std::string& variable_info);
  virtual ~UndeclaredVarException() = default;
  virtual const char* what() const noexcept override;
  
 private:
  const std::string what_string;
};