//
// Created by zhrys on 2021/11/28.
//

#ifndef LIKE1DB_STORAGE_INDEX_INDEX_H_
#define LIKE1DB_STORAGE_INDEX_INDEX_H_
#include "common/common.h"

class Index {
 private:
  TableNo table_no;
  std::string name;
};

class BtreeIndex : public Index {

};

#endif //LIKE1DB_STORAGE_INDEX_INDEX_H_
