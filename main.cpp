#include <iostream>
#include <log/RedoLog.h>
#include "bufferpool/BufferPool.h"
#include <string>

using namespace std;

class Like1db {
 private:
  RedoLog redo_log;
  BufferPool buffer_pool{1024};
 public:
  explicit Like1db(const string &data_path) : redo_log(data_path) {
    cout << "like1db by like1" << endl;
  }

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
};

int main() {
  //RedoLog::initialize("db/redo");
  Like1db db{"db"};
  db.start();
  return 0;
}
