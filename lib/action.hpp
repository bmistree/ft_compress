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
    virtual ~Action();
    
    int action_type() const;
    virtual bool operator== (const Action& action) = 0;
    
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

class ForwardAction : public Action
{
public:
    ForwardAction();
    virtual ~ForwardAction();
    const static int FORWARD_ACTION_TYPE = 1;
    
    virtual bool operator== (const Action& action);
};

#endif
