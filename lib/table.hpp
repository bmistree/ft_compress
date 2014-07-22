#ifndef __TABLE_HPP__
#define __TABLE_HPP__
#include <memory>
#include <set>

#include "entry.hpp"
#include "perturbation_undoer.hpp"

typedef int TableId;

class Table;
typedef std::shared_ptr<Table> SharedTablePtr;
typedef std::set<SharedTablePtr> TablePtrSet;
typedef TablePtrSet::const_iterator TablePtrSetCIter;

class Table
{
public:
    Table();
    ~Table();
    TableId id() const;
    void add_entry(UniqueEntryPtr& entry_ptr);
    void finalize();
    void debug_print_table() const;
    int num_entries() const;
    
    static void chain_tables(SharedTablePtr parent, SharedTablePtr child);

    /**
       Select one of the actions to perform on this table and do so.  Save state
       before this action so that can return to it if get call to
       undo_last_perturbation.
     */
    void perturb();
    void undo_last_perturbation();
    
    /** Should really be private, but need for testing */
    
    /**
       Whenever have:
         1) One entry with higher priority than another entry and
         2) Higher priority entry's match is a superset of lower priority entry
       can delete lower priority entry.
     */
    void filter_eclipsed();
    /**
       From all rules that have wildcards in this table, choose one at random
       and split it into two largest rules that we can.
       
       @returns Returns true if has an entry to split.  false if do not.       
     */
    bool split_random();

    /**
       Try to merge two rules in table.  First, find set of all rules in table
       that can be merged.  Then, select one pair of rules from this set
       randomly and merge them.  Two rules can be merged iff:
         1) They have equivalent action sets
         2) They have the same priorities
       Note on 2: this condition is sufficient, but not necessary.  When we
       combine it with reprioritization action, we're set though.

       @returns Returns true if there were entries to merge.  false otherwise.
     */
    bool merge_random();

    /**
       Update the priority of a random rule either up or down.
     */
    bool priority_random();
    
private:
    TableId _id;

    // sorted by priority.  Higher priority closer to index 0.
    EntryVec _entries;
    TablePtrSet _children;
    SharedTablePtr _parent;
    UniquePerturbationUndoerPtr _last_perturbation_undoer;
    
    void update_priority_up(int index_to_update);
    void update_priority_down(int index_to_update);
};


#endif
