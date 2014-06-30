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

    /**
       @returns Returns true if h is a superset of this.  False otherwise.
     */
    bool superset(const Header& h) const;
    
private:
    std::string _header_str;
};

#endif
