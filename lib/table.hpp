#ifndef __TABLE_HPP__
#define __TABLE_HPP__
#include <memory>
#include <set>

#include "entry.hpp"

typedef int TableId;

class Table;
typedef std::shared_ptr<Table> SharedTablePtr;
typedef std::set<SharedTablePtr> TablePtrSet;


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
     */
    void split_random();
    
private:
    TableId _id;

    // sorted by priority.  Higher priority closer to index 0.
    EntryVec _entries;
    TablePtrSet _children;
    SharedTablePtr _parent;
};


#endif
