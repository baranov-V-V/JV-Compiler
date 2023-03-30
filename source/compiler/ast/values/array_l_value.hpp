#pragma once

#include "l_value.hpp"
#include "util/symbol.hpp"

class ArrayLValue : public LValue {
 public:
  ArrayLValue(const Symbol& identifier, Expression* idx);
  ~ArrayLValue() override;

  void Accept(Visitor* visitor) override;

  Symbol identifier;
  Expression* idx;
};
