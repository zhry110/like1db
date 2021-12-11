//
// Created by zhrys on 2021/11/24.
//

#include <page.h>
#include "RedoRecord.h"
#include <iostream>
using std::cout;

bool WritePageRecord::redo() {
  cout << "Write page " << page << " of Table " << table;
  cout << ", value length is " << len - sizeof(WritePageRecord) << endl;
  return false;
}

WritePageRecord *WritePageRecord::new_record(TableId table_no,
                                             PageNo page_no, PagePos pos,
                                             byte *buf, size_t len) {
  auto mem = new byte[len + sizeof(WritePageRecord)];
  auto record = new(mem) WritePageRecord;
  record->table = table_no;
  record->page = page_no;
  record->len = len + sizeof(WritePageRecord);
  record->pos = pos;
  byte *data = reinterpret_cast<byte *>(record + 1);
  memcpy(data, buf, len);
  return record;
}
