cmake_minimum_required(VERSION 2.12)
project(qdb)

add_compile_options(-Wall -Wextra -Werror -pedantic -pedantic-errors)
add_compile_options(-std=c++11)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
set(QDB_SOURCES
    qdb/trace.cc)

add_library(qdb ${QDB_SOURCES})
