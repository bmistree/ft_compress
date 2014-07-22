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
    GeneralActionConstructionParameters action_params;
    action_params.num_ports = 64;

    
    Table table;
    PopulateRandomTable::populate_random_table(
        table,NUM_ENTRIES_TO_POPULATE,action_params);

    return table.num_entries() == NUM_ENTRIES_TO_POPULATE;
}
