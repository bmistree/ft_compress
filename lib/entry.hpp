#ifndef __ENTRY_HPP__
#define __ENTRY_HPP__

#include "header.hpp"
#include "action.hpp"
#include <vector>
#include <memory>

class Entry;
typedef std::unique_ptr<Entry> UniqueEntryPtr;

class Entry
{
public:
    Entry(int priority,const Header& match);
    ~Entry();
    int priority() const;
    int priority(int new_priority);
    const Header& match() const;
    void add_action(Action* action);
    // sorts so that higher priority is closer to zero index of vector
    static bool sort_unique_ptr_by_priority_descending(
        const UniqueEntryPtr& a, const UniqueEntryPtr& b);
    void debug_print_entry() const;

    /**
      Only can be run on entries that have wildcard matches.  Splits this entry
      into two largest entries can be split into.  Priority of split rule is
      same.  
     */
    UniqueEntryPtr split_entry();

    
private:
    int _priority;
    Header _match;
    ActionList _action_list;
};

typedef std::vector<UniqueEntryPtr> EntryVec;
typedef EntryVec::iterator EntryVecIter;
typedef EntryVec::const_iterator EntryVecCIter;

#endif
