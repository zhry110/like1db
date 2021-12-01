//
// Created by zhrys on 2021/11/26.
//

#ifndef LIKE1DB_LOG_REDOFILEFORMAT_H_
#define LIKE1DB_LOG_REDOFILEFORMAT_H_
#include <page/page.h>
#include "common/common.h"

struct RedoFileHeader {
  constexpr static lsn REDO_FILE_SIZE = 1 * 1024 * 1024 * 1024;
  Checksum checksum{0};
  lsn start_lsn{0};
  lsn last_checkpoint{0};
};

#endif //LIKE1DB_LOG_REDOFILEFORMAT_H_
