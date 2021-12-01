//
// Created by zhrys on 2021/11/26.
//

#ifndef LIKE1DB_BUFFERPOOL_BUFFERPOOL_H_
#define LIKE1DB_BUFFERPOOL_BUFFERPOOL_H_

#include "page/page.h"

class BufferPool {
 public:
  BufferPool(size_t size) {}
  Page *load_for_read(TableNo t_no, Pageno p_no) {
    return nullptr;
  }
  Page *load_for_write(TableNo t_no, Pageno p_no) {
    return nullptr;
  }
  void release(Page *page) {};
};

#endif //LIKE1DB_BUFFERPOOL_BUFFERPOOL_H_
