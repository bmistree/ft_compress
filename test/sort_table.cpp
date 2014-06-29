#include "../lib/action.hpp"
#include "../lib/entry.hpp"
#include "../lib/header.hpp"
#include "../lib/table.hpp"

#include <stdlib.h>
#include <time.h>

int main(int argc, char**argv)
{
    srand(time(NULL));
    
    Header match("");
    Entry e(32,match);

    Table table;
    for (int i = 0; i < 100; ++i)
    {
        int priority = rand();
        Entry* entry =
            new Entry(
                priority,
                Header(""));
        UniqueEntryPtr entry_ptr(entry);
        table.add_entry(entry_ptr);
    }
    table.finalize();
    table.debug_print_table();
    return 0;
}
