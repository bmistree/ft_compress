#include "cost_functions.hpp"
#include "../lib/table.hpp"

TableSize::TableSize(const TablePtrSet& table_set)
 : _table_set(table_set)
{}


float TableSize::cost () const
{
    int total_num_entries = 0;
    for (TablePtrSet::const_iterator citer = _table_set.begin();
         citer != _table_set.end(); ++citer)
    {
        total_num_entries += (*citer)->num_entries();
    }
    return (float) total_num_entries;
};
