/**
 * QDB
 */

#ifndef QDB_TRACE_H_
#define QDB_TRACE_H_

/**
 * @brief QDB_TRACE is a debugging macro for extended the syslog with additional
 *        low-level trace messages.
 */
#if defined(QDB_TRACE_ENABLED)
# ifndef QDB_TRACE
#  define QDB_TRACE ::qdb::TraceMessage(__FILE__, __LINE__)
# endif  // QDB_TRACE
#else
# define QDB_TRACE while(0) *static_cast<std::ostream*>(nullptr)
#endif  // defined(QDB_TRACE_ENABLED)

#include <string>
#include <ostream>
#include "qdb/log_buffer.h"

namespace qdb
{

#if defined(QDB_LOG_HANDLER)
void log_message(const std::string& message);
#endif  // defined(QDB_LOG_HANDLER)

class TraceMessage
{
public:
    TraceMessage(const std::string& filename, size_t line);
    ~TraceMessage();

    template <class Data>
    TraceMessage& operator<<(const Data& data)
    {
        stream_ << data;
        return *this;
    }

private:
    using Buffer = qdb::LogBuffer<255>;

    const std::string   filename_;
    const size_t        line_;
    Buffer              buffer_;
    std::ostream        stream_;
};  // class TraceMessage

}  // namespace qdb

#endif  // QDB_TRACE_H_

