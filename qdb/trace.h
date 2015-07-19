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
#include "qdb/print_log.h"
#include "qdb/log_buffer.h"

namespace qdb
{

class TraceMessage
{
public:
    TraceMessage(const std::string& filename, size_t line);
    ~TraceMessage();

    template <class Data>
    TraceMessage& operator<<(const Data& data);

private:
    using Buffer = qdb::LogBuffer<255>;

    std::string capture_log_line();

    const std::string   filename_;
    const size_t        line_;
    Buffer              buffer_;
    std::ostream        stream_;
};  // class TraceMessage


// Inline implementations.

inline
TraceMessage::~TraceMessage()
{
    qdb::PrintLog(capture_log_line());
}

template <class Data>
inline
TraceMessage& TraceMessage::operator<<(const Data& data)
{
    stream_ << data;
    return *this;
}


}  // namespace qdb

#endif  // QDB_TRACE_H_

