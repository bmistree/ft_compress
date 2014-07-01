#ifndef __ACTION_HPP__
#define __ACTION_HPP__

#include <vector>

class Action;
typedef std::vector<Action*> ActionList;
typedef ActionList::iterator ActionListIter;
typedef ActionList::const_iterator ActionListCIter;


class Action
{
public:
    int action_type();
    virtual ~Action();
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
};

class ForwardAction : public Action
{
public:
    ForwardAction();
    virtual ~ForwardAction();
    const static int FORWARD_ACTION_TYPE = 1;
};

#endif
