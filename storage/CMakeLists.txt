include_directories(../)
add_library(storage index/btree/BtreeIndex.cpp index/Index.cpp index/Index.h record/Record.cpp record/Field.cpp table/Table.cpp table/Table.h)