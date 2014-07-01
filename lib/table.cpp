#include <algorithm>
#include <iostream>
#include <iomanip>
#include <map>
#include <cassert>
#include <stdlib.h>

#include "table.hpp"

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

bool Table::split_random()
{
    // Grab random wildcard rule

    // first, find all wildcard rules
    std::vector<int> wildcard_rule_indices;
    for (int i = 0; i < _entries.size(); ++i)
    {
        const Header& header = _entries[i]->match();
        if (header.has_wildcard())
            wildcard_rule_indices.push_back(i);
    }

    if (wildcard_rule_indices.empty())
        return false;
    
    int wildcard_rule_indices_index = rand() % wildcard_rule_indices.size();
    int wildcard_rule_index =
        wildcard_rule_indices[wildcard_rule_indices_index];

    // Split the wildcard rule and insert new entry for split.
    UniqueEntryPtr new_entry = _entries[wildcard_rule_index]->split_entry();
    // FIXME: this is gross, but can't figure out how to insert unique pointers.
    //_entries.insert(wildcard_rule_index,std::move(new_entry));
    _entries.push_back(std::move(new_entry));
    finalize();
    return true;
}

bool Table::merge_random()
{
    // FIXME: ugly n^2 algorithm for merging entries
    std::vector<std::pair<int,int>> merge_indices;

    for (int i=0; i < _entries.size(); ++i)
    {
        const UniqueEntryPtr& entry_i = _entries[i];
        for (int j=i+1; j < _entries.size(); ++j)
        {
            const UniqueEntryPtr& entry_j = _entries[j];
            if (entry_i->can_merge(entry_j))
                merge_indices.push_back(std::pair<int,int>(i,j));
        }
    }

    // no entries to merge
    if (merge_indices.empty())
        return false;

    // choose random entry to merge
    int rand_merge_indices_index = rand() % merge_indices.size();
    // note: not necessary that this pair is const.  Just adding const because
    // don't modify entry at all.
    const std::pair<int,int>& entries_to_merge =
        merge_indices[rand_merge_indices_index];

    UniqueEntryPtr& to_merge_into = _entries[entries_to_merge.first];
    UniqueEntryPtr& to_merge = _entries[entries_to_merge.second];

    // update entry that's been merged
    to_merge_into->merge_into_me(to_merge);
    // remove old entry
    _entries.erase(_entries.begin() + entries_to_merge.second);

    // return that we actually performed the merge successfully.
    return true;
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
