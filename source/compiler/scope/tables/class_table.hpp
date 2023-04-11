#pragma once

#include <map>
#include "types/class_type.hpp"
#include "types/util/class_info.hpp"

class ClassTable {
 public:
  ClassTable() = default;
  ClassTable(const ClassTable&) = delete;
  ClassTable(ClassTable&&) = default;

  void CreateClassInfo(SharedPtr<ClassType> type);

  [[nodiscard]] const ClassInfo& GetInfo(SharedPtr<ClassType> type) const;
  [[nodiscard]] ClassInfo& GetInfo(SharedPtr<ClassType> type);

  [[nodiscard]] bool HasInfo(SharedPtr<ClassType> type) const;

  void AddMethod(SharedPtr<ClassType> type, const Symbol& symbol, SharedPtr<MethodType> method_type);
  void AddField(SharedPtr<ClassType> type, const Symbol& symbol, SharedPtr<Type> field);

 private:
  /*
  struct ClassComp : public std::binary_function<SharedPtr<ClassType>, SharedPtr<ClassType>, bool> {
    bool operator()(const SharedPtr<ClassType>& lhs, const SharedPtr<ClassType>& rhs) const {
      return *lhs.get() < *rhs.get();
    }
  };
  */

  std::unordered_map<SharedPtr<ClassType>, ClassInfo, ClassTypeHash, ClassTypeEq> class_table;
};
