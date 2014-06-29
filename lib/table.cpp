#include "table.hpp"
#include <algorithm>

Table::Table()
{
    static TableId tid_generator = 0;
    _id = tid_generator ++;
}

Table::~Table()
{}

TableId Table::id() const
{
    return _id;
}

void Table::add_entry(UniqueEntryPtr entry_ptr)
{
    _entries.push_back(std::move(entry_ptr));
}

void Table::finalize()
{
    std::sort(_entries.begin(), _entries.end(),
        Entry::sort_unique_ptr_by_priority);
}
