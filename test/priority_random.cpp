#include "../lib/header.hpp"
#include "../lib/table.hpp"

#include <iomanip>
#include <iostream>
#include <stdlib.h>
#include <time.h>

int main(int argc, char**argv)
{
    srand(time(NULL));
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

    for (int i = 0; i < 5; ++i)
        table.priority_random();
    table.debug_print_table();
    return 0;
}
