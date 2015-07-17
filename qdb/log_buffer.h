/**
 * QDB
 */

#ifndef QDB_LOG_BUFFER_H_
#define QDB_LOG_BUFFER_H_

#include <streambuf>
#include <functional>

namespace qdb
{

template <size_t Size>
struct LogBuffer
: std::streambuf
{
    using Flush = std::function<void()>;

    LogBuffer()
    {
        setp(buffer, buffer + Size);
    }

    void sink(Flush flush)
    {
        flush_ = flush;
    }

    void sink()
    {
        Flush().swap(flush_);
    }

    std::streamsize in_avail() const
    {
        return (pptr() - pbase());
    }

    const char* c_str() const
    {
        *pptr() = '\0';
        return pbase();
    }

    int_type overflow(int_type c = std::char_traits<char>::eof())
    {
        if ( flush_ )
        {
            flush_();
            sputc(c);
        }
        return c;
    }

    void reset()
    {
        pbump(pbase() - pptr());
    }

    char buffer[Size + 1];

private:
    Flush flush_;
};  //  struct LogBuffer

}  // namespace qdb

#endif  // QDB_LOG_BUFFER_H_
