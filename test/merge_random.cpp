#include "../lib/header.hpp"
#include "../lib/table.hpp"

#include <iomanip>
#include <iostream>

/**
Generates a table that has this form:

   Priority     Match 
------------------------
A   2000         1x111
B   1999         0xxx1
C   1998         xx011
D   1997         000xx

Splits into a table that has this form:
   
   Priority     Match 
------------------------
A1  2000         10111
A2  2000         11111
B1  1999         00001
B2  1999         00011
B3  1999         00101
B4  1999         00111
B5  1999         01001
B6  1999         01011
B7  1999         01101
B8  1999         01111
C1  1998         00011
C2  1998         01011
C3  1998         10011
C4  1998         11011
D1  1997         00000
D2  1997         00001
D3  1997         00010
D4  1997         00011

Then, tries to remerge tables.

 */
bool run();

int main(int argc, char**argv)
{
    if (run())
        std::cout<<"\n\nSUCCESS\n\n";
    else
        std::cout<<"\n\nFAILURE\n\n";
    
    return 0;
}

bool run()
{
    Table table;
    Entry* entry_a =
        new Entry(
            2000,Header("1x111"));
    UniqueEntryPtr entry_ptr_a(entry_a);
    table.add_entry(entry_ptr_a);

    Entry* entry_b =
        new Entry(
            1999,Header("0xxx1"));
    UniqueEntryPtr entry_ptr_b(entry_b);
    table.add_entry(entry_ptr_b);

    Entry* entry_c =
        new Entry(
            1998,Header("xx011"));
    UniqueEntryPtr entry_ptr_c(entry_c);
    table.add_entry(entry_ptr_c);

    Entry* entry_d =
        new Entry(
            1997,Header("000xx"));
    UniqueEntryPtr entry_ptr_d(entry_d);
    table.add_entry(entry_ptr_d);

    // sorts by priority
    table.finalize();

    bool should_split = true;
    // should not need this many iterations.  doing them as part of test.
    for (int i = 0; i < 100; ++i)
        table.split_random();
    
    // see docstring at top of func declaration.
    if (table.num_entries() != 18)
        return false;

    // now remerge
    for (int i = 0; i < 100; ++i)
        table.merge_random();

    if (table.num_entries() != 4)
        return false;
    
    return true;
}
