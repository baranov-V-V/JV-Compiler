#include "array_l_value.hpp"

ArrayLValue::ArrayLValue(const Symbol& identifier, Expression* idx) : identifier(identifier), idx(idx) {}

void ArrayLValue::Accept(Visitor* visitor) {
  visitor->Visit(this);
}

ArrayLValue::~ArrayLValue() {
  delete idx;
}
