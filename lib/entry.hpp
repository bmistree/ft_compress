#ifndef __ENTRY_HPP__
#define __ENTRY_HPP__

#include "match.hpp"
#include "action.hpp"

class Entry
{
public:
    Entry(int priority,Match match);
    ~Entry();
    int priority() const;
    int priority(int new_priority);
    const Match& match() const;
    void add_action(Action* action);
    
private:
    int _priority;
    Match _match;
    ActionList _action_list;
};

#endif
