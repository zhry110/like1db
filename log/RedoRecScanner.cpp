//
// Created by zhrys on 2021/11/24.
//

#include "RedoRecScanner.h"
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
using std::cout;

RedoRecord *FileRecScanner::next() {
  if (current_scan + sizeof(size_t) > buf_len) {
    read_next_page(sizeof(size_t));
    if (buf_len > 0 && buf_len < sizeof(size_t)) {
      cout << "[Error]: Redo file end with a incomplete record" << endl;
      std::terminate();
    } else if (buf_len == 0) {
      return nullptr;
    }
  }
  size_t record_len = *(size_t *) buf;
  if (record_len > PAGE_SIZE || record_len == 0) {
    cout << "[Error]: Bad redo record with length " << record_len << endl;
    std::terminate();
  }
  if (record_len + current_scan > buf_len) {
    read_next_page(record_len);
    if (buf_len < record_len) {
      cout << "[Error]: Redo file end, but record length is wrong";
      cout << ", [real, expected]=[" << buf_len << ", " << record_len << "]" << endl;
      std::terminate();
    }
  }
  auto record = (RedoRecord *) (buf + current_scan);
  current_scan += record_len;
  return record;
}
void FileRecScanner::read_next_page(size_t expected_len) {
  if (lseek(redo_fd, (off_t) current_scan - (off_t) buf_len, SEEK_CUR) == -1) {
    terminate();
  }
  ssize_t rdn = ::read(redo_fd, buf, PAGE_SIZE);
  if (rdn < 0) {
    std::terminate();
  }
  buf_len = rdn;
  current_scan = 0;
}
