/**
 * QDB
 */

#include <chrono>
#include <iomanip>
#include <iostream>
#include "qdb/print_log.h"

namespace qdb
{
namespace detail
{
namespace
{

std::time_t timestamp()
{
    return std::chrono::system_clock::to_time_t(
        std::chrono::system_clock::now());
}

}  // unnamed namespace

void print_log_default(const std::string& message)
{
    std::time_t now = timestamp();
    std::clog << '<' << std::put_time(std::localtime(&now), "%F %T") << '>'
        << ' ' << message << std::endl;
}

}  // namespace detail
}  // namespace qdb
