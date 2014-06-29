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
    static void chain_tables(SharedTablePtr parent, SharedTablePtr child);
    
private:
    TableId _id;
    EntryVec _entries;
    TablePtrSet _children;
    SharedTablePtr _parent;
};

#endif
