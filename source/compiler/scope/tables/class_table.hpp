#pragma once

#include <map>
#include "types/class_type.hpp"
#include "ir/objects/class_info.hpp"

/**
 * @brief Holds most basic info about the classes, need to construct this to
 * find all methods and fields of all classes before type checking
 * 
 */
class ClassTable {
 public:
  ClassTable() = default;
  ClassTable(const ClassTable&) = delete;
  ClassTable(ClassTable&&) = default;

  void CreateClassInfo(SharedPtr<ClassType> type);

  [[nodiscard]] const ClassInfo& GetInfo(SharedPtr<ClassType> type) const;
  [[nodiscard]] ClassInfo& GetInfo(SharedPtr<ClassType> type);

  void AddMethod(SharedPtr<ClassType> type, const Symbol& symbol, SharedPtr<MethodType> method_type);
  void AddField(SharedPtr<ClassType> type, const Symbol& symbol, SharedPtr<Type> field);

 private:
  std::map<SharedPtr<ClassType>, ClassInfo> class_table;
};
