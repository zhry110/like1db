//
// Created by zhrys on 2021/11/19.
//

#include "RedoLog.h"

RedoLog::RedoLog(const path &data) : redo_log_path(data / "redo") {
  if (!std::filesystem::exists(redo_log_path)) {
    cout << "[Error] Redo file " << absolute(redo_log_path) << " " << "not exists,";
    cout << "Maybe you need init db first" << endl;
    std::terminate();
  }
  for (const auto &entry: filesystem::directory_iterator(redo_log_path)) {
    if (current_redo_log_name.empty()) {
      current_redo_log_name = entry.path();
    } else if (entry.path() > current_redo_log_name) {
      current_redo_log_name = entry.path();
    }
  }
  if (current_redo_log_name.empty()) {
    cout << "[Error]: redo log files is missing" << endl;
    std::terminate();
  }
  log_file_counter = stoll(current_redo_log_name.filename().c_str());
  assert(log_file_counter > 0);
  current_redo_log = open(current_redo_log_name.c_str(), O_RDWR | O_APPEND);
  assert(current_redo_log != -1);
}
void RedoLog::initialize(const filesystem::path &redo_log_path) {
  cout << "[Info]: Initialize redo files" << endl;
  if (filesystem::exists(redo_log_path)) {
    cout << "[Error]: Redo logs already exists" << endl;
    std::terminate();
  }
  filesystem::create_directories(redo_log_path);
  filesystem::path current_file_name = redo_log_path / new_redo_file_name(1);
  int redo_log = open((current_file_name).c_str(), O_CREAT | O_RDWR, S_IRWXU);
  assert(redo_log != -1);
  auto *header = new RedoFileHeader;
  header->free = sizeof(RedoFileHeader) + 88;
  ssize_t len = write(redo_log, header, sizeof(RedoFileHeader));
  assert(len == sizeof(RedoFileHeader));

  cout << "[Info]: Redo file " << current_file_name << " created" << endl;
  string a = "abcd";
  auto record = WritePageRecord::new_record(1, 1, 123, (byte *) a.c_str(), a.length());
  ssize_t wtn = write(redo_log, record, record->length());
  wtn = write(redo_log, record, record->length());
  cout << wtn << " bytes wrote" << endl;
  delete record;
  close(redo_log);
  filesystem::resize_file(current_file_name, RedoFileHeader::REDO_FILE_SIZE);
}
void RedoLog::checkpoint() {

}
void RedoLog::log(const RedoRecord &record) {
  ssize_t wtn = write(current_redo_log, &record, record.length());
  assert(record.length() == wtn);
}
void RedoLog::commit(lsn to) {

}
string RedoLog::new_redo_file_name(int no) {
  constexpr static size_t NAME_LENGTH = 21;
  string name = to_string(no);
  assert(name.length() <= NAME_LENGTH);
  while (name.length() < NAME_LENGTH) {
    name.insert(name.begin(), '0');
  }
  return name;
}
bool WritePageRecord::redo() {
  cout << "Write page " << page << " of Table " << table;
  cout << ", value length is " << len - sizeof(WritePageRecord) << endl;
  return false;
}
WritePageRecord *WritePageRecord::new_record(Tableno table_no,
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

RedoRecord *RedoRecordIterator::next() {
  if (total_scan == 0) {
    RedoFileHeader header;
    total_scan = sizeof(RedoFileHeader);
    if (lseek(redo_fd, 0, SEEK_SET) == -1 || read(redo_fd, &header, total_scan) != total_scan) {
      std::terminate();
    }
    end = header.free;
  } else if (total_scan == end) {
    return nullptr;
  } else if (eof) {
    cout << "[Error]: Unexpected end of file" << endl;
    std::terminate();
  }
  if (current_scan + sizeof(size_t) > buf_len) {
    read_next_page();
  }
  size_t record_len = *(size_t *) buf;
  if (record_len + current_scan > buf_len) {
    read_next_page();
  }
  auto record = (RedoRecord *) (buf + current_scan);
  current_scan += record_len;
  total_scan += record_len;
  return record;
}
void RedoRecordIterator::read_next_page() {
  if (lseek(redo_fd, (off_t) current_scan - (off_t) buf_len, SEEK_CUR) == -1) {
    terminate();
  }
  buf_len = ::read(redo_fd, buf, PAGE_SIZE);
  if (total_scan + buf_len >= end) {
    buf_len = (ssize_t) end - (ssize_t) total_scan;
  }
  if (buf_len == 0) {
    eof = true;
  }
  current_scan = 0;
}
