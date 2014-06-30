#include "../lib/header.hpp"
#include "../lib/table.hpp"

#include <iomanip>
#include <iostream>

/**
Generates a table that has this form:

   Priority     Match 
------------------------
A   2000         10101
B   1999         10101
C   1998         11011
D   1997         1x111
E   1996         1x111
F   1995         10111
G   1994         11111
H   1993         11110
I   1992         xxxxx
J   1991         10111
K   1990         00000
L   1989         xxxxx
M   1988         000xx

Returns true if ends with table of this form:
   
   Priority     Match 
------------------------
A   2000         10101
C   1998         11011
D   1997         1x111
H   1993         11110
I   1992         xxxxx
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
            2000,Header("10101"));
    UniqueEntryPtr entry_ptr_a(entry_a);
    table.add_entry(entry_ptr_a);

    Entry* entry_b =
        new Entry(
            1999,Header("10101"));
    UniqueEntryPtr entry_ptr_b(entry_b);
    table.add_entry(entry_ptr_b);

    Entry* entry_c =
        new Entry(
            1998,Header("11011"));
    UniqueEntryPtr entry_ptr_c(entry_c);
    table.add_entry(entry_ptr_c);

    Entry* entry_d =
        new Entry(
            1997,Header("1x111"));
    UniqueEntryPtr entry_ptr_d(entry_d);
    table.add_entry(entry_ptr_d);

    Entry* entry_e =
        new Entry(
            1996,Header("1x111"));
    UniqueEntryPtr entry_ptr_e(entry_e);
    table.add_entry(entry_ptr_e);

    Entry* entry_f =
        new Entry(
            1995,Header("10111"));
    UniqueEntryPtr entry_ptr_f(entry_f);
    table.add_entry(entry_ptr_f);

    Entry* entry_g =
        new Entry(
            1994,Header("11111"));
    UniqueEntryPtr entry_ptr_g(entry_g);
    table.add_entry(entry_ptr_g);

    Entry* entry_h =
        new Entry(
            1993,Header("11110"));
    UniqueEntryPtr entry_ptr_h(entry_h);
    table.add_entry(entry_ptr_h);

    Entry* entry_i =
        new Entry(
            1992,Header("xxxxx"));
    UniqueEntryPtr entry_ptr_i(entry_i);
    table.add_entry(entry_ptr_i);

    Entry* entry_j =
        new Entry(
            1991,Header("10111"));
    UniqueEntryPtr entry_ptr_j(entry_j);
    table.add_entry(entry_ptr_j);

    Entry* entry_k =
        new Entry(
            1990,Header("00000"));
    UniqueEntryPtr entry_ptr_k(entry_k);
    table.add_entry(entry_ptr_k);

    Entry* entry_l =
        new Entry(
            1989,Header("xxxxx"));
    UniqueEntryPtr entry_ptr_l(entry_l);
    table.add_entry(entry_ptr_l);

    Entry* entry_m =
        new Entry(
            1988,Header("000xx"));
    UniqueEntryPtr entry_ptr_m(entry_m);
    table.add_entry(entry_ptr_m);

    // sorts by priority
    table.finalize();
    
    // get rid of all entries that overlap with existing entries.
    table.filter_eclipsed();

    // see docstring at top of func declaration.
    if (table.num_entries() == 5)
        return true;
    return false;
}
