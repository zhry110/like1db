//
// Created by zhrys on 2021/11/19.
//

#include "page.h"
Page::PageId::PageId(TableNo table_no, PageNo page_no) : table_no(table_no), page_no(page_no) {}
bool Page::PageId::operator==(const Page::PageId &rhs) const {
  return table_no == rhs.table_no && page_no == rhs.page_no;
}
bool Page::PageId::operator!=(const Page::PageId &rhs) const {
  return !(rhs == *this);
}
