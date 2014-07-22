#include <iomanip>
#include <iostream>
#include <vector>

#include "../lib/table.hpp"
#include "../util/populate_random_table.hpp"
#include "../util/mcmc.hpp"

#define NUM_ENTRIES_TO_POPULATE 10000
#define NUM_HEADER_BITS 20
#define ACCEPTANCE_PARAMETER .5

int main(int argc, char**argv)
{
    SharedTablePtr table( new Table());
    PopulateRandomTable::populate_random_table(
        *table, NUM_ENTRIES_TO_POPULATE, NUM_HEADER_BITS);
    table->filter_eclipsed();
    TablePtrSet table_ptr_set;
    table_ptr_set.insert(table);
    
    TableSizeCostFunction tscf;
    TableSizeCandidateProducer tscp (table_ptr_set,tscf);
    MCMC<TablePtrSet> mcmc(tscp,ACCEPTANCE_PARAMETER);
        
    std::cout<<"\nInitial table size: "<<table->num_entries();
    for (int i = 0; i < 10000; ++i)
    {
        mcmc.iterate();
        std::cout<<"\n\tCurrent table size: "<<table->num_entries();
        if ((i % 10) == 0)
            std::cout.flush();
    }

    return 0;
}
