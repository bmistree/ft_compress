#ifndef __PERTURBATION_UNDOER_HPP__
#define __PERTURBATION_UNDOER_HPP__

#include <memory>
#include "entry.hpp"

class PerturbationUndoer;
typedef std::unique_ptr<PerturbationUndoer> UniquePerturbationUndoerPtr;

class PerturbationUndoer
{
public:
    virtual void undo() const = 0;
};

/**
   For cases where action results in no op.
 */
class EmptyUndoer : public PerturbationUndoer
{
public:
    virtual void undo() const
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
    virtual void undo() const;
    
private:
    EntryVec& _entries;
    int _old_entry_index;
};

#endif
