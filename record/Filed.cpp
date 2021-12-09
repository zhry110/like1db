//
// Created by zhrys on 2021/12/5.
//

#include "Filed.h"
std::unordered_map<Filed::Type, short> Filed::TYPE_LENGTH{{INT, 4}, {LONG, 8}};

size_t Filed::length() const {
  return length_;
}
const std::string &Filed::name() const {
  return name_;
}
bool Filed::nullable() const {
  return nullable_;
}
const std::byte *Filed::default_value() const {
  return default_value_;
}
