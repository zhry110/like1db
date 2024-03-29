//
// Created by zhrys on 2021/11/28.
//

#ifndef LIKE1DB_PAGE_RECORD_H_
#define LIKE1DB_PAGE_RECORD_H_
#include <vector>
#include <map>
#include "Field.h"

struct Value {
 private:
  const Field *field;
  std::byte *value;
 public:
  size_t len{0};
  bool null_value{true};
 public:
  explicit Value(const Field *filed) : field(filed) {
    value = static_cast<std::byte *>(malloc(field->length()));
    len = field->fixed_length() ? field->length() : 0;
  }
  template<class T>
  Value &operator=(T val) {
    if (field->length() < sizeof(val)) {
      // todo failed
    }
    *(T *) value = val;
    null_value = false;
    return *this;
  }
  Value &operator=(const std::string &str) {
    memcpy(value, str.c_str(), field->length());
    this->len = str.length();
    null_value = false;
    return *this;
  }
};

class Record {
 private:
  std::map<std::string, Value *> names{};
  std::vector<Value *> fields;

 public:
  explicit Record(const std::vector<const Field *> &fields) {
    if (fields.empty()) {
      std::terminate();
    }
    for (auto &field: fields) {
      auto value = new Value(field);
      names[field->name()] = value;
      this->fields.push_back(value);
    }
  }
  Value &operator[](size_t index);
  Value &operator[](const std::string &field_name);
  virtual ~Record();
};

#endif //LIKE1DB_PAGE_RECORD_H_
