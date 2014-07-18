#include <string>
#include <cassert>
#include <iostream>
#include <stdlib.h>
#include <vector>

#include "header.hpp"

Header::Header(std::string header_str)
 : _header_str(header_str),
   _has_wildcard(false)
{
    for(std::string::const_iterator iter = header_str.begin();
        iter != header_str.end(); ++iter)
    {
        if ((*iter) == MATCH_ANY_CHAR)
        {
            _has_wildcard = true;
            break;
        }
    }
}
Header::Header(int num_bits)
 : _header_str(""),
   _has_wildcard(false)
{
    for (int i = 0; i < num_bits; ++i)
    {
        int which_char = rand() % 3;
        switch (which_char)
        {
          case 0:
            _header_str += '1';
            break;
          case 1:
            _header_str += '0';
            break;
          case 2:
            _header_str += MATCH_ANY_CHAR;
            _has_wildcard = true;
            break;
          default:
            assert(false);
        }
    }
}

Header::~Header()
{}

bool Header::has_wildcard() const
{
    return _has_wildcard;
}

Header Header::split_header()
{
    if (! _has_wildcard)
        assert(false);

    // randomly split on some part of header
    std::vector<int> wildcard_positions;
    for (int i =0; i < _header_str.size(); ++i)
    {
        if (_header_str[i] == MATCH_ANY_CHAR)
            wildcard_positions.push_back(i);
    }

    // update _has_wildcard: splitting may have removed all wildcards
    _has_wildcard = wildcard_positions.size() > 1;
    
    // choose a random wildcard to split
    int wildcard_positions_index = rand() % wildcard_positions.size();
    int wildcard_index = wildcard_positions[wildcard_positions_index];
    _header_str[wildcard_index] = '0';

    std::string new_header = _header_str;
    new_header[wildcard_index] = '1';
    
    return Header(new_header);
}

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

void Header::merge_header(const Header& to_merge_with)
{
    // do not currently handle differently-sized headers.
    if (to_merge_with._header_str.size() != _header_str.size())
        assert(false);

    for (int i = 0; i < _header_str.size(); ++i)
    {
        char my_char = _header_str[i];
        // keep match any char
        if (my_char == MATCH_ANY_CHAR)
            continue;
        
        char their_char = to_merge_with._header_str[i];
        if (my_char != their_char)
            _header_str[i] = MATCH_ANY_CHAR;
    }
}
