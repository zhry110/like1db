include_directories(../page ../common)
add_library(redo RedoLog.cpp RedoRecord.cpp RedoRecScanner.cpp RedoRecScanner.h RedoFileFormat.cpp RedoFileFormat.h)