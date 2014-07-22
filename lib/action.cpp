#include "action.hpp"
#include <stdlib.h>

/** Action */
Action::Action(ActionType act_type)
 : _action_type(act_type)
{}
Action::~Action()
{}

UniqueActionPtr Action::generate_random_action(
    const GeneralActionConstructionParameters& params)
{
    int which_action = rand() % _action_generator_map.size();
    return std::move( _action_generator_map[which_action](params));
}

ActionType Action::action_type() const
{
    return _action_type;
}
bool Action::operator!= (const Action& action)
{
    return ! ((*this) == action);
}


/** DropAction */
DropAction::DropAction()
 : Action(ActionType::DROP_ACTION_TYPE)
{}

DropAction::DropAction(const GeneralActionConstructionParameters& params)
 : DropAction()
{}

DropAction::~DropAction()
{}

bool DropAction::operator== (const Action& action)
{
    return action.action_type() == action_type();
}

/** ForwardAction */
ForwardAction::ForwardAction(int port)
 : Action(ActionType::FORWARD_ACTION_TYPE),
   _port(port)
{}
ForwardAction::ForwardAction(const GeneralActionConstructionParameters& params)
 : ForwardAction( rand() % params.num_ports)
{}

ForwardAction::~ForwardAction()
{}

bool ForwardAction::operator== (const Action& action)
{
    if (action.action_type() != action_type())
        return false;

    const ForwardAction& cast_action = (const ForwardAction&) action;
    return cast_action._port == _port;
}
