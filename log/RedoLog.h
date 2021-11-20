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
 private:
  enum Type : uint16_t {
    UNKNOWN = 1,
    WRITE_PAGE,
    CREATE_FILE,
    DELETE_FILE,
  };
  Type type{};
 public:
  virtual bool redo() = 0;
  virtual size_t length() const = 0;
};

class WritePageRecord : public RedoRecord {
 private:
  Tableno table{BAD_TABLE_NO};
  Pageno page{BAD_PAGE_NO};
  PagePos pos{0};
  size_t len{0};
  byte data[0];
 public:
  WritePageRecord(Tableno table, Pageno page, PagePos pos, size_t len, byte *data);
  bool redo() override;
  [[nodiscard]] size_t length() const override {
    return sizeof(WritePageRecord);
  }
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

  void recovery();

  void checkpoint();

  void log(const RedoRecord &record);

  void commit(lsn to);

  ~RedoLog() {
    close(current_redo_log);
  }
};

#endif //LIKE1DB_REDOLOG_H
