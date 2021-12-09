//
// Created by zhrys on 2021/12/4.
//

#ifndef LIKE1DB__LIKE1DB_H_
#define LIKE1DB__LIKE1DB_H_
#include "log/RedoLog.h"
#include "bufferpool/BufferPool.h"
#include <iostream>
using namespace std;

class Like1db {
 private:
  RedoLog redo_log;
  BufferPool *buffer_pool_;
 public:
  explicit Like1db(const string &data_path) : redo_log(data_path) {
    cout << "like1db by like1" << endl;
    buffer_pool_ = new BufferPool(1024);
  }

  BufferPool *buffer_pool() { return buffer_pool_; }

  void write() {
  }

  void start() {
    recovery();
  }

  void recovery() const {
    cout << "[Info]: Start recovery..." << endl;
    auto iterator = redo_log.record_scanner();
    RedoRecord *record;
    size_t redo_count = 0;
    while ((record = iterator.next()) != nullptr) {
      ((WritePageRecord *) record)->redo();
      redo_count++;
    }
    cout << "[Info]: Recovery end, " << redo_count << " records replayed." << endl;
  }
  static Like1db *instances() {
    static auto db = new Like1db("");
    return db;
  }
  virtual ~Like1db() {
    delete buffer_pool_;
  }
};

#endif //LIKE1DB__LIKE1DB_H_
