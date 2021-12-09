//
// Created by zhrys on 2021/11/28.
//

#ifndef LIKE1DB_PAGE_RECORD_H_
#define LIKE1DB_PAGE_RECORD_H_
#include <vector>
#include <map>
#include "Filed.h"

struct Value {
  std::byte *value;
  Value &operator=(long long val) const {
    *(long long *) value = val;
  }
  Value &operator=(int val) const {
    *(int *) value = val;
  }
  Value &operator=(bool val) const {
    *(bool *) value = val;
  }
};

class Record {
 private:
  std::byte *data;
  int data_len;
  std::map<std::string, Value> values;

 public:
  explicit Record(const std::vector<Filed *> &fields) {
    if (fields.empty()) {
      std::terminate();
    }
    for (auto &filed: fields) {
      data_len += filed->length();
    }
    data = new std::byte[data_len];
  }
  void append(const Filed &filed, std::byte *data);
  void reset() { memset(data, data_len, sizeof(std::byte)); }
  virtual ~Record();
};

#endif //LIKE1DB_PAGE_RECORD_H_
