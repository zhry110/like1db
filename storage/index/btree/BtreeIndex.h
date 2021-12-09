//
// Created by zhrys on 2021/11/26.
//

#ifndef LIKE1DB_STORAGE_INDEX_BTREE_BTREEINDEX_H_
#define LIKE1DB_STORAGE_INDEX_BTREE_BTREEINDEX_H_

#include "common/common.h"
#include "page/page.h"
#include "record/Record.h"
#include "storage/index/Index.h"
#include "Like1db.h"

class BtreeIndex : public Index {
 private:
  Page::PageId root_id;
 public:
  explicit BtreeIndex(const Page::PageId &root_id);
  RecordScanner *scanner(Order order, const Record &begin, bool with_begin) override;
};

#endif //LIKE1DB_STORAGE_INDEX_BTREE_BTREEINDEX_H_
