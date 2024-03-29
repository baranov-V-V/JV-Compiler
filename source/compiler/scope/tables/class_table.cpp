#include "compiler/core/logger.hpp"
#include "class_table.hpp"

void ClassTable::CreateClassInfo(SharedPtr<ClassType> type) {
  if (class_table.contains(type)) {
    LOG_CRITICAL("already has \"{}\" class", type->ToString());
  }
  class_table.emplace(type, ClassInfo());
}

const ClassInfo& ClassTable::GetInfo(SharedPtr<ClassType> type) const {
  return class_table.at(type);
}

ClassInfo& ClassTable::GetInfo(SharedPtr<ClassType> type) {
  return class_table.at(type);
}

void ClassTable::AddMethod(SharedPtr<ClassType> type, const Symbol& symbol, SharedPtr<MethodType> method_type) {
  ClassTable::GetInfo(type).AddMethodType(symbol, method_type);
}

void ClassTable::AddField(SharedPtr<ClassType> type, const Symbol& symbol, SharedPtr<Type> field) {
  ClassTable::GetInfo(type).AddFieldType(symbol, field);
}

bool ClassTable::HasInfo(SharedPtr<ClassType> type) const {
  return class_table.contains(type);
}

const std::unordered_map<SharedPtr<ClassType>, ClassInfo, ClassTable::ClassTypeHash, ClassTable::ClassTypeEq>& ClassTable::GetAllInfo() const {
  return class_table;
}

ClassTable::ClassTable(ClassTable&& table) noexcept : class_table(std::move(table.class_table)) {

}
