#ifndef __HEADER_HPP__
#define __HEADER_HPP__

#include <string>

/**
   Currently, tracking header contents with simple string.  String can only have
   1s, 0s, and xs.  xs mean "match any".
 */

class Header
{
public:
    Header(std::string header_str);
    ~Match();
    
private:
    std::string _header_str;
    
};

#endif
