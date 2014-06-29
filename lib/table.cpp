#include "table.hpp"
#include <algorithm>
#include <iostream>
#include <iomanip>


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

void Table::chain_tables(SharedTablePtr parent, SharedTablePtr child)
{
    parent->_children.insert(child);
    child->_parent = parent;
}

void Table::debug_print_table() const
{
    std::cout<<"\nPrinting table "<< _id<<"\n";
    for (EntryVecCIter citer = _entries.begin(); citer != _entries.end();
         ++citer)
    {
        (*citer)->debug_print_entry();
        std::cout<<"\n";
    }
}

void Table::add_entry(UniqueEntryPtr& entry_ptr)
{
    _entries.push_back(std::move(entry_ptr));
}

void Table::finalize()
{
    std::sort(_entries.begin(), _entries.end(),
        Entry::sort_unique_ptr_by_priority);
}
