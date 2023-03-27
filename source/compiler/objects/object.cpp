//
// Created by viktor on 27.03.23.
//

#include "object.hpp"

Object::Object(Type type) : type(type) {}

Type Object::GetType() const {
  return this->type;
}
