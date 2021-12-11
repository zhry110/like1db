//
// Created by zhrys on 2021/12/5.
//

#ifndef LIKE1DB_RECORD_FIELD_H_
#define LIKE1DB_RECORD_FIELD_H_
#include <unordered_map>
#include <string>
#include <utility>
#include <ostream>
class Field {
 public:
  enum Type {
    INT,
    LONG,
    VARCHAR,
    BLOB
  };
  static short TYPE_LENGTH[];
 private:
  Type type_;
  size_t length_;
  std::string name_;
  bool nullable_{true};
  std::byte *default_value_{nullptr};
 public:
  Field(std::string name, Type type, size_t length, bool nullable, std::byte *default_value) :
      name_(std::move(name)), type_(type) {
    if (type == BLOB || type == VARCHAR) this->length_ = length;
    else this->length_ = TYPE_LENGTH[type_];
  }
  Field(std::string name, Type type, size_t length) :
      Field(std::move(name), type, length, true, nullptr) {
  }
  [[nodiscard]] size_t length() const { return length_; }
  [[nodiscard]] const std::string &name() const { return name_; }
  [[nodiscard]] bool nullable() const { return nullable_; }
  [[nodiscard]] const std::byte *default_value() const { return default_value_; }
  [[nodiscard]] bool fixed_length() const { return type_ == INT || type_ == LONG; };
};
#endif //LIKE1DB_RECORD_FIELD_H_
