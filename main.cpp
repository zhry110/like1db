#include <iostream>
#include <log/RedoLog.h>
#include "Like1db.h"
#include <string>

int main() {
  //RedoLog::initialize("db/redo");
  Like1db db{"db"};
  db.start();
  return 0;
}
