#ifndef __TABLE_HPP__
#define __TABLE_HPP__

#include "entry.hpp"

typedef int TableId;

class Table
{
public:
    Table();
    ~Table();
    TableId id() const;
    void add_entry(UniqueEntryPtr& entry_ptr);
    void finalize();
    void debug_print_table() const;
private:
    TableId _id;
    EntryVec _entries;
};

#endif
