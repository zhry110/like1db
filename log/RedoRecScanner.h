//
// Created by zhrys on 2021/11/24.
//

#ifndef LIKE1DB_LOG_REDORECSCANNER_H_
#define LIKE1DB_LOG_REDORECSCANNER_H_

#include "RedoRecord.h"
#include "RedoFileFormat.h"
#include <filesystem>
#include <vector>
#include <unistd.h>
#include <fcntl.h>

using std::filesystem::path;
using std::byte;

class FileRecScanner {
 public:
  constexpr static size_t PAGE_SIZE = 52;
 private:
  int redo_fd;

  byte *buf;
  size_t buf_len{0};
  FilePos current_scan{0};
  lsn start_lsn_{0};
 public:
  explicit FileRecScanner(const filesystem::path &redo_file) {
    redo_fd = open(redo_file.c_str(), O_RDWR);
    if (redo_fd == -1 || lseek(redo_fd, sizeof(RedoFileHeader), SEEK_SET) == -1) {
      std::terminate();
    }
    if (redo_fd < 0) {
      std::terminate();
    }
    buf = new byte[PAGE_SIZE];
  }
  ~FileRecScanner() {
    delete buf;
    close(redo_fd);
  }
  RedoRecord *next();
  void read_next_page(size_t expected_len);
  [[nodiscard]] lsn start_lsn() const { return start_lsn_; }
};

class RedoRecScanner {
 private:
  lsn last_checkout;
  vector<FileRecScanner *> file_scanners{};
  vector<FileRecScanner *>::iterator current_scanner;
 public:
  RedoRecScanner(lsn last_checkout, const filesystem::path &redo_path,
                 size_t file_no, const function<filesystem::path(size_t)> &file_name_func)
      : last_checkout(last_checkout) {
    while (true) {
      filesystem::path file_path = redo_path / file_name_func(file_no);
      if (!filesystem::exists(file_path)) {
        break;
      }
      auto file_rec_scanner = new FileRecScanner(file_path);
      file_scanners.insert(file_scanners.begin(), file_rec_scanner);
      if (file_rec_scanner->start_lsn() < last_checkout || file_no == 0) {
        break;
      }
      file_no -= 1;
    }
    current_scanner = file_scanners.begin();
  }

  RedoRecord *next() {
    while (current_scanner != file_scanners.end()) {
      auto record = (*current_scanner)->next();
      if (record == nullptr) {
        current_scanner++;
      } else {
        return record;
      }
    }
    return nullptr;
  }
};

#endif //LIKE1DB_LOG_REDORECSCANNER_H_
