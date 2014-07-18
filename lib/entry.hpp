#ifndef __ENTRY_HPP__
#define __ENTRY_HPP__

#include "header.hpp"
#include "action.hpp"
#include <vector>
#include <memory>

#define MAX_PRIORITY 32000

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
    void add_action(UniqueActionPtr& action);
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

    /**
       Combines matches of this and to_merge_into_me.  Assumes that this and
       to_merge_into_me are merge-able.  (@see merge_random in table.hpp.)
     */
    void merge_into_me(const UniqueEntryPtr& to_merge_into_me);
    /**
       @return Returns true if this can merge with to_check.  false otherwise.
     */
    bool can_merge(const UniqueEntryPtr& to_check) const;
    
private:
    int _priority;
    Header _match;
    ActionList _action_list;
};

typedef std::vector<UniqueEntryPtr> EntryVec;
typedef EntryVec::iterator EntryVecIter;
typedef EntryVec::const_iterator EntryVecCIter;

#endif
