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
  current_redo_log = open(current_redo_log_name.c_str(), O_RDWR);
  assert(current_redo_log != -1);
  RedoFileHeader header;
  ssize_t rdn = read(current_redo_log, &header, sizeof(RedoFileHeader));
  assert(rdn == sizeof(RedoFileHeader));
  start_lsn = header.start_lsn;
  last_checkpoint = header.last_checkpoint;
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
  ssize_t len = write(redo_log, header, sizeof(RedoFileHeader));
  assert(len == sizeof(RedoFileHeader));

  cout << "[Info]: Redo file " << current_file_name << " created" << endl;
  string a = "abcd";
  auto record = WritePageRecord::new_record(1, 1, 123, (byte *) a.c_str(), a.length());
  //ssize_t wtn = write(redo_log, record, record->length());
  //wtn = write(redo_log, record, record->length());
  //cout << wtn << " bytes wrote" << endl;
  close(redo_log);

  RedoLog log("db");
  log.log(record);
  log.log(record);
  log.log(record);
  delete record;
}
void RedoLog::checkpoint() {

}
lsn RedoLog::log(const RedoRecord *record) {
  ssize_t wtn = write(current_redo_log, record, record->length());
  assert(record->length() == wtn);
  return current_lsn.fetch_add(record->length());
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
