#pragma once

#include <map>
#include "types/class_type.hpp"
#include "ir/objects/class_info.hpp"

class ClassTable {
 public:
  ClassTable() = default;
  ClassTable(const ClassTable&) = delete;
  ClassTable(ClassTable&&) = default;

  void CreateClassInfo(SharedPtr<ClassType> type);

  [[nodiscard]] const ClassInfo& GetInfo(SharedPtr<ClassType> type) const;
  [[nodiscard]] ClassInfo& GetInfo(SharedPtr<ClassType> type);

  void AddMethod(SharedPtr<ClassType> type, SharedPtr<MethodType> method_type);
  void AddField(SharedPtr<ClassType> type, SharedPtr<Type> field);

 private:
  std::map<SharedPtr<ClassType>, ClassInfo> class_table;
};
