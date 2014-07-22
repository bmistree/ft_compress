#include <vector>
#include <memory>
#include <iostream>

#include "perturbation_undoer.hpp"
#include "table.hpp"

/** SplitRandomUndoer */
SplitRandomUndoer::SplitRandomUndoer(EntryVec& entries, int old_entry_index)
 : _entries(entries),
   _old_entry_index(old_entry_index)
{}

SplitRandomUndoer::~SplitRandomUndoer()
{}

void SplitRandomUndoer::undo()
{
    UniqueEntryPtr& old_entry = _entries[_old_entry_index];
    UniqueEntryPtr& new_entry = _entries[_old_entry_index + 1];

    // update entry that's been merged
    old_entry->merge_into_me(new_entry);
    // remove former new_entry
    _entries.erase(_entries.begin() + _old_entry_index + 1);
}


/** MergeRandomUndoer */

MergeRandomUndoer::MergeRandomUndoer(
    EntryVec& entries,int entry_still_there_index,
    Header entry_still_there_old_header,UniqueEntryPtr removed_entry)
 : _entries(entries),
   _entry_still_there_index(entry_still_there_index),
   _entry_still_there_old_header(entry_still_there_old_header),
   _removed_entry(std::move(removed_entry))
{}

MergeRandomUndoer::~MergeRandomUndoer()
{}

void MergeRandomUndoer::undo()
{
    // FIXME: See below
    std::cout<<"\nFIXME: may still need to re-add ";
    std::cout<<"all entries that got finalized out.\n";
    
    _entries[_entry_still_there_index]->set_header(
        _entry_still_there_old_header);
    _entries.insert(
        _entries.begin() + _entry_still_there_index + 1,
        std::move(_removed_entry));
}

/** PriorityRandomUndoer */

PriorityRandomUndoer::PriorityRandomUndoer(
    Table* table, UniqueEntryPtr& entry, int old_priority)
 : _table(table),
   _entry(entry),
   _old_priority(old_priority)
{}
PriorityRandomUndoer::~PriorityRandomUndoer()
{}

void PriorityRandomUndoer::undo()
{
    _entry->priority(_old_priority);
    // FIXME: expensive to undo this operation.
    _table->finalize();
}
