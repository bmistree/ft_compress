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

bool Entry::sort_unique_ptr_by_priority(
    const UniqueEntryPtr& a, const UniqueEntryPtr& b)
{
    return a->priority() < b->priority();
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
