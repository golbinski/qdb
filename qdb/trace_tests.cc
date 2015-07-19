/**
 * QDB
 */

#include <gtest/gtest.h>
#include "qdb/trace.h"

// mock print handler
namespace qdb
{
namespace testing
{
namespace
{

std::string* gBuffer = nullptr;

struct TmpBuffer
{
    std::string data;

    TmpBuffer()
    {
        gBuffer = &data;
    }

    ~TmpBuffer()
    {
        gBuffer = nullptr;
    }
};  // struct TmpBuffer

}  // unnamed namespace
}  // namespace testing
void PrintLog(const std::string& message)
{
    ASSERT_TRUE(::qdb::testing::gBuffer != nullptr);
    *::qdb::testing::gBuffer = message;
}

}  // namespace qdb

namespace qdb
{
namespace testing
{

struct TraceShould : ::testing::Test
{
    TmpBuffer buffer;
};  // test fixture TraceShould

bool HasSubstr(const std::string& str, const std::string& substr)
{
    return str.find(substr) != std::string::npos;
}

TEST_F(TraceShould, FlushMessageUsingPrintHandler)
{
    const std::string message{"example message"};
    QDB_TRACE << message;
    ASSERT_PRED2(HasSubstr, buffer.data, message);
}

}  // namespace testing
}  // namespace qdb
