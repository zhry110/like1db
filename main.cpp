#include <iostream>
#include <log/RedoLog.h>
#include <string>

using namespace std;

class Like1db {
 private:
  RedoLog redo_log;
 public:
  explicit Like1db(const string &data_path) : redo_log(data_path) {
    cout << "like1db by like1" << endl;
  }

  void write() {
    redo_log.log(WritePageRecord());
  }

  void start() {
    redo_log.recovery();
  }
};

#include <fcntl.h>
#include <filesystem>
int main() {
  RedoLog::initialize("db/redo");
  Like1db db{"db"};
  db.start();
  return 0;
}
