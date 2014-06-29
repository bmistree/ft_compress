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
    static bool sort_unique_ptr_by_priority(
        const UniqueEntryPtr& a, const UniqueEntryPtr& b);
    
private:
    int _priority;
    Header _match;
    ActionList _action_list;
};

typedef std::vector<UniqueEntryPtr> EntryVec;
typedef EntryVec::iterator EntryVecIter;
typedef EntryVec::const_iterator EntryVecCIter;

#endif
