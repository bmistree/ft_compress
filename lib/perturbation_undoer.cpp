#include "perturbation_undoer.hpp"

SplitRandomUndoer::SplitRandomUndoer(EntryVec& entries, int old_entry_index)
 : _entries(entries),
   _old_entry_index(old_entry_index)
{}

SplitRandomUndoer::~SplitRandomUndoer()
{}

void SplitRandomUndoer::undo() const
{
    UniqueEntryPtr& old_entry = _entries[_old_entry_index];
    UniqueEntryPtr& new_entry = _entries[_old_entry_index + 1];

    // update entry that's been merged
    old_entry->merge_into_me(new_entry);
    // remove former new_entry
    _entries.erase(_entries.begin() + _old_entry_index + 1);
}
