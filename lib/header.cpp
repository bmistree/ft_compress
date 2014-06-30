#include "header.hpp"
#include <string>
#include <cassert>
#include <iostream>

Header::Header(std::string header_str)
 : _header_str(header_str)
{}
Header::~Header()
{}

bool Header::is_subset_of(const Header& h) const
{
    //Returns true if h is a superset of this.  False otherwise.
    if (h._header_str.size() != _header_str.size())
        assert(false);
    
    for (size_t i =0; i < h._header_str.size(); ++i)
    {
        char h_char = h._header_str[i];
        if (h_char == MATCH_ANY_CHAR)
            continue;

        char m_char = _header_str[i];
        if (m_char != h_char)
            return false;
    }
    return true;
}

const std::string& Header::header_str() const
{
    return _header_str;
}
