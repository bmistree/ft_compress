#include "cost_functions.hpp"
#include "../lib/table.hpp"


float TableSizeCostFunction::cost (const TablePtrSet& table_set) const
{
    int total_num_entries = 0;
    for (TablePtrSet::const_iterator citer = table_set.begin();
         citer != table_set.end(); ++citer)
    {
        total_num_entries += (*citer)->num_entries();
    }
    return (float) total_num_entries;
};
