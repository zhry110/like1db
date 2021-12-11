//
// Created by zhrys on 2021/11/24.
//

#ifndef LIKE1DB_LOG_REDORECORD_H_
#define LIKE1DB_LOG_REDORECORD_H_
#include "common/common.h"
#include "page/page.h"

using namespace std;

class RedoRecord {
 public:
  enum Type : uint16_t {
    UNKNOWN = 1,
    WRITE_PAGE,
    CREATE_FILE,
    DELETE_FILE,
  };
 protected:
  size_t len{0};
  Type type;
 public:
  explicit RedoRecord(Type type) : type(type) {}
  [[nodiscard]] size_t length() const { return len; }
};

class WritePageRecord : public RedoRecord {
 private:
  TableId table{BAD_TABLE_NO};
  Pageno page{BAD_PAGE_NO};
  PagePos pos{};
  byte data[0];
 public:
  WritePageRecord() : RedoRecord(WRITE_PAGE) {};

  bool redo();
  static WritePageRecord *new_record(TableId table_no,
                                     PageNo page_no, PagePos pos,
                                     byte *buf, size_t len);
};

#endif //LIKE1DB_LOG_REDORECORD_H_
