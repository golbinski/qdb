/**
 * QDB
 */

#include <iostream>
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
    std::clog << filename_ << '#' << line_ << ": " << buffer_.c_str() << '\n';
    buffer_.reset();
}


}  // namespace qdb
