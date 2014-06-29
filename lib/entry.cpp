#include "entry.hpp"

Entry::Entry(int priority,Match match)
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

int Entry::priority() const
{
    return _priority;
}
int Entry::priority(int new_priority)
{
    _priority = new_priority;
    return _priority;
}

const Match& Entry::match() const
{
    return _match;
}

void Entry::add_action(Action* action)
{
    _action_list.push_back(action);
}
