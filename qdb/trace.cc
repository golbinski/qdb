/**
 * QDB
 */

#if !defined(QDB_LOG_HANDLER)
#include <iostream>
#endif  // !defined(QDB_LOG_HANDLER)
#include <boost/format.hpp>
#include "qdb/trace.h"

namespace qdb
{
namespace
{

std::string ExtractFileName(const std::string& filename)
{
    const std::size_t pos = filename.find_last_of('/');
    if ( pos != std::string::npos )
    {
        return filename.substr(pos + 1);
    }
    else
    {
        return filename;
    }
}

#if !defined(QDB_LOG_HANDLER)
void log_message(const std::string& message)
{
    std::clog << message << std::endl;
}
#endif  // !defined(QDB_LOG_HANDLER)

}  // unnamed namespace

TraceMessage::TraceMessage(const std::string& filename, size_t line)
: filename_(ExtractFileName(filename))
, line_(line)
, buffer_()
, stream_(&buffer_)
{
}

TraceMessage::~TraceMessage()
{
    log_message(boost::str(boost::format("%s#%lu: %s")
        % filename_.c_str()
        % line_
        % buffer_.c_str()));
    buffer_.reset();
}


}  // namespace qdb
