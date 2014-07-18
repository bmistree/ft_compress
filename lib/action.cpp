#include "action.hpp"
#include <stdlib.h>

/** Action */
Action::Action(int act_type)
 : _action_type(act_type)
{}
Action::~Action()
{}

UniqueActionPtr Action::generate_random_action()
{
    int which_action = rand() % _action_generator_map.size();
    return std::move( _action_generator_map[which_action]());
}

int Action::action_type() const
{
    return _action_type;
}
bool Action::operator!= (const Action& action)
{
    return ! ((*this) == action);
}


/** DropAction */
DropAction::DropAction()
 : Action(DROP_ACTION_TYPE)
{}

DropAction::~DropAction()
{}

bool DropAction::operator== (const Action& action)
{
    return action.action_type() == action_type();
}

/** ForwardAction */
ForwardAction::ForwardAction()
 : Action(FORWARD_ACTION_TYPE)
{}
ForwardAction::~ForwardAction()
{}

bool ForwardAction::operator== (const Action& action)
{
    return action.action_type() == action_type();
}
