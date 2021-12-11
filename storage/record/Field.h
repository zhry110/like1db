//
// Created by zhrys on 2021/12/5.
//

#ifndef LIKE1DB_RECORD_FIELD_H_
#define LIKE1DB_RECORD_FIELD_H_
#include <unordered_map>
#include <string>
#include <utility>
#include <ostream>
using std::string;
using std::byte;

class Field {
 public:
  enum Type {
    UNKNOWN,
    INT,
    LONG,
    VARCHAR,
    BLOB
  };
 protected:
  Type type_;
  size_t length_;
  std::string name_;
  bool nullable_{true};
  bool has_default_val_;
 public:
  Field(std::string name, Type type, size_t length, bool nullable, bool has_default_val)
      : length_(length), name_(std::move(name)), nullable_(nullable),
        type_(type), has_default_val_(has_default_val) {
  }
  [[nodiscard]] size_t length() const { return length_; }
  [[nodiscard]] const std::string &name() const { return name_; }
  [[nodiscard]] bool nullable() const { return nullable_; }
  [[nodiscard]] virtual const std::byte *default_value() const = 0;
  [[nodiscard]] virtual bool fixed_length() const = 0;
};

class IntField : public Field {
 private:
  int default_value_{};
 public:
  IntField(const string &name, bool nullable, bool has_default_val, int default_value)
      : Field(name, INT, sizeof(int), nullable, has_default_val) {
    default_value_ = default_value;
  }
  [[nodiscard]] const std::byte *default_value() const override {
    return reinterpret_cast<const byte *>(default_value_);
  }
  [[nodiscard]] bool fixed_length() const override {
    return true;
  }
};

class LongField : public Field {
 private:
  long long default_value_{};
 public:
  LongField(const string &name, bool nullable, bool has_default_val, long long default_value)
      : Field(name, LONG, sizeof(long long), nullable, has_default_val) {
    default_value_ = default_value;
  }
  [[nodiscard]] const std::byte *default_value() const override {
    return reinterpret_cast<const byte *>(default_value_);
  }
  [[nodiscard]] bool fixed_length() const override {
    return true;
  }
};

class VarcharField : public Field {
 private:
  char *default_value_{nullptr};
 public:
  VarcharField(const string &name, size_t length, bool nullable, bool has_default_val, byte *default_value)
      : Field(name, VARCHAR, length, nullable, has_default_val) {
    if (this->has_default_val_) {
      default_value_ = new char[length];
      memcpy(default_value_, default_value, length);
    }
  }
  [[nodiscard]] const std::byte *default_value() const override {
    return reinterpret_cast<const byte *>(default_value_);
  }
  [[nodiscard]] bool fixed_length() const override {
    return false;
  }
};
#endif //LIKE1DB_RECORD_FIELD_H_
