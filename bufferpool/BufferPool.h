//
// Created by zhrys on 2021/11/26.
//

#ifndef LIKE1DB_BUFFERPOOL_BUFFERPOOL_H_
#define LIKE1DB_BUFFERPOOL_BUFFERPOOL_H_

#include "page/page.h"

class BufferPool {
 public:
  explicit BufferPool(size_t size) {}
  Page *read(Page::PageId id) {
    return nullptr;
  }
  Page *write(Page::PageId id) {
    return nullptr;
  }
  void release(Page *page) {};
};

#endif //LIKE1DB_BUFFERPOOL_BUFFERPOOL_H_
