#ifndef __ACTION_HPP__
#define __ACTION_HPP__

#include <vector>
#include <memory>
#include <unordered_map>

class Action;
typedef std::unique_ptr<Action> UniqueActionPtr;

// FIXME: probably want to use unique pointers for actions here.
typedef std::vector<UniqueActionPtr> ActionList;
typedef ActionList::iterator ActionListIter;
typedef ActionList::const_iterator ActionListCIter;

/**
   Keeps track of all actions.  Used to generate random actions.
 */
typedef std::function<UniqueActionPtr()> ActionFactory;
static std::unordered_map<int,ActionFactory> _action_generator_map;
static int _action_counter = 0;
template<class cls>
static bool _register_action()
{
    ActionFactory to_insert =
        [ /* captures no variables from external scope */]
        ( /* takes no arguments*/)
        -> UniqueActionPtr /* return type */
        {
            return std::move(UniqueActionPtr(new cls()));
        };
    _action_generator_map[_action_counter] = to_insert;
    _action_counter += 1;
    return true;
}


class Action
{
public:
    virtual ~Action();
    int action_type() const;
    virtual bool operator== (const Action& action) = 0;
    bool operator!= (const Action& action);
    static UniqueActionPtr generate_random_action();
private:
    int _action_type;
protected:
    Action(int act_type);
};

class DropAction : public Action
{
public:
    DropAction();
    virtual ~DropAction();
    const static int DROP_ACTION_TYPE = 0;

    virtual bool operator== (const Action& action);
};
const static bool register_drop_action = _register_action<DropAction>();

class ForwardAction : public Action
{
public:
    ForwardAction();
    virtual ~ForwardAction();
    const static int FORWARD_ACTION_TYPE = 1;
    
    virtual bool operator== (const Action& action);
};
const static bool register_forward_action = _register_action<ForwardAction>();
#endif
