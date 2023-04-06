#include "class_info.hpp"

ClassInfo::ClassInfo(std::initializer_list<SharedPtr<MethodType>> methods,
                     std::initializer_list<SharedPtr<Type>> fields) :
                     methods(methods), fields(fields) {

}

ClassInfo::ClassInfo(const std::vector<SharedPtr<MethodType>> &methods, const std::vector<SharedPtr<Type>> &fields) :
    methods(methods), fields(fields) {
}

const SharedPtr<MethodType> &ClassInfo::GetMethodType(int idx) const {
    return methods.at(idx);
}

int ClassInfo::GetMethodsNum() const {
    return methods.size();
}

void ClassInfo::AddMethodType(const SharedPtr<MethodType> &method_type) {
    methods.push_back(method_type);
}

const SharedPtr<Type> &ClassInfo::GetFieldType(int idx) const {
    return fields.at(idx);
}

int ClassInfo::GetFieldsNum() const {
    return fields.size();
}

void ClassInfo::AddFieldType(const SharedPtr<Type> &field_type) {
    fields.push_back(field_type);
}
