//
// Created by zhrys on 2021/11/19.
//

#ifndef LIKE1DB_COMMON_COMMON_H_
#define LIKE1DB_COMMON_COMMON_H_
#include <string>
using fd = int;
using lsn = size_t;
using Tableno = size_t;
using Pageno = size_t;

using PagePos = uint32_t;

constexpr static Tableno BAD_TABLE_NO = -1;
constexpr static Tableno BAD_PAGE_NO = -1;

#endif //LIKE1DB_COMMON_COMMON_H_
