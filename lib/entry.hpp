#ifndef __ENTRY_HPP__
#define __ENTRY_HPP__

#include "header.hpp"
#include "action.hpp"

class Entry
{
public:
    Entry(int priority,Header match);
    ~Entry();
    int priority() const;
    int priority(int new_priority);
    const Header& match() const;
    void add_action(Action* action);
    
private:
    int _priority;
    Header _match;
    ActionList _action_list;
};

#endif