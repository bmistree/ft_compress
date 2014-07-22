#include <algorithm>
#include <iostream>
#include <iomanip>
#include <map>
#include <cassert>
#include <stdlib.h>

#include "table.hpp"
#include "perturbation_undoer.hpp"

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

void Table::perturb()
{
    // FIXME: this is a gross way of selecting perturbation to perform
    int which_perturb = rand() % 3;
    switch (which_perturb)
    {
      case 0:
        split_random();
        break;
      case 1:
        priority_random();
        break;
      case 2:
        merge_random();
        break;
      default:
        assert (false);
    }
}

void Table::undo_last_perturbation()
{
    // should already have perturbed before entering.
    if (! _last_perturbation_undoer)
        assert(false);

    _last_perturbation_undoer->undo();
    // resets pointer to undoer.
    _last_perturbation_undoer.reset(nullptr);
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

            if (! j_entry)
            {
                std::cout<<"\nFor some reason have invalid entry\n";
                assert(false);
            }
            
            
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
    {
        // do no op on undo
        _last_perturbation_undoer.reset(new EmptyUndoer());
        return false;
    }
    
    int wildcard_rule_indices_index = rand() % wildcard_rule_indices.size();
    int wildcard_rule_index =
        wildcard_rule_indices[wildcard_rule_indices_index];

    // Split the wildcard rule and insert new entry for split.
    UniqueEntryPtr new_entry = _entries[wildcard_rule_index]->split_entry();
    _entries.insert(
        _entries.begin() + wildcard_rule_index,
        std::move(new_entry));
    
    _last_perturbation_undoer.reset(
        new SplitRandomUndoer(_entries,wildcard_rule_index));
    
    return true;
}

void Table::update_priority_up(int index_to_update)
{
    const UniqueEntryPtr& to_update = _entries[index_to_update];
    
    if (index_to_update == (_entries.size() -1))
    {
        // do not need to re-sort _entries vec: modifying last entry won't
        // affect order
        int current_priority = to_update->priority();
        to_update->priority(current_priority + 1);
        return;
    }
        
    int can_update_until_priority = -1;
    for (int i = index_to_update+1; i<_entries.size(); ++i)
    {
        const UniqueEntryPtr& comparing = _entries[i];
        if (to_update->match().is_subset_of(comparing->match()))
        {
            can_update_until_priority = comparing->priority();
            break;
        }
    }

    if (can_update_until_priority != -1)
    {
        int to_update_priority = to_update->priority();
        int priority_delta = can_update_until_priority - to_update_priority;
        int new_priority = to_update_priority + ( rand() % priority_delta);
        to_update->priority(new_priority);        
    }

    // FIXME: re-sorting all instead of just moving one entry.
    finalize();
}

void Table::update_priority_down(int index_to_update)
{
    const UniqueEntryPtr& to_update = _entries[index_to_update];
    
    if (index_to_update == 0)
    {
        // do not need to re-sort _entries vec: modifying first entry won't
        // affect order
        int current_priority = to_update->priority();
        to_update->priority(current_priority - 1);
        return;
    }

    int can_update_until_priority = -1;
    for (int i = index_to_update-1; i>=0; --i)
    {
        const UniqueEntryPtr& comparing = _entries[i];
        if (to_update->match().is_subset_of(comparing->match()))
        {
            can_update_until_priority = comparing->priority();
            break;
        }
    }
    
    if (can_update_until_priority != -1)
    {
        int to_update_priority = to_update->priority();
        int priority_delta = to_update_priority - can_update_until_priority;
        int new_priority = to_update_priority - ( rand() % priority_delta);
        to_update->priority(new_priority);        
    }

    // FIXME: re-sorting all instead of just moving one entry.
    finalize();
}


bool Table::priority_random()
{
    if (_entries.empty())
        return false;
    int entry_to_update_index = rand() % _entries.size();
    bool update_priority_up_b = ((rand() % 2) == 0);

    UniqueEntryPtr& to_update = _entries[entry_to_update_index];
    int previous_priority = to_update->priority();
    
    if (update_priority_up_b)
        update_priority_up(entry_to_update_index);
    else
        update_priority_down(entry_to_update_index);

    _last_perturbation_undoer.reset(
        new PriorityRandomUndoer(this,to_update,previous_priority));
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
    {
        _last_perturbation_undoer.reset(new EmptyUndoer());
        return false;
    }

    // choose random entry to merge
    int rand_merge_indices_index = rand() % merge_indices.size();
    // note: not necessary that this pair is const.  Just adding const because
    // don't modify entry at all.
    const std::pair<int,int>& entries_to_merge =
        merge_indices[rand_merge_indices_index];

    // note: important that merge into smaller index so that undoer inserts
    // correctly later.
    UniqueEntryPtr& to_merge_into = _entries[entries_to_merge.first];
    UniqueEntryPtr& to_merge = _entries[entries_to_merge.second];
    // finding this before the merge so that get previous value.
    Header previous_match = to_merge_into->match();
    
    // update entry that's been merged
    to_merge_into->merge_into_me(to_merge);
    // remove old entry
    _entries.erase(_entries.begin() + entries_to_merge.second);

    _last_perturbation_undoer.reset(
        new MergeRandomUndoer(
            _entries,entries_to_merge.first,
            previous_match,std::move(to_merge)));
    
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
