#include "../lib/header.hpp"

#include <iomanip>
#include <iostream>

/**
   @return true if check gets correct result.  false otherwise.
 */
bool check(
    const Header& potential_superset, const Header& potential_subset,
    bool is_superset);

int main(int argc, char**argv)
{
    
    {
        Header match_all("xxxxx");
        Header test_match_1("01010"); // should match
        Header test_match_2("11111"); // should match

        if ((!check(match_all,test_match_1,true)) ||
            (!check(match_all,test_match_2,true)))
        {
            std::cout<<"\nFailed\n";
            return -1;
        }
    }

    {
        Header testing_against("x1010");
        Header test_match_1("01010"); // should match
        Header test_match_2("11010"); // should match
        Header test_match_3("11111"); // should not match
        Header test_match_4("11011"); // should not match
        
        if ((!check(testing_against,test_match_1,true)) ||
            (!check(testing_against,test_match_2,true)) ||
            (!check(testing_against,test_match_2,false)) ||
            (!check(testing_against,test_match_2,false)))
        {
            std::cout<<"\nFailed\n";
            return -1;
        }
    }
    
    {
        Header testing_against("11010");
        Header test_match_1("01010"); // should not match
        Header test_match_2("11010"); // should match
        if ((!check(testing_against,test_match_1,true)) ||
            (!check(testing_against,test_match_2,true)))
        {
            std::cout<<"\nFailed\n";
            return -1;
        }
    }    

    std::cout<<"\nPassed\n";
    return 0;
}


bool check(
    const Header& potential_superset, const Header& potential_subset,
    bool is_superset)
{
    return is_superset == potential_subset.superset(potential_superset);
}
