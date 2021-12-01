//
// Created by zhrys on 2021/11/19.
//

#ifndef LIKE1DB_COMMON_COMMON_H_
#define LIKE1DB_COMMON_COMMON_H_
#include <string>
using fd = int;
using lsn = size_t;
using TableNo = size_t;
using Pageno = size_t;

using PagePos = uint32_t;
using FilePos = uint64_t;

constexpr static TableNo BAD_TABLE_NO = -1;
constexpr static TableNo BAD_PAGE_NO = -1;

#endif //LIKE1DB_COMMON_COMMON_H_
