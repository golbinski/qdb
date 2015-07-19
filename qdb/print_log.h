/**
 * QDB
 */

#ifndef QDB_PRINT_LOG_H_
#define QDB_PRINT_LOG_H_

#include <string>

namespace qdb
{
namespace detail
{

void print_log_default(const std::string& message);

}  // namespace detail

#if defined(QDB_PRINT_LOG_HANDLER)
void PrintLog(const std::string& message);
#else  // defined(QDB_PRINT_LOG_HANDLER)
inline
void PrintLog(const std::string& message)
{
    detail::print_log_default(message);
}
#endif  // defined(QDB_PRINT_LOG_HANDLER)

}  // namespace qdb

#endif  // QDB_PRINT_LOG_H_

