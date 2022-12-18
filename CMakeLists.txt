cmake_minimum_required(VERSION 3.22)
project(fennecs)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(src)

add_subdirectory(tests)

add_subdirectory(third_party)