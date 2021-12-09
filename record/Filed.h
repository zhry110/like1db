//
// Created by zhrys on 2021/12/5.
//

#ifndef LIKE1DB_RECORD_FILED_H_
#define LIKE1DB_RECORD_FILED_H_
#include <unordered_map>
#include <string>
#include <utility>
class Filed {
 public:
  enum Type {
    INT,
    LONG,
    VARCHAR,
    BLOB
  };
  static std::unordered_map<Type, short> TYPE_LENGTH;
 private:
  Type type_;
  size_t length_;
  std::string name_;
  bool nullable_{true};
  std::byte *default_value_{nullptr};
 public:
  Filed(std::string name, Type type, size_t length, bool nullable, std::byte *default_value) :
      name_(std::move(name)), type_(type) {
    if (type == BLOB || type == VARCHAR) this->length_ = length;
    else this->length_ = TYPE_LENGTH[type_];
  }
  Filed(std::string name, Type type, size_t length) :
      Filed(std::move(name), type, length, true, nullptr) {
  }
  [[nodiscard]] size_t length() const;
  [[nodiscard]] const std::string &name() const;
  [[nodiscard]] bool nullable() const;
  [[nodiscard]] const std::byte *default_value() const;
};

#endif //LIKE1DB_RECORD_FILED_H_
