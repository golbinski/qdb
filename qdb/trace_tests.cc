/**
 * QDB
 */

#include <gtest/gtest.h>
#include "qdb/trace.h"

// mock print handler
namespace qdb
{

void PrintLog(const std::string& message)
{
    std::cout << message << std::endl;
}

}  // namespace qdb

namespace qdb
{
namespace testing
{

TEST(Random, succeed)
{
    QDB_TRACE << "Hello World!?";
    QDB_TRACE << "Next line of log! Awesome!";
}

}  // namespace testing
}  // namespace qdb
