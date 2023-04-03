#pragma once

#include "object.hpp"

class Float : public Object {
 public:
  explicit Float(float value);
  ~Float() override = default;

  [[nodiscard]] float GetValue() const;
  void SetValue(float value);

  [[nodiscard]] SharedPtr<Type> GetType() const override;
  [[nodiscard]] std::string ToString() const override;
  [[nodiscard]] bool Equals(const Object* obj) override;

 private:
  float value;
};
