//
// Created by zhrys on 2021/12/5.
//

#include "Field.h"
short Field::TYPE_LENGTH[] = {4, 8, 8, 8};
std::ostream &operator<<(std::ostream &os, const Field &field) {
  os << "name_: " << field.name_;
  return os;
}

