//
// Created by zhrys on 2021/11/26.
//

#include "BtreeIndex.h"
BtreeIndex::BtreeIndex(const Page::PageId &root_id) : root_id(root_id) {}
RecordScanner *BtreeIndex::scanner(Index::Order order, const Record &begin, bool with_begin) {
  Page *root = Like1db::instances()->buffer_pool()->read(root_id);

  return nullptr;
}

