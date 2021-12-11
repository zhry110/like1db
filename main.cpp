#include <iostream>
#include <log/RedoLog.h>
#include "Like1db.h"
#include <string>

#include "storage/record/Record.h"

int main() {
  //RedoLog::initialize("db/redo");
  Like1db db{"db"};
  db.start();
  std::vector<const Field *> fields;
  fields.push_back(new IntField("a", true, true, 4));
  Record record(fields);
  record[0] = 5;
  record["a"] = 6;
  return 0;
}
