#ifndef __HEADER_HPP__
#define __HEADER_HPP__

#include <string>

#define MATCH_ANY_CHAR 'x'

/**
   Currently, tracking header contents with simple string.  String can only have
   1s, 0s, and xs.  xs mean "match any".
 */

class Header
{
public:
    Header(std::string header_str);
    ~Header();
    const std::string& header_str() const;
    bool has_wildcard() const;
    
    /**
       @returns Returns true if h is a superset of this.  False otherwise.
     */
    bool is_subset_of(const Header& h) const;

    /**
       Can only be called on a header that has a wildcard.
       
       @returns Returns a header that returns half the match header of this
       header.  Also, modifies this header to take the other half of the match.
     */
    Header split_header();
    
private:
    std::string _header_str;
    bool _has_wildcard;
};

#endif
