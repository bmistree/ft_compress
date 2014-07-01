#include "action.hpp"

/** Action */
Action::Action(int act_type)
 : _action_type(act_type)
{}
Action::~Action()
{}

int Action::action_type()
{
    return _action_type;
}


/** DropAction */
DropAction::DropAction()
 : Action(DROP_ACTION_TYPE)
{}

DropAction::~DropAction()
{}

/** ForwardAction */
ForwardAction::ForwardAction()
 : Action(FORWARD_ACTION_TYPE)
{}
ForwardAction::~ForwardAction()
{}

