cmake_minimum_required(VERSION 3.9)
project(shit)

set(CMAKE_CXX_STANDARD 11)

add_executable(shit main.cpp SignalFd.cpp SignalFd.h)