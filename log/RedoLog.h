//
// Created by zhrys on 2021/11/19.
//

#ifndef LIKE1DB_REDOLOG_H
#define LIKE1DB_REDOLOG_H
#include "common/common.h"
#include "page/page.h"
#include "RedoRecord.h"
#include "RedoRecScanner.h"
#include "RedoFileFormat.h"
#include <iostream>
#include <atomic>
#include <filesystem>
#include <fcntl.h>
#include <unistd.h>
using std::filesystem::path;
using namespace std;

class RedoLog {
 private:
  const path redo_log_path;
  fd current_redo_log{};
  path current_redo_log_name{};
  atomic<size_t> log_file_counter{1};

  atomic<lsn> current_lsn{};
  lsn start_lsn{0};
  lsn last_checkpoint{0};
 public:
  explicit RedoLog(const path &data);

  RedoLog(const RedoLog &redo_log) = delete;

  RedoLog &operator=(const RedoLog &redo_log) = delete;

  static void initialize(const path &redo_log_path);

  void checkpoint();

  void rotate();

  lsn log(const RedoRecord *record);

  void commit(lsn to);

  static string new_redo_file_name(int no);

  RedoRecScanner record_scanner() const {
    return {last_checkpoint, redo_log_path, log_file_counter, new_redo_file_name};
  }

  ~RedoLog() {
    close(current_redo_log);
  }
};

#endif //LIKE1DB_REDOLOG_H
