//
// Created by zhrys on 2021/11/26.
//

#ifndef LIKE1DB_STORAGE_INDEX_BTREE_BTREE_H_
#define LIKE1DB_STORAGE_INDEX_BTREE_BTREE_H_

#include "common/common.h"
#include "page/page.h"
#include "record/Record.h"

class RecordScanner {
 private:
 public:
};

class Btree {
 private:
  Page::PageId root_id;
 public:
  explicit Btree(const Page::PageId &root_id);
  const std::tuple<Record *, bool> search_equals() {};
  RecordScanner search_greater() { return {}; };
};

#endif //LIKE1DB_STORAGE_INDEX_BTREE_BTREE_H_
