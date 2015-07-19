cmake_minimum_required(VERSION 2.12)
project(qdb LANGUAGES CXX)

function(ADD_GTEST DIR)
    include(ExternalProject)
    ExternalProject_Add(GoogleTest
        PREFIX              ${DIR}
        SVN_REPOSITORY      http://googletest.googlecode.com/svn/tags/release-1.7.0
        BUILD_IN_SOURCE     1
        UPDATE_DISCONNECTED 1
        INSTALL_COMMAND     "")
    set(GTEST_INCLUDE_DIRS ${CMAKE_CURRENT_BINARY_DIR}/gtest/src/GoogleTest/include PARENT_SCOPE)
    set(GTEST_LIBRARY_DIRS ${CMAKE_CURRENT_BINARY_DIR}/gtest/src/GoogleTest PARENT_SCOPE)
endfunction()

add_compile_options(-Wall -Wextra -Werror -pedantic -pedantic-errors)
add_compile_options(-std=c++11)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
set(QDB_SOURCES
    qdb/trace.cc
    qdb/print_log.cc)

add_library(qdb ${QDB_SOURCES})

add_gtest(${CMAKE_CURRENT_BINARY_DIR}/gtest)
include_directories(${GTEST_INCLUDE_DIRS})
link_directories(${GTEST_LIBRARY_DIRS})

# testing

add_definitions(
    -DQDB_TRACE_ENABLED
    -DQDB_PRINT_LOG_HANDLER)

set(QDB_TESTS_SOURCES
    qdb/trace_tests.cc)
add_executable(qdb_tests ${QDB_SOURCES} ${QDB_TESTS_SOURCES})
target_link_libraries(qdb_tests
    gtest_main
    gtest
    pthread)

add_custom_target(tests
    COMMAND qdb_tests
    DEPENDS qdb_tests
    COMMENT "Executing tests...")
