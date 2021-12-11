//
// Created by zhrys on 2021/11/28.
//

#ifndef LIKE1DB_STORAGE_INDEX_INDEX_H_
#define LIKE1DB_STORAGE_INDEX_INDEX_H_
#include "common/common.h"
#include "record/Record.h"
class RecordScanner {
 public:
  virtual Record *next() = 0;
};
class Index {
 private:
  TableId table_no;
  std::string name;
 public:
  enum Order {
    ASC,
    DESC
  };
 public:
  virtual RecordScanner *scanner(Order order, const Record &begin, bool with_begin) = 0;
};


#endif //LIKE1DB_STORAGE_INDEX_INDEX_H_
