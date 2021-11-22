//
// Created by zhrys on 2021/11/19.
//

#ifndef LIKE1DB_REDOLOG_H
#define LIKE1DB_REDOLOG_H
#include "common/common.h"
#include "page/page.h"
#include <iostream>
#include <atomic>
#include <filesystem>
#include <fcntl.h>
#include <unistd.h>
using std::filesystem::path;
using FilePos = uint64_t;
using namespace std;
struct RedoFileHeader {
  constexpr static lsn REDO_FILE_SIZE = 1 * 1024 * 1024 * 1024;
  Checksum checksum{0};
  FilePos free{sizeof(RedoFileHeader)};
  lsn last_checkpoint{0};
  lsn last_commit{0};
};

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
  Tableno table{BAD_TABLE_NO};
  Pageno page{BAD_PAGE_NO};
  PagePos pos{};
  byte data[0];
 public:
  WritePageRecord() : RedoRecord(WRITE_PAGE) {};

  bool redo();
  static WritePageRecord *new_record(Tableno table_no,
                                     PageNo page_no, PagePos pos,
                                     byte *buf, size_t len);
};

class RedoRecordIterator {
 public:
  constexpr static size_t PAGE_SIZE = 52;
 private:
  int redo_fd;
  FilePos end{0};
  FilePos total_scan{0};
  bool eof{false};

  byte *buf;
  size_t buf_len{0};
  FilePos current_scan{0};
 public:
  explicit RedoRecordIterator(int fd) : redo_fd(fd) {
    buf = new byte[PAGE_SIZE];
  }
  ~RedoRecordIterator() {
    delete buf;
  }
  RedoRecord *next();
  void read_next_page();
};

class RedoLog {
 private:
  const path redo_log_path;
  fd current_redo_log{};
  path current_redo_log_name{};
  atomic<size_t> log_file_counter{1};
 private:
  static string new_redo_file_name(int no);
 public:
  explicit RedoLog(const path &data);

  RedoLog(const RedoLog &redo_log) = delete;

  RedoLog &operator=(const RedoLog &redo_log) = delete;

  static void initialize(const path &redo_log_path);

  void checkpoint();

  void log(const RedoRecord &record);

  void commit(lsn to);

  RedoRecordIterator record_iterator() const {
    return RedoRecordIterator(current_redo_log);
  }

  ~RedoLog() {
    close(current_redo_log);
  }
};



#endif //LIKE1DB_REDOLOG_H
