include(CheckIncludeFiles)

check_include_files("sys/event.h" HAVE_KQUEUE)
check_include_files("sys/epoll.h" HAVE_EPOLL)

add_library(tcp_server tcp_server.cpp)