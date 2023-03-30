#pragma once

#include "l_value.hpp"
#include "util/symbol.hpp"

class IdentifierLValue : public LValue {
 public:
  explicit IdentifierLValue(const Symbol& name);
  ~IdentifierLValue() override = default;

  void Accept(Visitor* visitor) override;

  Symbol name;
};
