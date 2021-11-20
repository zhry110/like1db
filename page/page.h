//
// Created by zhrys on 2021/11/19.
//

#ifndef LIKE1DB_PAGE_PAGE_H_
#define LIKE1DB_PAGE_PAGE_H_
#include "common/common.h"

using PageType = uint16_t;
using Checksum = uint64_t[4];
using PageNo = uint64_t;
class Page {
 public:
  constexpr static size_t PAGE_SIZE = 16 * 1024;
  enum PageType {
    INDEX_BTREE
  };
 protected:
  /** common header */
  Checksum checksum;
  PageType type;
  PageNo next;
  PageNo prev;
};

#endif //LIKE1DB_PAGE_PAGE_H_
