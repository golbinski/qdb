/**
 * QDB
 */

#include <boost/format.hpp>
#include "qdb/trace.h"

namespace qdb
{
namespace
{

std::string extract_filename(const std::string& filename)
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

}  // unnamed namespace

TraceMessage::TraceMessage(const std::string& filename, size_t line)
: filename_(extract_filename(filename))
, line_(line)
, buffer_()
, stream_(&buffer_)
{
}

std::string TraceMessage::capture_log_line()
{
    const std::string log{ boost::str(boost::format("[trace] %s#%lu: %s")
        % filename_.c_str()
        % line_
        % buffer_.c_str()) };
    buffer_.reset();
    return log;
}

}  // namespace qdb
