#include <iomanip>
#include <iostream>

#include "../lib/table.hpp"
#include "../util/populate_random_table.hpp"

#define NUM_ENTRIES_TO_POPULATE 100

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
    PopulateRandomTable::populate_random_table(
        table,NUM_ENTRIES_TO_POPULATE);

    return table.num_entries() == NUM_ENTRIES_TO_POPULATE;
}
