#include "table.hpp"
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <map>
#include <cassert>

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

int Table::num_entries() const
{
    return _entries.size();
}

void Table::filter_eclipsed()
{
    // FIXME: very inefficient algorithm for removing.

    // keys are indices to remove from, values are garbage.  exploiting fact
    // that map stores keys in order
    std::map<int,bool> index_to_remove_from;

    for (int i = 0; i < _entries.size(); ++i)
    {
        const UniqueEntryPtr& i_entry = _entries[i];
        for(int j = i+1; j != _entries.size();++j)
        {
            const UniqueEntryPtr& j_entry = _entries[j];
            if (j_entry->match().is_subset_of(i_entry->match()))
                index_to_remove_from[j] = true;
        }
    }

    // iterating over backwards so that remove entries backwards to forwards in
    // entries.  That way, do not have to readjust removal indices.
    for (std::map<int,bool>::reverse_iterator riter = index_to_remove_from.rbegin();
         riter != index_to_remove_from.rend(); ++riter)
    {
        int index_to_remove = riter->first;
        _entries.erase( _entries.begin() + index_to_remove);
    }
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
        Entry::sort_unique_ptr_by_priority_descending);
}
