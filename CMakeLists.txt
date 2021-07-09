cmake_minimum_required(VERSION 3.19)
project(like1db)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
include_directories(log net coroutine)

add_executable(like1db main.cpp coroutine/CoroutineTask.cpp coroutine/CoroutineTask.h net/tcp_server.cpp net/tcp_server.h log/log.h)