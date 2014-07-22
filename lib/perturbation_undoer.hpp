#ifndef __PERTURBATION_UNDOER_HPP__
#define __PERTURBATION_UNDOER_HPP__

#include <memory>
#include "entry.hpp"


class PerturbationUndoer;
typedef std::unique_ptr<PerturbationUndoer> UniquePerturbationUndoerPtr;

class PerturbationUndoer
{
public:
    virtual void undo() = 0;
};

/**
   For cases where action results in no op.
 */
class EmptyUndoer : public PerturbationUndoer
{
public:
    virtual void undo()
    {}
};


class SplitRandomUndoer : public PerturbationUndoer
{
public:
    /**
       @param entries --- reference to entries held by actual table.
       
       @param old_entry_index --- The position that the entry that was split
       resides in.  old_entry_index+1 should be the entry that it was split
       with.
    */
    SplitRandomUndoer(EntryVec& entries,int old_entry_index);
    ~SplitRandomUndoer();
    virtual void undo();
    
private:
    EntryVec& _entries;
    int _old_entry_index;
};

class MergeRandomUndoer : public PerturbationUndoer
{
public:
    /**
       @param entries --- reference to entries held by actual table.
       
       @param entry_still_there_index --- The position of the new combined
       entry.

       @param entry_still_there_old_header --- The header for the old entry that
       was merged into.

       @param removed_entry --- The entry that was removed during merge.
    */
    MergeRandomUndoer(
        EntryVec& entries,int entry_still_there_index,
        Header entry_still_there_old_header,
        UniqueEntryPtr removed_entry);
    ~MergeRandomUndoer();
    virtual void undo();
    
private:
    EntryVec& _entries;
    int _entry_still_there_index;
    Header _entry_still_there_old_header;
    UniqueEntryPtr _removed_entry;
};


class Table;
class PriorityRandomUndoer : public PerturbationUndoer
{
public:
    // table is borrowed, do not delete
    PriorityRandomUndoer(
        Table* table, UniqueEntryPtr& entry, int old_priority);
    ~PriorityRandomUndoer();
    virtual void undo();
    
private:
    // borrowed, do not delete
    Table* _table;
    UniqueEntryPtr& _entry;
    int _old_priority;
};


#endif
