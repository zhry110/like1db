//
// Created by zhrys on 2021/11/28.
//

#include "Record.h"
Record::~Record() {
}
Value &Record::operator[](size_t index) {
  return *fields[index];
}
Value &Record::operator[](const std::string &field_name) {
  return *this->names[field_name];
}
