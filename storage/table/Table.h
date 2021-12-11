//
// Created by zhrys on 2021/12/11.
//

#ifndef LIKE1DB_STORAGE_TABLE_TABLE_H_
#define LIKE1DB_STORAGE_TABLE_TABLE_H_
#include <vector>
#include "storage/record/Field.h"
using std::vector;
class Table {
 private:
  vector<Field *> fields;
};

#endif //LIKE1DB_STORAGE_TABLE_TABLE_H_
