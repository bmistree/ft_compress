#include "header.hpp"
#include <string>

Header::Header(std::string header_str)
 : _header_str(header_str)
{}
Header::~Header()
{}

const std::string& Header::header_str() const
{
    return _header_str;
}
