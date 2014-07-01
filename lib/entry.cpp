#include <memory>
#include <iostream>
#include <iomanip>
#include <cassert>

#include "entry.hpp"
#include "header.hpp"


Entry::Entry(int priority,const Header& match)
 : _priority (priority),
   _match (match)
{}

Entry::~Entry()
{
    for (ActionListIter iter = _action_list.begin();
         iter != _action_list.end(); ++iter)
    {
        delete *iter;
    }
    _action_list.clear();
}

UniqueEntryPtr Entry::split_entry()
{
    // can only be run on header that has wildcard
    if (! _match.has_wildcard())
        assert(false);

    Header split_header = _match.split_header();
    Entry* split_entry = new Entry(_priority,split_header);
    UniqueEntryPtr split_entry_ptr(split_entry);
    return std::move(split_entry_ptr);
}

void Entry::debug_print_entry() const
{
    std::cout<<"\tpriority: "<<_priority<<"\n";
    std::cout<<"\tmatch: "<<_match.header_str()<<"\n";
}

bool Entry::sort_unique_ptr_by_priority_descending(
    const UniqueEntryPtr& a, const UniqueEntryPtr& b)
{
    return a->priority() > b->priority();
}

int Entry::priority() const
{
    return _priority;
}
int Entry::priority(int new_priority)
{
    _priority = new_priority;
    return _priority;
}

const Header& Entry::match() const
{
    return _match;
}

void Entry::add_action(Action* action)
{
    _action_list.push_back(action);
}

void Entry::merge_into_me(const UniqueEntryPtr& to_merge_into_me)
{
    // FIXME: stub method, must finish.
}

bool Entry::can_merge(const UniqueEntryPtr& to_check) const
{
    if (to_check->priority() != _priority)
        return false;

    // FIXME: can be a lot less conservative checking action list.  In
    // particular, this requires that actions are in same order.  In reality,
    // lots of actions can commute.  Similarly, may be able to merge rules that

    if (_action_list.size() != to_check->_action_list.size())
        return false;

    for (int i = 0; i < _action_list.size(); ++i)
    {
        Action* my_action = _action_list[i];
        const Action* to_check_action = to_check->_action_list[i];

        if ( (*my_action) != (*to_check_action) )
            return false;
    }
    return true;
}
